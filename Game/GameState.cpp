#include "GameState.hpp"

#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <cstdlib>

#include "SDL.h"

#include "../AN/ANDeclarations.hpp"
#include "../AN/GameLoop.hpp"
#include "../AN/BitmapFont.hpp"
#include "../AN/Helpers.hpp"
#include "../AN/TextureHelper.hpp"

#include "GameDeclarations.hpp"
#include "Game.hpp"
#include "MoveButton.hpp"

#include "Extras/ExtraDeclarations.hpp"
#include "Extras/Card.hpp"
#include "Extras/OtherHand.hpp"
#include "Extras/CardSpriteManager.hpp"
#include "Extras/CardHand.hpp"
#include "Extras/SomeHand.hpp"

namespace game
{

GameState::GameState(Game *_g) : g(_g), tex_arrow(NULL), state(STATE::NONE),
                                 state_next(STATE::NONE), state_prev(STATE::NONE),
                                 anim_timer(0), rounds(0), player(DIRECTION::NORTH),
                                 starting(DIRECTION::NORTH), first_card(false),
                                 hearts_broken(false) {}

GameState::~GameState()
{
    cleanup();
}

void GameState::setup(an::SDLData *d)
{
    tex_arrow = d->textures->get("arrow.png");

    generate_deck();

    for (int i = 0; i < 4; i++)
        rotations.push_back(std::vector<Card>());

    state_prev = STATE::NONE;
    state = STATE::ANIMATION;
    state_next = STATE::DEALING_CARDS;
    anim_timer = 90;

    first_card = true;
    hearts_broken = false;
    rounds = 0;
}

void GameState::cleanup()
{
    choices.clear();
    rotations.clear();
    deck.clear();
    tex_arrow = NULL;
}

void GameState::handleEvent(SDL_Event *e)
{
    MoveButton *btn_move = g->g_btn_move();
    CardHand *hand = g->g_hand();

    switch (e->type)
    {
    case SDL_MOUSEBUTTONDOWN:
    {
        SDL_MouseButtonEvent data = e->button;
        if (data.button != SDL_BUTTON_LEFT)
            break;
        if (!btn_move->was_clicked(data.x, data.y))
            break;

        switch (state)
        {
        case STATE::ROTATION:
        {
            if (hand->count() != 3)
                break;
            btn_move->visible = false;

            hand->place_rotation(rotations[3]);

            state = STATE::ROTATION_WAITING;
        }
        break;
        case STATE::CHOOSE_CARD:
        {
            if (!hand->chosen)
                break;

            Card c = hand->get_choice();
            if (!hand->can_play(this, c))
                break;

            hand->play_card(choices);
            btn_move->visible = false;
            first_card = false;

            state_prev = state;
            state = STATE::NEXT_MOVE;
        }
        break;
        default:
            break;
        }
    }
    break;
    default:
        break;
    }

    switch (state)
    {
    case STATE::ROTATION:
    case STATE::CHOOSE_CARD:
    case STATE::WAIT_TO_CHOOSE:
        hand->handleEvent(e);
        break;
    default:
        break;
    }
}

void GameState::update()
{
    CardHand *hand = g->g_hand();
    MoveButton *btn_move = g->g_btn_move();
    std::vector<OtherHand> *players = g->g_players();

    switch (state)
    {
    case STATE::ANIMATION:
        anim_timer--;
        if (anim_timer <= 0)
            state = state_next;
        switch (state)
        {
        case STATE::ROTATION:
        {
            btn_move->set_color(150, 0, 0);
            btn_move->msg = STR_ROTATION_PICK;
            btn_move->visible = true;
        }
        break;
        default:
            break;
        }
        break;
    case STATE::DEALING_CARDS:
    {
        if (deck.size() == 0)
        {
            hand->multi_select = true;
            hand->chosen = false;

            state_prev = state;
            state = STATE::ANIMATION;
            state_next = STATE::ROTATION;
            anim_timer = 120;
            break;
        }

        anim_timer--;
        if (anim_timer > 0)
            break;
        anim_timer = 3;

        Card top = deck.back();
        deck.pop_back();

        get_somehand(player)->dealt(top);
        player = rotate_direction(player);
    }
    break;
    case STATE::ROTATION:
    {
        int count = hand->count();
        if (count == 3)
        {
            btn_move->set_color(0, 150, 0);
            btn_move->msg = STR_ROTATION_CONFIRM;
        }
        else
        {
            btn_move->set_color(150, 0, 0);
            btn_move->msg = STR_ROTATION_PICK;
        }

        for (int i = 0; i < 3; i++)
        {
            if ((*players)[i].chosen)
                continue;
            if (std::rand() % 120 != 0)
                continue;
            (*players)[i].choose_rotation(rotations[i]);
        }
    }
    break;
    case STATE::ROTATION_WAITING:
    {
        bool need_more = false;
        for (int i = 0; i < 3; i++)
        {
            if ((*players)[i].chosen)
                continue;
            need_more = true;
            if (std::rand() % 30 != 0)
                continue;
            (*players)[i].choose_rotation(rotations[i]);
        }
        if (!need_more)
        {
            state_prev = state;
            state = STATE::ANIMATION;
            state_next = STATE::ROTATION_PERFORM;
            anim_timer = ROTATION_DELAY + ROTATION_TIME + ROTATION_HOLD;
        }
    }
    break;
    case STATE::ROTATION_PERFORM:
    {
        for (int i = 0; i < 4; i++)
            get_somehand(i)->take_rotation(rotations[(i + 1) % 4]);
        state = STATE::PICK_FIRST;
    }
    break;
    case STATE::PICK_FIRST:
    {
        hand->multi_select = false;
        hand->reset_choice();
        first_card = true;

        for (int i = 0; i < 4; i++)
        {
            if (get_somehand(i)->has_two_clubs())
            {
                if (i == 3)
                {
                    starting = player = DIRECTION::SOUTH;
                    state = STATE::CHOOSE_CARD;
                }
                else
                {
                    starting = player = static_cast<DIRECTION>(i);
                    state = STATE::WAIT_TO_CHOOSE;
                    anim_timer = 60;
                }
            }
        }

        btn_move->visible = true;
        if (player == DIRECTION::SOUTH)
        {
            btn_move->set_color(150, 0, 0);
            btn_move->msg = STR_CHOOSE_PICK;
        }
        else
        {
            btn_move->set_color(0, 150, 150);
            btn_move->msg = STR_WAIT_TURN;
        }
    }
    break;
    case STATE::CHOOSE_CARD:
    {
        if (hand->chosen)
        {
            Card c = hand->get_choice();
            if (hand->can_play(this, c))
            {
                btn_move->set_color(0, 150, 0);
                btn_move->msg = STR_CHOOSE_CONFIRM;
                break;
            }
        }
        btn_move->set_color(150, 0, 0);
        btn_move->msg = STR_CHOOSE_PICK;
    }
    break;
    case STATE::WAIT_TO_CHOOSE:
    case STATE::WAIT_TO_FINISH:
    {
        anim_timer--;
        if (anim_timer > 0)
            break;
        switch (player)
        {
        case DIRECTION::EAST:
            (*players)[1].choose_card(this, choices);
            break;
        case DIRECTION::WEST:
            (*players)[2].choose_card(this, choices);
            break;
        case DIRECTION::NORTH:
        default:
            (*players)[0].choose_card(this, choices);
            break;
        }
        first_card = false;

        state_prev = state;
        state = STATE::NEXT_MOVE;
    }
    break;
    case STATE::NEXT_MOVE:
    {
        anim_timer--;
        if (anim_timer > 0)
            break;
        player = rotate_direction(player);
        if (player == starting)
        {
            state = STATE::END_HAND;
            anim_timer = 90;
        }
        else
        {
            int choose_time = rand_int(30, 60);
            if (state_prev == STATE::CHOOSE_CARD)
            {
                anim_timer = choose_time;
                state = STATE::WAIT_TO_FINISH;
            }
            else if (player == DIRECTION::SOUTH)
                state = STATE::CHOOSE_CARD;
            else
            {
                anim_timer = choose_time;
                state = STATE::WAIT_TO_CHOOSE;
            }
        }
    }
    break;
    case STATE::END_HAND:
    {
        end_round();
        SDL_SetTextureColorMod(tex_arrow, 50, 255, 50);

        state_prev = state;
        state = STATE::ANIMATION;
        state_next = STATE::END_ROUND;
        anim_timer = 60;
    }
    break;
    case STATE::END_ROUND:
    {
        SDL_SetTextureColorMod(tex_arrow, 255, 255, 255);

        starting = player;
        choices.clear();

        rounds++;
        if (rounds >= 13)
        {
            state = STATE::GAME_OVER;
            int lowest = -1;
            for (int i = 0; i < 4; i++)
            {
                int points = get_somehand(i)->points;
                lowest = (points < lowest || lowest == -1) ? points : lowest;
            }
            for (int i = 0; i < 4; i++)
            {
                SomeHand *sh = get_somehand(i);
                sh->chosen = sh->points <= lowest;
            }
            break;
        }

        for (int i = 0; i < 4; i++)
            get_somehand(i)->chosen = false;

        if (player == DIRECTION::SOUTH)
            state = STATE::CHOOSE_CARD;
        else
            state = STATE::WAIT_TO_CHOOSE;

        btn_move->visible = true;
        if (player == DIRECTION::SOUTH)
        {
            btn_move->set_color(150, 0, 0);
            btn_move->msg = STR_CHOOSE_PICK;
        }
        else
        {
            btn_move->set_color(0, 150, 150);
            btn_move->msg = STR_WAIT_TURN;
        }
    }
    break;
    default:
        break;
    }
}

void GameState::render(an::SDLData *d, CardSpriteManager *csm)
{
    std::vector<OtherHand> *players = g->g_players();
    CardHand *hand = g->g_hand();
    SDL_Texture *back = csm->get_back();
    an::BitmapFont *bfnt = g->g_bfnt();
    const int cx = d->loop->SCREEN_WIDTH / 2;
    const int cy = d->loop->SCREEN_HEIGHT / 2 + OtherHand::CENTER_OFFSET;

    STATE to_draw = state;
    if (state == STATE::ANIMATION)
    {
        switch (state_prev)
        {
        case STATE::ROTATION_WAITING:
            to_draw = STATE::ROTATION_PERFORM;
            break;
        case STATE::END_HAND:
            to_draw = STATE::END_HAND;
            break;
        default:
            break;
        }
    }

    switch (to_draw)
    {
    case STATE::DEALING_CARDS:
    {
        if (deck.size() > 0)
            an::renderTexture_centered(d, back, cx, cy, NULL, CENTER_SCALE, 0.0);
    }
    break;
    case STATE::ROTATION:
    case STATE::ROTATION_WAITING:
    {
        for (int i = 0; i < 4; i++)
        {
            switch (i)
            {
            case 0:
            case 1:
            case 2:
                if ((*players)[i].chosen)
                    draw_center(d, i, back, true);
                break;
            case 3:
            default:
                if (hand->chosen)
                    draw_center(d, 3, back, true);
                break;
            }
        }
    }
    break;
    case STATE::ROTATION_PERFORM:
    {
        double p = (double)(ROTATION_TIME + ROTATION_DELAY - anim_timer) / (double)ROTATION_TIME;
        if (p < 0.0)
            p = 0.0;
        if (p > 1.0)
            p = 1.0;

        double angle = p * 90.0;
        int len = (int)(an::CARD_HEIGHT * CENTER_SCALE);
        int t_dx = lengthdir_x(len, angle);
        int t_dy = lengthdir_y(len, angle);
        int dlen = (int)(OtherHand::SPACING_SIDES * CENTER_SCALE);
        int t_ddx = lengthdir_x(dlen, angle + 90.0);
        int t_ddy = lengthdir_y(dlen, angle + 90.0);

        int dx, dy, ddx, ddy, da;
        for (int i = 0; i < 4; i++)
        {
            switch (i)
            {
            case 0:
                dx = t_dy;
                dy = -t_dx;
                ddx = t_ddy;
                ddy = -t_ddx;
                da = 180.0;
                break;
            case 1:
                dx = t_dx;
                dy = t_dy;
                ddx = t_ddx;
                ddy = t_ddy;
                da = 270.0;
                break;
            case 2:
                dx = -t_dx;
                dy = -t_dy;
                ddx = -t_ddx;
                ddy = -t_ddy;
                da = 90.0;
                break;
            case 3:
            default:
                dx = -t_dy;
                dy = t_dx;
                ddx = -t_ddy;
                ddy = t_ddx;
                da = 0.0;
                break;
            }
            for (int j = -1; j <= 1; j++)
                an::renderTexture_centered(d, back, cx + dx - j * ddx, cy + dy - j * ddy, NULL, CENTER_SCALE, angle + da);
        }
    }
    break;
    case STATE::CHOOSE_CARD:
    case STATE::WAIT_TO_CHOOSE:
    case STATE::WAIT_TO_FINISH:
    case STATE::NEXT_MOVE:
    case STATE::END_HAND:
    {
        draw_arrow(d, cx, cy);

        DIRECTION cur = starting;
        for (auto it = choices.begin(); it != choices.end(); it++)
        {
            switch (cur)
            {
            case DIRECTION::NORTH:
                draw_center(d, 0, csm->get_texture(*it), false);
                break;
            case DIRECTION::EAST:
                draw_center(d, 1, csm->get_texture(*it), false);
                break;
            case DIRECTION::WEST:
                draw_center(d, 2, csm->get_texture(*it), false);
                break;
            case DIRECTION::SOUTH:
            default:
                draw_center(d, 3, csm->get_texture(*it), false);
                break;
            }
            cur = rotate_direction(cur);
        }

        if (to_draw == STATE::END_HAND)
            draw_arrow(d, cx, cy);
    }
    break;
    case STATE::GAME_OVER:
    {
        std::ostringstream oss;
        int dx, dy, delta;
        dx = dy = 0;
        delta = (int)(an::CARD_HEIGHT * CENTER_SCALE);
        for (int i = 0; i < 4; i++)
        {
            switch (i)
            {
            case 0:
            {
                dx = 0;
                dy = -delta;
                oss << "North: " << (*players)[0].points;
                bfnt->set_halign(an::FA_CENTER);
                bfnt->set_valign(an::FA_BOTTOM);
            }
            break;
            case 1:
            {
                dx = delta;
                dy = 0;
                oss << "East: " << (*players)[1].points;
                bfnt->set_halign(an::FA_LEFT);
                bfnt->set_valign(an::FA_MIDDLE);
            }
            break;
            case 2:
            {
                dx = -delta;
                dy = 0;
                oss << "West: " << (*players)[2].points;
                bfnt->set_halign(an::FA_RIGHT);
                bfnt->set_valign(an::FA_MIDDLE);
            }
            break;
            case 3:
            default:
            {
                dx = 0;
                dy = delta;
                oss << "Player: " << hand->points;
                bfnt->set_halign(an::FA_CENTER);
                bfnt->set_valign(an::FA_TOP);
            }
            break;
            }

            if (get_somehand(i)->chosen)
                bfnt->set_color(50, 255, 50);
            else
                bfnt->set_color(255, 255, 255);
            bfnt->renderString(oss.str(), cx + dx, cy + dy);
            oss.str("");
        }

        bfnt->set_color(255, 50, 50);
        bfnt->set_halign(an::FA_CENTER);
        bfnt->set_valign(an::FA_BOTTOM);
        bfnt->renderString(STR_RESTART, cx, d->loop->SCREEN_HEIGHT);

        bfnt->set_color(255, 255, 255);
        bfnt->set_valign(an::FA_MIDDLE);
    }
    break;
    default:
        break;
    }

    if (state == STATE::ANIMATION)
    {
        std::string msg = ANIM_BLANK;
        switch (state_next)
        {
        case STATE::DEALING_CARDS:
            msg = ANIM_DEALING_CARDS;
            break;
        case STATE::ROTATION:
            msg = ANIM_ROTATION;
            break;
        case STATE::ROTATION_PERFORM:
            msg = ANIM_ROTATION_PERFORM;
            break;
        default:
            break;
        }
        if (msg != ANIM_BLANK)
            bfnt->renderString(msg, cx, cy);
    }

    if (state != STATE::GAME_OVER && state != STATE::DEALING_CARDS &&
        !(state == STATE::ANIMATION && state_next == STATE::DEALING_CARDS))
    {
        std::ostringstream oss("");
        int x, y;
        an::HALIGN hal;
        an::VALIGN val;
        for (int i = 0; i < 4; i++)
        {
            switch (i)
            {
            case 0:
                oss << 'N';
                x = 0;
                y = 0;
                hal = an::FA_LEFT;
                val = an::FA_TOP;
                break;
            case 1:
                oss << 'E';
                x = d->loop->SCREEN_WIDTH;
                y = 0;
                hal = an::FA_RIGHT;
                val = an::FA_TOP;
                break;
            case 2:
                oss << 'W';
                x = 0;
                y = d->loop->SCREEN_HEIGHT;
                hal = an::FA_LEFT;
                val = an::FA_BOTTOM;
                break;
            case 3:
            default:
                oss << 'P';
                x = d->loop->SCREEN_WIDTH;
                y = d->loop->SCREEN_HEIGHT;
                hal = an::FA_RIGHT;
                val = an::FA_BOTTOM;
                break;
            }
            oss << ':' << get_somehand(i)->points;
            bfnt->set_halign(hal);
            bfnt->set_valign(val);
            bfnt->renderString(oss.str(), x, y);
            oss.str("");
        }
        bfnt->set_halign(an::FA_CENTER);
        bfnt->set_valign(an::FA_MIDDLE);
    }
}

bool GameState::can_play(std::vector<Card> &my_hand, Card &my_card)
{
    if (first_card)
        return my_card.g_suit() == SUIT::CLUBS && my_card.g_value() == FACE::TWO;

    if (my_card.g_suit() == SUIT::HEARTS)
        return is_broken(my_hand);

    if (choices.size() == 0)
        return true;

    Card trick = choices[0];
    SUIT s_trick = trick.g_suit();
    if (my_card.g_suit() == s_trick)
        return true;

    for (auto it = my_hand.begin(); it != my_hand.end(); it++)
        if (it->g_suit() == s_trick)
            return false;
    return true;
}

bool GameState::is_over()
{
    return state == STATE::GAME_OVER;
}

void GameState::generate_deck()
{
    Card::generate_deck(deck);
    std::random_shuffle(deck.begin(), deck.end());
}

void GameState::draw_center(an::SDLData *d, int i, SDL_Texture *tex, bool three)
{
    const int cx = d->loop->SCREEN_WIDTH / 2;
    const int cy = d->loop->SCREEN_HEIGHT / 2 + OtherHand::CENTER_OFFSET;

    int sx, sy, dx, dy;
    double angle;
    sx = sy = dx = dy = 0;
    angle = 0.0;

    switch (i)
    {
    case 0:
        sx = cx + (int)(OtherHand::SPACING_SIDES * CENTER_SCALE);
        sy = cy - (int)(an::CARD_HEIGHT * CENTER_SCALE);
        dx = -(int)(OtherHand::SPACING_SIDES * CENTER_SCALE);
        dy = 0;
        angle = 180.0;
        break;
    case 1:
        sx = cx + (int)(an::CARD_HEIGHT * CENTER_SCALE);
        sy = cy + (int)(OtherHand::SPACING_SIDES * CENTER_SCALE);
        dx = 0;
        dy = -(int)(OtherHand::SPACING_SIDES * CENTER_SCALE);
        angle = 270.0;
        break;
    case 2:
        sx = cx - (int)(an::CARD_HEIGHT * CENTER_SCALE);
        sy = cy - (int)(OtherHand::SPACING_SIDES * CENTER_SCALE);
        dx = 0;
        dy = (int)(OtherHand::SPACING_SIDES * CENTER_SCALE);
        angle = 90.0;
        break;
    case 3:
    default:
        sx = cx - (int)(OtherHand::SPACING_SIDES * CENTER_SCALE);
        sy = cy + (int)(an::CARD_HEIGHT * CENTER_SCALE);
        dx = (int)(OtherHand::SPACING_SIDES * CENTER_SCALE);
        dy = 0;
        angle = 0.0;
        break;
    }

    if (!three)
        an::renderTexture_centered(d, tex, sx + dx, sy + dy, NULL, CENTER_SCALE, angle);
    else
        for (int j = 0; j < 3; j++)
            an::renderTexture_centered(d, tex, sx + j * dx, sy + j * dy, NULL, CENTER_SCALE, angle);
}

bool GameState::is_broken(std::vector<Card> &hand)
{
    if (hearts_broken)
        return true;

    for (auto it = choices.begin(); it != choices.end(); it++)
        if (it->g_suit() == SUIT::HEARTS)
            return hearts_broken = true;

    for (auto it = hand.begin(); it != hand.end(); it++)
        if (it->g_suit() != SUIT::HEARTS)
            return false;

    return hearts_broken = true;
}

void GameState::end_round()
{
    if (choices.size() == 0)
        return;

    Card trick = choices[0];
    int points, winner;
    points = trick.points();
    winner = 0;

    for (unsigned int i = 1; i < choices.size(); i++)
    {
        Card cur = choices[i];
        if (cur > trick)
        {
            trick = cur;
            winner = i;
        }
        points += cur.points();
    }

    for (int i = 0; i < winner; i++)
        player = rotate_direction(player);
    get_somehand(player)->points += points;
}

SomeHand *GameState::get_somehand(int i)
{
    std::vector<OtherHand> *players = g->g_players();
    switch (i)
    {
    case 0:
    case 1:
    case 2:
        return (SomeHand *)(&((*players)[i]));
    case 3:
    default:
        return g->g_hand();
    }
}

SomeHand *GameState::get_somehand(DIRECTION d)
{
    std::vector<OtherHand> *players = g->g_players();
    switch (d)
    {
    case DIRECTION::NORTH:
        return (SomeHand *)(&((*players)[0]));
    case DIRECTION::EAST:
        return (SomeHand *)(&((*players)[1]));
    case DIRECTION::WEST:
        return (SomeHand *)(&((*players)[2]));
    case DIRECTION::SOUTH:
    default:
        return g->g_hand();
    }
}

void GameState::draw_arrow(an::SDLData *d, int cx, int cy)
{
    double angle = 0.0;
    switch (player)
    {
    case DIRECTION::NORTH:
        angle = 180.0;
        break;
    case DIRECTION::EAST:
        angle = 270.0;
        break;
    case DIRECTION::WEST:
        angle = 90.0;
        break;
    case DIRECTION::SOUTH:
    default:
        angle = 0.0;
        break;
    }
    an::renderTexture_centered(d, tex_arrow, cx, cy, NULL, 1.0, angle);
}

} // namespace game

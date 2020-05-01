#include "CardHand.hpp"

#include <vector>

#include "../../AN/ANDeclarations.hpp"
#include "../../AN/GameLoop.hpp"
#include "../../AN/Helpers.hpp"

#include "ExtraDeclarations.hpp"
#include "SomeHand.hpp"
#include "Card.hpp"
#include "CardSpriteManager.hpp"

#include "../GameDeclarations.hpp"
#include "../GameState.hpp"

namespace game
{

const int CardHand::DROP = 100;
const int CardHand::SPACING = 45;
const int CardHand::RAISE = 50;

CardHand::CardHand() : SomeHand(),
                       multi_select(false) {}

CardHand::~CardHand()
{
    cleanup();
}

void CardHand::setup(an::SDLData *d)
{
    SomeHand::setup(d);
    multi_select = false;
}

void CardHand::cleanup()
{
    SomeHand::cleanup();
}

void CardHand::clear()
{
    cards.clear();
}

void CardHand::reset_choice()
{
    for (auto it = cards.begin(); it != cards.end(); it++)
        it->chosen = false;
    chosen = false;
}

Card CardHand::get_choice()
{
    for (auto it = cards.begin(); it != cards.end(); it++)
        if (it->chosen)
            return *it;
    return Card::BLANK;
}

void CardHand::render(an::SDLData *d, CardSpriteManager *csm)
{
    if (cards.size() == 0)
        return;

    const int sx = start_x();
    const int sy = start_y();

    int x = sx - CardHand::SPACING;
    for (auto it = cards.begin(); it != cards.end(); it++)
        an::renderTexture(d, csm->get_texture(*it), x += CardHand::SPACING, sy - (it->chosen ? CardHand::RAISE : 0), NULL);
}

void CardHand::handleEvent(SDL_Event *e)
{
    if (e->type != SDL_MOUSEBUTTONDOWN)
        return;

    SDL_MouseButtonEvent data = e->button;
    if (data.button != SDL_BUTTON_LEFT)
        return;

    const int mx = data.x;
    const int my = data.y;
    const int sx = start_x();
    const int sy = start_y();
    const int w = an::CARD_WIDTH;
    const int h = an::CARD_HEIGHT;
    int x = sx - CardHand::SPACING;
    int y = sy;

    auto it_cur = cards.end();
    for (auto it = cards.begin(); it != cards.end(); it++)
    {
        x += CardHand::SPACING;
        y = sy - (it->chosen ? CardHand::RAISE : 0);

        if ((x <= mx && mx <= x + w) && (y <= my && my <= y + h))
            it_cur = it;
    }

    if (it_cur != cards.end())
    {
        if (multi_select)
            it_cur->chosen = !it_cur->chosen;
        else if (it_cur->chosen)
        {
            it_cur->chosen = false;
            chosen = false;
        }
        else
        {
            for (auto it = cards.begin(); it != cards.end(); it++)
                it->chosen = false;
            it_cur->chosen = true;
            chosen = true;
        }
    }
}

int CardHand::count()
{
    int res = 0;
    for (auto it = cards.begin(); it != cards.end(); it++)
        if (it->chosen)
            res++;
    return res;
}

int CardHand::start_x()
{
    if (cards.size() == 0)
        return -1;
    return (data->loop->SCREEN_WIDTH - ((cards.size() - 1) * CardHand::SPACING + an::CARD_WIDTH)) / 2;
}

int CardHand::start_y()
{
    if (cards.size() == 0)
        return -1;
    return data->loop->SCREEN_HEIGHT - an::CARD_HEIGHT + CardHand::DROP;
}

} // namespace game

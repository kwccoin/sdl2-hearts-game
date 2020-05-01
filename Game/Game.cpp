#include "Game.hpp"

#include <string>
#include <vector>

#include "SDL.h"

#include "../AN/ANDeclarations.hpp"
#include "../AN/GameLogic.hpp"
#include "../AN/GameLoop.hpp"
#include "../AN/Helpers.hpp"
#include "../AN/TextureHelper.hpp"
#include "../AN/BitmapFont.hpp"

#include "GameDeclarations.hpp"
#include "GameState.hpp"
#include "MoveButton.hpp"

#include "Extras/ExtraDeclarations.hpp"
#include "Extras/CardSpriteManager.hpp"
#include "Extras/Card.hpp"
#include "Extras/CardHand.hpp"
#include "Extras/OtherHand.hpp"

#define safe_cleanup(x) \
    if (x != NULL)      \
    {                   \
        x->cleanup();   \
        delete x;       \
        x = NULL;       \
    }

namespace game
{

Game::Game(CardSpriteManager *_csm) : an::GameLogic(),
                                      csm(_csm), hand(NULL), btn_move(NULL), gs(NULL), img_table(NULL), bfnt(NULL) {}

Game::~Game()
{
    cleanup();
}

void Game::setup(an::SDLData *d)
{
    GameLogic::setup(d);

    csm->setup(d);

    hand = new CardHand();
    hand->setup(d);

    players.push_back(OtherHand(DIRECTION::NORTH));
    players.push_back(OtherHand(DIRECTION::EAST));
    players.push_back(OtherHand(DIRECTION::WEST));

    btn_move = new MoveButton();
    btn_move->setup(this, d);

    gs = new GameState(this);
    gs->setup(d);

    img_table = data->textures->get("table.png");

    bfnt = new an::BitmapFont();
    bfnt->setup(data, "bitfonts/fnt_bordered.png", 32, 53, " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~", true);
    bfnt->set_scale(1);
    bfnt->set_halign(an::HALIGN::FA_CENTER);
    bfnt->set_valign(an::VALIGN::FA_MIDDLE);
}

void Game::cleanup()
{
    safe_cleanup(bfnt);
    safe_cleanup(gs);
    players.clear();
    safe_cleanup(btn_move);
    safe_cleanup(hand);
    csm = NULL;
}

void Game::handleEvent(SDL_Event *e)
{
    // Handle events
    if (e->type == SDL_QUIT)
        return;

    if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_r && gs->is_over())
    {
        gs->cleanup();
        gs->setup(data);
    }
    else
        gs->handleEvent(e);
}

void Game::update()
{
    gs->update();
}

void Game::render()
{
    an::renderTexture(data, img_table, NULL, NULL);

    hand->render(data, csm);
    for (auto it = players.begin(); it != players.end(); it++)
        it->render(data, csm);
    btn_move->render(data);

    gs->render(data, csm);
}

an::BitmapFont *Game::g_bfnt()
{
    return bfnt;
}

CardHand *Game::g_hand()
{
    return hand;
}

std::vector<OtherHand> *Game::g_players()
{
    return &players;
}

MoveButton *Game::g_btn_move()
{
    return btn_move;
}

} // namespace game

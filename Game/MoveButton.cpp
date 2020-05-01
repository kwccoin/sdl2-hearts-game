#include "MoveButton.hpp"

#include <string>

#include "SDL.h"

#include "../AN/ANDeclarations.hpp"
#include "../AN/Helpers.hpp"
#include "../AN/TextureHelper.hpp"
#include "../AN/GameLoop.hpp"
#include "../AN/BitmapFont.hpp"

#include "GameDeclarations.hpp"
#include "Game.hpp"

#include "Extras/ExtraDeclarations.hpp"
#include "Extras/OtherHand.hpp"

namespace game
{

MoveButton::MoveButton() : visible(false), msg(""), g(NULL), bfnt(NULL),
                           color_r(255), color_g(255), color_b(255), tex(NULL),
                           cx(0), cy(0), x(0), y(0), w(0), h(0) {}

MoveButton::~MoveButton()
{
    cleanup();
}

void MoveButton::setup(Game *_g, an::SDLData *d)
{
    g = _g;

    tex = d->textures->get("move_button.png");
    if (tex == NULL)
        return;

    SDL_QueryTexture(tex, NULL, NULL, &w, &h);

    cx = d->loop->SCREEN_WIDTH / 2;
    cy = d->loop->SCREEN_HEIGHT / 2 + OtherHand::CENTER_OFFSET + an::CARD_WIDTH;
    x = cx - w / 2;
    y = cy - h / 2;
}

void MoveButton::cleanup()
{
    if (tex != NULL)
        SDL_SetTextureColorMod(tex, 255, 255, 255);
    tex = NULL;
}

void MoveButton::render(an::SDLData *d)
{
    if (!visible)
        return;

    an::renderTexture(d, tex, x, y, NULL);

    if (bfnt == NULL)
        bfnt = g->g_bfnt();
    bfnt->renderString(msg, cx, cy);
}

bool MoveButton::was_clicked(int mx, int my)
{
    return mx >= x && mx <= x + w && my >= y && my <= y + h;
}

void MoveButton::set_color(Uint8 r, Uint8 g, Uint8 b)
{
    if (color_r == r && color_g == g && color_b == b)
        return;

    color_r = r;
    color_g = g;
    color_b = b;
    SDL_SetTextureColorMod(tex, color_r, color_g, color_b);
}

} // namespace game

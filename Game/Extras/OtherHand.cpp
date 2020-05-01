#include "OtherHand.hpp"

#include <vector>
#include <cstdlib>

#include "SDL.h"

#include "../../AN/ANDeclarations.hpp"
#include "../../AN/GameLoop.hpp"
#include "../../AN/Helpers.hpp"

#include "ExtraDeclarations.hpp"
#include "SomeHand.hpp"
#include "CardSpriteManager.hpp"
#include "CardHand.hpp"
#include "Card.hpp"

#include "../GameDeclarations.hpp"
#include "../GameState.hpp"

namespace game
{

const int OtherHand::DROP = 150;
const int OtherHand::SPACING = CardHand::SPACING;
const int OtherHand::SPACING_SIDES = OtherHand::SPACING / 2;
const int OtherHand::CENTER_OFFSET = (CardHand::DROP - OtherHand::DROP) / 2;

OtherHand::OtherHand(DIRECTION _dir) : SomeHand(), dir(_dir)
{
    validate_direction(dir);
}

OtherHand::~OtherHand() {}

void OtherHand::render(an::SDLData *d, CardSpriteManager *csm)
{
    SDL_Texture *tex = csm->get_back();
    const int n = cards.size();
    if (tex == NULL || n == 0)
        return;

    const int sw = d->loop->SCREEN_WIDTH;
    const int sh = d->loop->SCREEN_HEIGHT;

    int sx, sy, dx, dy;
    double angle;
    sx = sy = dx = dy = 0;
    angle = 0.0;

    switch (dir)
    {
    case DIRECTION::NORTH:
        sx = sw / 2 + ((n - 1) * OtherHand::SPACING) / 2;
        sy = an::CARD_HEIGHT / 2 - OtherHand::DROP;
        dx = -OtherHand::SPACING;
        dy = 0;
        angle = 180;
        break;
    case DIRECTION::EAST:
        sx = sw - an::CARD_HEIGHT / 2 + OtherHand::DROP;
        sy = sh / 2 + OtherHand::CENTER_OFFSET + ((n - 1) * OtherHand::SPACING_SIDES) / 2;
        dx = 0;
        dy = -OtherHand::SPACING_SIDES;
        angle = 270;
        break;
    case DIRECTION::WEST:
        sx = an::CARD_HEIGHT / 2 - OtherHand::DROP;
        sy = sh / 2 + OtherHand::CENTER_OFFSET - ((n - 1) * OtherHand::SPACING_SIDES) / 2;
        dx = 0;
        dy = OtherHand::SPACING_SIDES;
        angle = 90;
        break;
    default:
        return;
    }

    for (int i = 0; i < n; i++)
        renderTexture_centered(d, tex, sx + i * dx, sy + i * dy, NULL, 1.0, angle);
}

void OtherHand::choose_rotation(std::vector<Card> &rotation)
{
    if (chosen)
        return;

    for (int i = 0; i < 3; i++)
    {
        auto it = cards.begin();
        it += std::rand() % cards.size();
        Card c = *it;
        rotation.push_back(c);
        cards.erase(it);
    }
    chosen = true;
}

void OtherHand::choose_card(GameState *gs, std::vector<Card> &choices)
{
    for (auto it = cards.begin(); it != cards.end(); it++)
        if (can_play(gs, *it))
        {
            Card c = *it;
            choices.push_back(c);
            cards.erase(it);
            return;
        }
}

} // namespace game

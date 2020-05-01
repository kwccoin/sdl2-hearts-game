#include "SomeHand.hpp"

#include <vector>

#include "../../AN/ANDeclarations.hpp"

#include "ExtraDeclarations.hpp"
#include "Card.hpp"
#include "CardSpriteManager.hpp"

#include "../GameDeclarations.hpp"
#include "../GameState.hpp"

namespace game
{

SomeHand::SomeHand() : chosen(false), points(0), data(NULL), cards() {}

SomeHand::~SomeHand()
{
    cleanup();
}

void SomeHand::setup(an::SDLData *d)
{
    data = d;

    points = 0;
    chosen = false;
}

void SomeHand::cleanup()
{
    cards.clear();
}

void SomeHand::render(an::SDLData *d, CardSpriteManager *csm) {}

void SomeHand::dealt(Card c)
{
    cards.push_back(c);
}

void SomeHand::place_rotation(std::vector<Card> &rotation)
{
    for (auto it = cards.begin(); it != cards.end();)
    {
        if (it->chosen)
        {
            Card c = *it;
            rotation.push_back(c);
            it = cards.erase(it);
        }
        else
            it++;
    }
    chosen = true;
}

void SomeHand::take_rotation(std::vector<Card> &rotation)
{
    for (auto it = rotation.begin(); it != rotation.end();)
    {
        Card c = *it;
        cards.push_back(c);
        it = rotation.erase(it);
    }
}

bool SomeHand::has_two_clubs()
{
    for (auto it = cards.begin(); it != cards.end(); it++)
        if (it->g_suit() == SUIT::CLUBS && it->g_value() == FACE::TWO)
            return true;
    return false;
}

void SomeHand::play_card(std::vector<Card> &choices)
{
    for (auto it = cards.begin(); it != cards.end(); it++)
        if (it->chosen)
        {
            Card c = *it;
            choices.push_back(c);
            cards.erase(it);
            return;
        }
}

bool SomeHand::can_play(GameState *gs, Card &c)
{
    return gs->can_play(cards, c);
}

} // namespace game

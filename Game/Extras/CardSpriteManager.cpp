#include "CardSpriteManager.hpp"

#include <string>
#include <map>
#include <vector>

#include "SDL.h"

#include "../../AN/ANDeclarations.hpp"
#include "../../AN/TextureHelper.hpp"

#include "ExtraDeclarations.hpp"
#include "Card.hpp"

namespace game
{

CardSpriteManager::CardSpriteManager() : sprites(), card_back(NULL) {}

CardSpriteManager::~CardSpriteManager()
{
    cleanup();
}

void CardSpriteManager::setup(an::SDLData *d)
{
    std::vector<Card> deck;
    Card::generate_deck(deck);
    for (auto it = deck.begin(); it != deck.end(); it++)
        sprites[it->g_suit()][it->g_value()] = d->textures->get(it->get_texture_name());
    card_back = d->textures->get("Cards/cardBack_green4.png");
}

void CardSpriteManager::cleanup()
{
    card_back = NULL;
}

SDL_Texture *CardSpriteManager::get_texture(Card c)
{
    auto it_s = sprites.find(c.g_suit());
    if (it_s == sprites.end())
        return NULL;

    auto it_s_sec = it_s->second;
    auto it_f = it_s_sec.find(c.g_value());
    if (it_f == it_s_sec.end())
        return NULL;

    return it_f->second;
}

SDL_Texture *CardSpriteManager::get_back()
{
    return card_back;
}

} /* namespace game */

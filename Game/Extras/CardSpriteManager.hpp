#ifndef GAME_EXTRAS_CARDSPRITEMANAGER_HPP_
#define GAME_EXTRAS_CARDSPRITEMANAGER_HPP_

#include <map>

#include "SDL.h"

#include "../../AN/ANDeclarations.hpp"
#include "ExtraDeclarations.hpp"

namespace game
{

class CardSpriteManager
{
public:
    CardSpriteManager();
    ~CardSpriteManager();

    void setup(an::SDLData *);
    void cleanup();

    SDL_Texture *get_texture(Card);
    SDL_Texture *get_back();

private:
    std::map<SUIT, std::map<FACE, SDL_Texture *>> sprites;
    SDL_Texture *card_back;
};

} // namespace game

#endif /* GAME_EXTRAS_CARDSPRITEMANAGER_HPP_ */

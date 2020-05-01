#ifndef GAME_GAME_HPP_
#define GAME_GAME_HPP_

#include <vector>

#include "SDL.h"
#include "SDL_ttf.h"

#include "../AN/ANDeclarations.hpp"
#include "../AN/GameLogic.hpp"

#include "GameDeclarations.hpp"
#include "Extras/ExtraDeclarations.hpp"

namespace game {

class Game : public an::GameLogic {
public:
    Game(CardSpriteManager*);
    ~Game();
    void setup(an::SDLData*);
    void cleanup();
    void handleEvent(SDL_Event*);
    void update();
    void render();

    an::BitmapFont* g_bfnt();
    CardHand* g_hand();
    std::vector<OtherHand>* g_players();
    MoveButton* g_btn_move();
private:
    CardSpriteManager *csm;

    CardHand *hand;
    std::vector<OtherHand> players;
    MoveButton *btn_move;

    GameState *gs;
    SDL_Texture *img_table;
    an::BitmapFont *bfnt;
};

}

#endif /* GAME_GAME_HPP_ */

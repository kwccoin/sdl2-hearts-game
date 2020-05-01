#ifndef GAME_MOVEBUTTON_HPP_
#define GAME_MOVEBUTTON_HPP_

#include <string>

#include "SDL.h"

#include "../AN/ANDeclarations.hpp"
#include "GameDeclarations.hpp"

namespace game
{

class MoveButton
{
public:
    MoveButton();
    ~MoveButton();

    void setup(Game *, an::SDLData *);
    void cleanup();

    void render(an::SDLData *);

    bool was_clicked(int, int);
    void set_color(Uint8, Uint8, Uint8);

    bool visible;
    std::string msg;

private:
    Game *g;
    an::BitmapFont *bfnt;

    Uint8 color_r, color_g, color_b;
    SDL_Texture *tex;
    int cx, cy, x, y, w, h;
};

} // namespace game

#endif /* GAME_MOVEBUTTON_HPP_ */

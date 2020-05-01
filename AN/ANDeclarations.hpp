#ifndef AN_ANDECLARATIONS_HPP_
#define AN_ANDECLARATIONS_HPP_

#include <iostream>
#include <string>

#include "SDL.h"

namespace an
{

void logSDLError(std::ostream &os, const std::string msg);
void logSDLError(const std::string msg);

// BitmapFont alignment
enum HALIGN
{
    FA_LEFT = -1,
    FA_CENTER,
    FA_RIGHT
};
enum VALIGN
{
    FA_TOP = -1,
    FA_MIDDLE,
    FA_BOTTOM
};

const Uint32 FRAME_DELTA = 1000 / 30;

const int CARD_WIDTH = 140;
const int CARD_HEIGHT = 190;

class BitmapFont;
class FontHelper;
class GameLogic;
class GameLoop;
class TextureHelper;

struct SDLData
{
    SDL_Window *win;
    SDL_Renderer *ren;
    TextureHelper *textures;
    FontHelper *fonts;
    GameLoop *loop;

    SDLData(SDL_Window *_win, SDL_Renderer *_ren, TextureHelper *_textures, FontHelper *_fonts, GameLoop *_loop) : win(_win), ren(_ren), textures(_textures), fonts(_fonts), loop(_loop) {}
};

} // namespace an

#endif /* AN_ANDECLARATIONS_HPP_ */

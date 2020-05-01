#ifndef AN_BITMAPFONT_HPP_
#define AN_BITMAPFONT_HPP_

#include <map>
#include <string>

#include "SDL.h"

#include "ANDeclarations.hpp"

namespace an
{

class BitmapFont
{
public:
    BitmapFont();
    ~BitmapFont();
    void setup(SDLData *, const std::string, const int, const int, const std::string, bool);
    void cleanup();
    void set_color(Uint8, Uint8, Uint8);
    void get_color(Uint8 *, Uint8 *, Uint8 *);
    void set_scale(int);
    int get_scale();
    int get_string_width(const std::string);
    int get_string_height(const std::string);
    void set_halign(HALIGN);
    HALIGN get_halign();
    void set_valign(VALIGN);
    VALIGN get_valign();
    void renderString(const std::string, const int, const int);

private:
    SDLData *data;
    SDL_Texture *tex;
    int WIDTH, HEIGHT;
    int cWidth, cHeight;
    SDL_Rect *def_pos;
    std::map<char, SDL_Rect *> *characters;
    int scale;
    HALIGN halign;
    VALIGN valign;
};

} // namespace an

#endif /* AN_BITMAPFONT_HPP_ */

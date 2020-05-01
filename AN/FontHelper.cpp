#include "FontHelper.hpp"

#include <iostream>
#include <map>
#include <utility>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

#include "ANDeclarations.hpp"
#include "Helpers.hpp"

namespace an
{

FontHelper::FontHelper() : data(NULL)
{
    fonts = new std::map<std::pair<const std::string, const int>, TTF_Font *>();
}

FontHelper::~FontHelper()
{
    cleanup();
}

void FontHelper::setup(SDLData *d)
{
    data = d;
}

void FontHelper::cleanup()
{
    if (fonts != NULL)
    {
        for (auto it = fonts->begin(); it != fonts->end(); it++)
            TTF_CloseFont((*fonts)[it->first]);
        fonts->clear();
        delete fonts;
        fonts = NULL;
    }
}

TTF_Font *FontHelper::get(const std::string file, const int size)
{
    std::pair<const std::string, const int> ind(file, size);
    if (fonts->find(ind) == fonts->end())
    {
        TTF_Font *font = TTF_OpenFont(("./res/fonts/" + file).c_str(), size);
        (*fonts)[ind] = font;

        // Failed?
        if (font == NULL)
            logSDLError("TTF_OpenFont");
    }
    return (*fonts)[ind];
}

bool FontHelper::loadFailed()
{
    for (auto it = fonts->begin(); it != fonts->end(); it++)
    {
        if (it->second == NULL)
            return true;
    }
    return false;
}

} // namespace an

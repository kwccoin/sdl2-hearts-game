#ifndef AN_FONTHELPER_HPP_
#define AN_FONTHELPER_HPP_

#include <map>
#include <utility>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

#include "ANDeclarations.hpp"

namespace an
{

class FontHelper
{
public:
    FontHelper();
    ~FontHelper();
    void setup(SDLData *);
    void cleanup();
    TTF_Font *get(const std::string, const int);
    bool loadFailed();

private:
    SDLData *data;
    std::map<std::pair<const std::string, const int>, TTF_Font *> *fonts;
};

} // namespace an

#endif /* AN_FONTHELPER_HPP_ */

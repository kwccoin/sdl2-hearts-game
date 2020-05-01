#ifndef AN_TEXTUREHELPER_HPP_
#define AN_TEXTUREHELPER_HPP_

#include <string>
#include <map>

#include "SDL.h"

#include "ANDeclarations.hpp"

namespace an
{

class TextureHelper
{
public:
    TextureHelper();
    ~TextureHelper();
    void setup(SDLData *);
    void cleanup();
    SDL_Texture *loadTexture(const std::string);
    SDL_Texture *get(const std::string);
    bool loadFailed();

private:
    SDLData *data;
    std::map<const std::string, SDL_Texture *> *textures;
};

} // namespace an

#endif /* AN_TEXTUREHELPER_HPP_ */

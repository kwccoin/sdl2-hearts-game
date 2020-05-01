#include "TextureHelper.hpp"

#include <string>
#include <map>
#include <exception>

#include "SDL.h"
#include "SDL_image.h"

#include "ANDeclarations.hpp"
#include "Helpers.hpp"

namespace an
{

TextureHelper::TextureHelper() : data(NULL), textures(NULL) {}

TextureHelper::~TextureHelper()
{
    cleanup();
}

void TextureHelper::setup(SDLData *d)
{
    textures = new std::map<const std::string, SDL_Texture *>();
    data = d;
}

void TextureHelper::cleanup()
{
    if (textures != NULL)
    {
        int t_w, t_h;
        for (auto it = textures->begin(); it != textures->end(); it++)
        {
            if (SDL_QueryTexture(it->second, NULL, NULL, &t_w, &t_h) == 0)
                SDL_DestroyTexture(it->second);
            else
                logSDLError(it->first);
        }
        textures->clear();
        delete textures;
        textures = NULL;
    }
}

SDL_Texture *TextureHelper::loadTexture(const std::string file)
{
    // Load the texture
    SDL_Texture *texture = IMG_LoadTexture(data->ren, file.c_str());

    // Failed?
    if (texture == NULL)
        logSDLError("IMG_LoadTexture");

    // Return
    return texture;
}

SDL_Texture *TextureHelper::get(const std::string file)
{
    if (textures->find(file) == textures->end())
    {
        SDL_Texture *tex = loadTexture("./res/" + file);
        (*textures)[file] = tex;
        if (tex == NULL)
            std::cout << "TextureHelper::get Error: " << file << std::endl;
    }
    return (*textures)[file];
}

bool TextureHelper::loadFailed()
{
    for (auto it = textures->begin(); it != textures->end(); it++)
    {
        if (it->second == NULL)
            return true;
    }
    return false;
}

} // namespace an

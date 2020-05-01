#ifndef AN_HELPERS_HPP_
#define AN_HELPERS_HPP_

#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

#include "ANDeclarations.hpp"

namespace an {

void renderTexture(SDLData*, SDL_Texture*,
        SDL_Rect*, SDL_Rect*);
void renderTexture(SDLData*, SDL_Texture*,
        int, int, int, int);
void renderTexture(SDLData*, SDL_Texture*,
        int, int, SDL_Rect*);
void renderTexture_centered(SDLData*, SDL_Texture*,
        int, int, SDL_Rect*);

SDL_Texture* createTextureFromString(SDLData*, TTF_Font*, const std::string);

void renderTexture(SDLData*, SDL_Texture*,
        SDL_Rect*, SDL_Rect*, double, double angle=0.0,
        SDL_Point* center=NULL,
        SDL_RendererFlip flip=SDL_FLIP_NONE);
void renderTexture_centered(SDLData*, SDL_Texture*,
        int, int, SDL_Rect*, double, double angle=0.0,
        SDL_RendererFlip flip=SDL_FLIP_NONE);

}

#endif /* AN_HELPERS_HPP_ */

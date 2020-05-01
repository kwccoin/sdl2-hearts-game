#include "Helpers.hpp"

#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "ANDeclarations.hpp"

namespace an
{

void renderTexture(SDLData *data, SDL_Texture *tex,
                   SDL_Rect *dst, SDL_Rect *clip)
{
    SDL_RenderCopy(data->ren, tex, clip, dst);
}

void renderTexture(SDLData *data, SDL_Texture *tex,
                   int x, int y, int w, int h)
{
    // Declare destination rectangle
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;

    // Render
    renderTexture(data, tex, &dst, NULL);
}

void renderTexture(SDLData *data, SDL_Texture *tex,
                   int x, int y, SDL_Rect *clip)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;

    // Get size
    if (clip != NULL)
    {
        dst.w = clip->w;
        dst.h = clip->h;
    }
    else
        SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);

    // Render
    renderTexture(data, tex, &dst, clip);
}

void renderTexture_centered(SDLData *data, SDL_Texture *tex,
                            int x, int y, SDL_Rect *clip)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;

    // Get size
    if (clip != NULL)
    {
        dst.w = clip->w;
        dst.h = clip->h;
    }
    else
        SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);

    // Center
    dst.x -= dst.w / 2;
    dst.y -= dst.h / 2;

    // Render offset
    renderTexture(data, tex, &dst, clip);
}

SDL_Texture *createTextureFromString(SDLData *data, TTF_Font *font, const std::string text)
{
    // Render out to surface
    SDL_Color c = {255, 255, 255, 255};
    SDL_Surface *surf = TTF_RenderText_Solid(font, text.c_str(), c);

    // Error?
    if (surf == NULL)
    {
        logSDLError("TTF_RenderText");
        return NULL;
    }

    // Convert to texture
    SDL_Texture *tex = SDL_CreateTextureFromSurface(data->ren, surf);

    // Free surface
    SDL_FreeSurface(surf);
    surf = NULL;

    // Error?
    if (tex == NULL)
        logSDLError("SDL_CreateTextureFromSurface");

    // Done
    return tex;
}

void renderTexture(SDLData *data, SDL_Texture *tex,
                   SDL_Rect *dst, SDL_Rect *clip, double scale, double angle,
                   SDL_Point *center, SDL_RendererFlip flip)
{
    if (dst != NULL && scale > 0.0)
    {
        dst->w = (int)(dst->w * scale);
        dst->h = (int)(dst->h * scale);
    }
    SDL_RenderCopyEx(data->ren, tex, clip, dst, angle, center, flip);
}

void renderTexture_centered(SDLData *data, SDL_Texture *tex,
                            int x, int y, SDL_Rect *clip, double scale, double angle, SDL_RendererFlip flip)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;

    // Get size
    if (clip != NULL)
    {
        dst.w = clip->w;
        dst.h = clip->h;
    }
    else
        SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);

    if (scale > 0.0)
    {
        dst.w = (int)(dst.w * scale);
        dst.h = (int)(dst.h * scale);
    }

    // Center
    dst.x -= dst.w / 2;
    dst.y -= dst.h / 2;

    renderTexture(data, tex, &dst, clip, 1.0, angle, NULL, flip);
}

} // namespace an

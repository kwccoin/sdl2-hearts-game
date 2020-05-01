#include "BitmapFont.hpp"

#include <map>
#include <string>
#include <stdexcept>
#include <cctype>

#include "SDL.h"

#include "ANDeclarations.hpp"
#include "Helpers.hpp"
#include "TextureHelper.hpp"

namespace an
{

BitmapFont::BitmapFont() : data(NULL), tex(NULL),
                           WIDTH(0), HEIGHT(0),
                           cWidth(0), cHeight(0),
                           def_pos(NULL), scale(1),
                           halign(FA_LEFT), valign(FA_TOP)
{
    characters = new std::map<char, SDL_Rect *>();
}

BitmapFont::~BitmapFont()
{
    cleanup();
}

void BitmapFont::setup(SDLData *d, const std::string file, const int char_width, const int char_height, const std::string chars, bool is_upper)
{
    // Store data
    data = d;

    // Load font texture
    tex = data->textures->get(file);

    // Invalid font? Error
    if (tex == NULL)
        return;

    // Get texture dimensions
    SDL_QueryTexture(tex, NULL, NULL, &WIDTH, &HEIGHT);

    // Calculate character dimensions
    cWidth = char_width;
    cHeight = char_height;
    const int char_num_width = WIDTH / cWidth;
    const int char_num_height = HEIGHT / cHeight;

    // Add characters with positions to map
    char c, cl;
    int x, y;
    SDL_Rect *pos;
    for (unsigned int i = 0; i < chars.size(); i++)
    {
        // Get char and image position
        c = chars[i];
        x = i % char_num_width;
        y = i / char_num_width;

        // Off the bottom?
        if (y > char_num_height)
            break;

        // Already in map?
        if (characters->find(c) != characters->end())
            continue;

        // Create position rectangle
        pos = new SDL_Rect();
        pos->x = x * cWidth;
        pos->y = y * cHeight;
        pos->w = cWidth;
        pos->h = cHeight;

        // Add to map
        (*characters)[c] = pos;

        // Upper-case only?
        cl = std::tolower(c);
        if (is_upper && cl != c)
            (*characters)[cl] = pos;

        // Was space?
        if (c == ' ')
            def_pos = pos;
    }
}

void BitmapFont::cleanup()
{
    if (characters != NULL)
    {
		// TODO: Causes a core dump when uncommented
        // for (auto it = characters->begin(); it != characters->end(); it++)
        // {
        //     delete it->second;
        // }

        characters->clear();
        delete characters;
        characters = NULL;

        // Was deleted already in map loop
        def_pos = NULL;
    }
}

void BitmapFont::set_color(Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetTextureColorMod(tex, r, g, b);
}

void BitmapFont::get_color(Uint8 *r, Uint8 *g, Uint8 *b)
{
    SDL_GetTextureColorMod(tex, r, g, b);
}

void BitmapFont::set_scale(int s)
{
    scale = (s <= 0) ? 1 : s;
}

int BitmapFont::get_scale()
{
    return scale;
}

int BitmapFont::get_string_width(const std::string msg)
{
    const int width = (scale > 1) ? cWidth * scale : cWidth;
    int res = 0, cur = 0;

    char c;
    for (unsigned int i = 0; i < msg.size(); i++)
    {
        c = msg[i];
        if (c == '\n')
        {
            cur = 0;
            continue;
        }
        cur++;
        if (cur > res)
            res = cur;
    }

    return res * width;
}

int BitmapFont::get_string_height(const std::string msg)
{
    const int height = (scale > 1) ? cHeight * scale : cHeight;
    int res = 0;
    bool started = true;

    char c;
    for (unsigned int i = 0; i < msg.size(); i++)
    {
        c = msg[i];
        if (started)
            res++;
        if (c == '\n')
            started = true;
        else
            started = false;
    }

    return res * height;
}

void BitmapFont::set_halign(HALIGN h)
{
    halign = h;
}

HALIGN BitmapFont::get_halign()
{
    return halign;
}

void BitmapFont::set_valign(VALIGN v)
{
    valign = v;
}

VALIGN BitmapFont::get_valign()
{
    return valign;
}

void BitmapFont::renderString(const std::string msg, const int x, const int y)
{
    // Alignment stuff
    int s_height = this->get_string_height(msg);

    // Desination rectangle
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = cWidth;
    dst.h = cHeight;

    // Scale?
    if (scale > 1)
    {
        dst.w *= scale;
        dst.h *= scale;
    }

    char c;
    SDL_Rect *pos;

    // Handle vertical alignment (easy)
    switch (valign)
    {
    case FA_TOP:
        break;
    case FA_MIDDLE:
        dst.y -= s_height / 2;
        break;
    case FA_BOTTOM:
        dst.y -= s_height;
        break;
    }

    // Handle horizontal alignment (hard)
    switch (halign)
    {
    case FA_LEFT:
    { // Easy
        for (unsigned int i = 0; i < msg.size(); i++)
        {
            c = msg[i];
            if (c == '\n')
            {
                dst.x = x;
                dst.y += dst.h;
                continue;
            }
            if (characters->find(c) != characters->end())
                pos = (*characters)[c];
            else
                pos = def_pos;
            if (pos != NULL)
                renderTexture(data, tex, &dst, pos);
            dst.x += dst.w;
        }
        break;
    }
    case FA_CENTER:
    case FA_RIGHT:
    { // Harder
        for (unsigned int i = 0, j = 0; i < msg.size() && j < msg.size(); i = j + 1)
        {
            c = ' ';

            // Find newline (or end)
            for (j = i; j < msg.size() && c != '\n'; j++)
                c = msg[j];

            // Found newline?
            if (c == '\n')
                j--;

            // Align as needed
            dst.x -= dst.w * (j - i) / (halign == FA_RIGHT ? 1 : 2);

            // Print out line
            for (; i < j; i++)
            {
                c = msg[i];
                if (characters->find(c) != characters->end())
                    pos = (*characters)[c];
                else
                    pos = def_pos;
                if (pos != NULL)
                    renderTexture(data, tex, &dst, pos);
                dst.x += dst.w;
            }

            // Next line
            dst.x = x;
            dst.y += dst.h;
        }
        break;
    }
    }
}

} // namespace an

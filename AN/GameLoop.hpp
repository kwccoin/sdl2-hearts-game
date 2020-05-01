#ifndef GAMELOOP_HPP_
#define GAMELOOP_HPP_

#include <string>

#include "SDL.h"

#include "ANDeclarations.hpp"

namespace an
{

class GameLoop
{
public:
    GameLoop(const int, const int, const std::string t = "Hello, World!");
    ~GameLoop();
    bool setup(GameLogic *);
    void cleanup();
    void handleEvents();
    void update();
    void render();
    void frameCap();
    bool is_running();
    void quit();

    SDLData *g_data();

    const int SCREEN_WIDTH, SCREEN_HEIGHT;
    const std::string title;

private:
    bool setup_SDL, setup_SDL_image, setup_SDL_ttf;
    SDL_Window *win;
    SDL_Renderer *ren;
    TextureHelper *textures;
    FontHelper *fonts;

    SDLData *data;

    GameLogic *logic;

    bool running;
    Uint32 frame_time;
};

} // namespace an

#endif /* GAMELOOP_HPP_ */

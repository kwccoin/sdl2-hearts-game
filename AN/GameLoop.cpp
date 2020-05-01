#include "GameLoop.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "ANDeclarations.hpp"
#include "Helpers.hpp"
#include "GameLogic.hpp"
#include "TextureHelper.hpp"
#include "FontHelper.hpp"

namespace an
{

GameLoop::GameLoop(const int SW, const int SH, const std::string t) : SCREEN_WIDTH(SW), SCREEN_HEIGHT(SH), title(t),
                                                                      setup_SDL(false), setup_SDL_image(false), setup_SDL_ttf(false),
                                                                      win(NULL), ren(NULL), textures(NULL), fonts(NULL), data(NULL),
                                                                      logic(NULL), running(false), frame_time(0) {}

GameLoop::~GameLoop()
{
    cleanup();
}

bool GameLoop::setup(GameLogic *g)
{
    // Randomize
    std::srand(std::time(NULL));

    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        logSDLError("SDL_Init");
        return false;
    }
    setup_SDL = true;

    // Setup SDL_image
    int imgFlags = IMG_INIT_PNG;
    if ((IMG_Init(imgFlags) & imgFlags) != imgFlags)
    {
        logSDLError("IMG_Init Error");
        return false;
    }
    setup_SDL_image = true;

    // Setup SDL_ttf
    if (TTF_Init() != 0)
    {
        logSDLError("TTF_Init");
        return false;
    }
    setup_SDL_ttf = true;

    // Open a window
    win = SDL_CreateWindow(title.c_str(),
                           SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                           SCREEN_WIDTH, SCREEN_HEIGHT,
                           SDL_WINDOW_SHOWN);
    if (win == NULL)
    {
        logSDLError("SDL_CreateWindow");
        return false;
    }

    // Create a renderer
    ren = SDL_CreateRenderer(win, -1,
                             SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL)
    {
        logSDLError("SDL_CreateRenderer");
        return false;
    }

    // Initialize resource helpers
    textures = new TextureHelper();
    fonts = new FontHelper();

    // Setup data
    data = new SDLData(win, ren, textures, fonts, this);

    // Setup resource helpers
    textures->setup(g_data());
    fonts->setup(g_data());

    // Setup game logic
    if (g == NULL)
    {
        std::cout << "GameLogic was NULL" << std::endl;
        return false;
    }
    logic = g;
    g->setup(g_data());

    // Check resource helpers
    if (textures->loadFailed())
        return false;
    if (fonts->loadFailed())
        return false;

    // Running
    running = true;

    // Setup successfully
    return true;
}

void GameLoop::cleanup()
{
    running = false;
    if (logic != NULL)
    {
        logic->cleanup();
        logic = NULL;
    }
    if (data != NULL)
    {
        delete data;
        data = NULL;
    }
    if (fonts != NULL)
    {
        fonts->cleanup();
        delete fonts;
        fonts = NULL;
    }
    if (textures != NULL)
    {
        textures->cleanup();
        delete textures;
        textures = NULL;
    }
    if (ren != NULL)
    {
        SDL_DestroyRenderer(ren);
        ren = NULL;
    }
    if (win != NULL)
    {
        SDL_DestroyWindow(win);
        win = NULL;
    }
    if (setup_SDL_ttf)
    {
        TTF_Quit();
        setup_SDL_ttf = false;
    }
    if (setup_SDL_image)
    {
        IMG_Quit();
        setup_SDL_image = false;
    }
    if (setup_SDL)
    {
        SDL_Quit();
        setup_SDL = false;
    }
}

void GameLoop::handleEvents()
{
    // FPS Capping
    frame_time = SDL_GetTicks();

    // Get events
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        // Quit?
        if (e.type == SDL_QUIT)
        {
            running = false;
        }

        // Pass to game
        logic->handleEvent(&e);
    }
}

void GameLoop::update()
{
    if (running)
        logic->update();
}

void GameLoop::render()
{
    if (running)
    {
        // Save current draw color
        Uint8 r, g, b, a;
        SDL_GetRenderDrawColor(ren, &r, &g, &b, &a);

        // Clear renderer black
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        // Restore draw color
        SDL_SetRenderDrawColor(ren, r, g, b, a);

        // Render game
        logic->render();

        // Update the screen
        SDL_RenderPresent(ren);
    }
}

void GameLoop::frameCap()
{
    Uint32 delta = SDL_GetTicks() - frame_time;
    if (delta < FRAME_DELTA)
        SDL_Delay(FRAME_DELTA - delta);
}

bool GameLoop::is_running()
{
    return running;
}

void GameLoop::quit()
{
    running = false;
}

SDLData *GameLoop::g_data()
{
    return data;
}

} // namespace an

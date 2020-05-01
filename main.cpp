#include <iostream>
#include <string>
#include <ctime>

#include "SDL.h"
#include "SDL_image.h"

#include "AN/ANDeclarations.hpp"
#include "AN/Helpers.hpp"
#include "AN/GameLoop.hpp"
#include "AN/GameLogic.hpp"

#include "Game/GameDeclarations.hpp"
#include "Game/Game.hpp"

#include "Game/Extras/ExtraDeclarations.hpp"
#include "Game/Extras/CardSpriteManager.hpp"

int main(int argc, char *args[])
{
    // State
    an::GameLoop *loop = new an::GameLoop(960, 640, "SDL 2.0 Hearts Game");
    game::CardSpriteManager *csm = new game::CardSpriteManager();
    game::Game *game = new game::Game(csm);
    int ret = 1;

    // Setup
    if (loop->setup(game))
    {
        ret = 0;

        // Main loop
        while (loop->is_running())
        {
            loop->handleEvents();
            loop->update();
            loop->render();
            loop->frameCap();
        }
    }

    // Cleanup
    loop->cleanup();
    delete loop;
    csm->cleanup();
    delete csm;
    game->cleanup();
    delete game;

    // Done
    return ret;
}

#include "GameLogic.hpp"

#include "SDL.h"

#include "ANDeclarations.hpp"

namespace an
{

GameLogic::GameLogic() : data(NULL) {}

GameLogic::~GameLogic()
{
    cleanup();
}

void GameLogic::setup(SDLData *d)
{
    data = d;
}

void GameLogic::cleanup() {}

void GameLogic::handleEvent(SDL_Event *event) {}

void GameLogic::update() {}

void GameLogic::render() {}

} // namespace an

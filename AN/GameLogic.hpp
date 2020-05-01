#ifndef AN_GAMELOGIC_HPP_
#define AN_GAMELOGIC_HPP_

#include "SDL.h"

#include "ANDeclarations.hpp"

namespace an
{

class GameLogic
{
public:
    friend class GameLoop;
    GameLogic();
    virtual ~GameLogic();
    virtual void setup(SDLData *);
    virtual void cleanup();
    virtual void handleEvent(SDL_Event *);
    virtual void update();
    virtual void render();

protected:
    SDLData *data;
};

} // namespace an

#endif /* AN_GAMELOGIC_HPP_ */

#include "ANDeclarations.hpp"

#include <iostream>
#include <string>

#include "SDL.h"

namespace an
{

void logSDLError(std::ostream &os, const std::string msg)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
}
void logSDLError(const std::string msg)
{
    logSDLError(std::cout, msg);
}

} // namespace an

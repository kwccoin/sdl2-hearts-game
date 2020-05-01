#ifndef GAME_EXTRAS_OTHERHAND_HPP_
#define GAME_EXTRAS_OTHERHAND_HPP_

#include <vector>

#include "SDL.h"

#include "../../AN/ANDeclarations.hpp"
#include "../GameDeclarations.hpp"

#include "ExtraDeclarations.hpp"
#include "SomeHand.hpp"

namespace game
{

class OtherHand : public SomeHand
{
public:
    static const int DROP;
    static const int SPACING;
    static const int SPACING_SIDES;
    static const int CENTER_OFFSET;

    OtherHand(DIRECTION);
    ~OtherHand();

    void render(an::SDLData *, CardSpriteManager *);

    void choose_rotation(std::vector<Card> &);
    void choose_card(GameState *, std::vector<Card> &);

private:
    DIRECTION dir;
};

} // namespace game

#endif /* GAME_EXTRAS_OTHERHAND_HPP_ */

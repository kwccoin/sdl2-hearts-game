#ifndef GAME_EXTRAS_CARDHAND_HPP_
#define GAME_EXTRAS_CARDHAND_HPP_

#include <vector>

#include "../../AN/ANDeclarations.hpp"
#include "../GameDeclarations.hpp"

#include "ExtraDeclarations.hpp"
#include "SomeHand.hpp"

namespace game
{

class CardHand : public SomeHand
{
public:
    static const int DROP;
    static const int SPACING;
    static const int RAISE;

    CardHand();
    ~CardHand();

    void setup(an::SDLData *);
    void cleanup();

    void clear();
    void reset_choice();
    Card get_choice();

    void render(an::SDLData *, CardSpriteManager *);
    void handleEvent(SDL_Event *);

    int count();

    bool multi_select;

private:
    int start_x();
    int start_y();
};

} // namespace game

#endif /* GAME_EXTRAS_CARDHAND_HPP_ */

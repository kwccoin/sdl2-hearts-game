#ifndef GAME_EXTRAS_SOMEHAND_HPP_
#define GAME_EXTRAS_SOMEHAND_HPP_

#include <vector>

#include "../../AN/ANDeclarations.hpp"
#include "ExtraDeclarations.hpp"
#include "../GameDeclarations.hpp"

namespace game
{

class SomeHand
{
public:
    SomeHand();
    virtual ~SomeHand();

    virtual void setup(an::SDLData *);
    virtual void cleanup();
    virtual void render(an::SDLData *, CardSpriteManager *);

    virtual void dealt(Card);
    virtual void place_rotation(std::vector<Card> &);
    virtual void take_rotation(std::vector<Card> &);
    virtual bool has_two_clubs();
    virtual void play_card(std::vector<Card> &);
    virtual bool can_play(GameState *, Card &);

    bool chosen;
    int points;

protected:
    an::SDLData *data;
    std::vector<Card> cards;
};

} // namespace game

#endif /* GAME_EXTRAS_SOMEHAND_HPP_ */

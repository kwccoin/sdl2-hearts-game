#ifndef GAME_EXTRA_EXTRADECLARATIONS_HPP_
#define GAME_EXTRA_EXTRADECLARATIONS_HPP_

#include <iostream>

namespace game
{

class Card;
class CardHand;
class CardSpriteManager;
class OtherHand;
class SomeHand;

enum class SUIT : char
{
    SPADES = 'S',
    HEARTS = 'H',
    CLUBS = 'C',
    DIAMONDS = 'D',
    NONE = 0
};
bool valid_suit(SUIT &);
void validate_suit(SUIT &);
std::ostream &operator<<(std::ostream &, SUIT &);
std::istream &operator>>(std::istream &, SUIT &);

enum class FACE : char
{
    TWO = '2',
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN = 'T',
    JACK = 'J',
    QUEEN = 'Q',
    KING = 'K',
    ACE = 'A',
    NONE = 0
};
bool valid_face(FACE &);
void validate_face(FACE &);
std::ostream &operator<<(std::ostream &, FACE &);
std::istream &operator>>(std::istream &, FACE &);
bool face_gt(const FACE &, const FACE &);

enum class DIRECTION : int
{
    NORTH = 0,
    EAST,
    WEST,
    SOUTH,
    NONE
};
bool valid_direction(DIRECTION &);
void validate_direction(DIRECTION &);
DIRECTION rotate_direction(DIRECTION);

} // namespace game

#endif /* GAME_EXTRA_EXTRADECLARATIONS_HPP_ */

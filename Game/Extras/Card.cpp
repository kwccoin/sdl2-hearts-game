#include "Card.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "ExtraDeclarations.hpp"

namespace game
{

const Card Card::BLANK = Card();
const std::string Card::NO_TEXTURE = "";

Card::Card(SUIT _suit, FACE _value, bool _chosen) : chosen(_chosen), my_suit(_suit), my_value(_value) {}

Card::Card(SUIT _suit, FACE _value) : Card(_suit, _value, false) {}

Card::Card() : Card(SUIT::NONE, FACE::NONE, false) {}

Card::~Card() {}

std::ostream &operator<<(std::ostream &os, Card &c)
{
    return os << c.my_value << " of " << c.my_suit;
}

std::istream &operator>>(std::istream &is, Card &c)
{
    return is >> c.my_suit >> c.my_value;
}

std::string Card::get_texture_name()
{
    if (!valid_suit(my_suit) || !valid_face(my_value))
        return Card::NO_TEXTURE;

    std::stringstream sb;
    sb << "Cards/card" << my_suit << my_value << ".png";
    return sb.str();
}

SUIT Card::g_suit()
{
    return my_suit;
}

FACE Card::g_value()
{
    return my_value;
}

void Card::generate_deck(std::vector<Card> &deck)
{
    char ms, mv;
    SUIT suit;
    FACE value;
    ms = mv = 0;
    do
    {
        suit = static_cast<SUIT>(ms++);
        mv = 0;
        do
        {
            value = static_cast<FACE>(mv++);
            if (valid_suit(suit) && valid_face(value))
                deck.push_back(Card(suit, value));
        } while (mv != 0);
    } while (ms != 0);
}

int Card::points()
{
    if (my_suit == SUIT::HEARTS)
        return 1;
    if (my_suit == SUIT::SPADES && my_value == FACE::QUEEN)
        return 13;
    return 0;
}

bool operator>(const Card &c, const Card &trick)
{
    if (c.my_suit != trick.my_suit)
        return false;
    return face_gt(c.my_value, trick.my_value);
}

} // namespace game

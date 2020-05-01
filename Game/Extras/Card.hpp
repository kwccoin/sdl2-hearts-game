#ifndef GAME_EXTRAS_CARD_HPP_
#define GAME_EXTRAS_CARD_HPP_

#include <iostream>
#include <string>
#include <vector>

#include "ExtraDeclarations.hpp"

namespace game
{

class Card
{
public:
    static const Card BLANK;
    static const std::string NO_TEXTURE;

    Card(SUIT, FACE, bool);
    Card(SUIT, FACE);
    Card();
    ~Card();

    friend std::ostream &operator<<(std::ostream &, Card &);
    friend std::istream &operator>>(std::istream &, Card &);

    std::string get_texture_name();
    SUIT g_suit();
    FACE g_value();

    static void generate_deck(std::vector<Card> &);
    int points();

    friend bool operator>(const Card &, const Card &);

    bool chosen;

private:
    SUIT my_suit;
    FACE my_value;
};

} // namespace game

#endif /* GAME_EXTRAS_CARD_HPP_ */

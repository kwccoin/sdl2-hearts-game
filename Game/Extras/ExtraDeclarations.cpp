#include "ExtraDeclarations.hpp"

#define face_os_case(x) \
    case FACE::x:       \
        return os << static_cast<char>(FACE::x)

namespace game
{

// SUIT helpers
bool valid_suit(SUIT &s)
{
    switch (s)
    {
    case SUIT::SPADES:
    case SUIT::HEARTS:
    case SUIT::CLUBS:
    case SUIT::DIAMONDS:
        return true;
    default:
        return false;
    }
}
void validate_suit(SUIT &s)
{
    if (!valid_suit(s))
        s = SUIT::NONE;
}
std::ostream &operator<<(std::ostream &os, SUIT &s)
{
    switch (s)
    {
    case SUIT::SPADES:
        return os << "Spades";
    case SUIT::HEARTS:
        return os << "Hearts";
    case SUIT::CLUBS:
        return os << "Clubs";
    case SUIT::DIAMONDS:
        return os << "Diamonds";
    case SUIT::NONE:
        return os << "No Suit";
    default:
        return os << "Unknown Suit";
    }
}
std::istream &operator>>(std::istream &is, SUIT &s)
{
    char c = 0;
    is >> c;
    s = static_cast<SUIT>(c);
    validate_suit(s);
    return is;
}

// FACE helpers
bool valid_face(FACE &f)
{
    switch (f)
    {
    case FACE::TWO:
    case FACE::THREE:
    case FACE::FOUR:
    case FACE::FIVE:
    case FACE::SIX:
    case FACE::SEVEN:
    case FACE::EIGHT:
    case FACE::NINE:
    case FACE::TEN:
    case FACE::JACK:
    case FACE::QUEEN:
    case FACE::KING:
    case FACE::ACE:
        return true;
    default:
        return false;
    }
}
void validate_face(FACE &f)
{
    if (!valid_face(f))
        f = FACE::NONE;
}
std::ostream &operator<<(std::ostream &os, FACE &f)
{
    switch (f)
    {
        face_os_case(TWO);
        face_os_case(THREE);
        face_os_case(FOUR);
        face_os_case(FIVE);
        face_os_case(SIX);
        face_os_case(SEVEN);
        face_os_case(EIGHT);
        face_os_case(NINE);
    case FACE::TEN:
        return os << "10";
        face_os_case(JACK);
        face_os_case(QUEEN);
        face_os_case(KING);
        face_os_case(ACE);
    case FACE::NONE:
        return os << "No Face";
    default:
        return os << "Unknown Face";
    }
}
std::istream &operator>>(std::istream &is, FACE &f)
{
    char c = 0;
    is >> c;
    f = static_cast<FACE>(c);
    validate_face(f);
    return is;
}
bool face_gt(const FACE &f, const FACE &trick)
{
    char c_f = static_cast<char>(f);
    char c_trick = static_cast<char>(trick);

    if (c_trick >= '2' && c_trick <= '9')
    {
        if (c_f >= '2' && c_f <= '9')
            return c_f > c_trick;
        return true;
    }
    else if (c_f >= '2' && c_f <= '9')
        return false;

    switch (trick)
    {
    case FACE::TEN:
        return !(f == FACE::TEN);
    case FACE::JACK:
        return !(f == FACE::TEN || f == FACE::JACK);
    case FACE::QUEEN:
        return f == FACE::KING || f == FACE::ACE;
    case FACE::KING:
        return f == FACE::ACE;
    case FACE::ACE:
    default:
        return false;
    }

    return false;
}

bool valid_direction(DIRECTION &dir)
{
    switch (dir)
    {
    case DIRECTION::NORTH:
    case DIRECTION::EAST:
    case DIRECTION::WEST:
    case DIRECTION::SOUTH:
        return true;
    default:
        return false;
    }
}
void validate_direction(DIRECTION &dir)
{
    if (!valid_direction(dir))
        dir = DIRECTION::NONE;
}
DIRECTION rotate_direction(DIRECTION dir)
{
    switch (dir)
    {
    case DIRECTION::NORTH:
        return DIRECTION::EAST;
    case DIRECTION::EAST:
        return DIRECTION::SOUTH;
    case DIRECTION::SOUTH:
        return DIRECTION::WEST;
    case DIRECTION::WEST:
    default:
        return DIRECTION::NORTH;
    }
}

} // namespace game

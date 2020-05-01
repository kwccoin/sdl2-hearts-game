#include "GameDeclarations.hpp"

#include <cstdlib>
#include <cmath>

namespace game
{

int rand_int(int a, int b)
{
    return a + (rand() % (b - a));
}

double deg2rad(double dir)
{
    static const double pi = 3.14159265358979323846264338327950288;
    static const double conversion = pi / 180.0;
    return dir * conversion;
}

int lengthdir_x(int len, double dir)
{
    return (int)(((double)len) * std::cos(deg2rad(dir)));
}

int lengthdir_y(int len, double dir)
{
    return (int)(((double)len) * std::sin(deg2rad(dir)));
}

} // namespace game

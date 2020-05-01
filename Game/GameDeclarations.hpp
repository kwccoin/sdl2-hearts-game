#ifndef GAME_GAMEDECLARATIONS_HPP_
#define GAME_GAMEDECLARATIONS_HPP_

#include <string>

namespace game
{

class Game;
class GameState;
class MoveButton;

enum class STATE
{
    NONE,
    ANIMATION,
    DEALING_CARDS,
    ROTATION,
    ROTATION_WAITING,
    ROTATION_PERFORM,
    PICK_FIRST,
    CHOOSE_CARD,
    WAIT_TO_CHOOSE,
    WAIT_TO_FINISH,
    NEXT_MOVE,
    END_HAND,
    END_ROUND,
    GAME_OVER,
};

const double CENTER_SCALE = 0.6;
const int ROTATION_DELAY = 30;
const int ROTATION_TIME = 90;
const int ROTATION_HOLD = 30;

int rand_int(int, int);
double deg2rad(double);
int lengthdir_x(int, double);
int lengthdir_y(int, double);

// Messages
const std::string ANIM_BLANK = "";
const std::string ANIM_DEALING_CARDS = "Everyone starts\nWith 13 cards";
const std::string ANIM_ROTATION = "Choose three cards\nTo pass along";
const std::string ANIM_ROTATION_PERFORM = "Cards will now be\nExchanged clock-wise";

const std::string STR_ROTATION_PICK = "Pick three\nCards";
const std::string STR_ROTATION_CONFIRM = "Confirm\nSelection";
const std::string STR_WAIT_TURN = "Wait for\nTurn";
const std::string STR_CHOOSE_PICK = "Choose a\nValid card";
const std::string STR_CHOOSE_CONFIRM = "Play this\nCard";
const std::string STR_RESTART = "Press <R> to play again";

} // namespace game

#endif /* GAME_GAMEDECLARATIONS_HPP_ */

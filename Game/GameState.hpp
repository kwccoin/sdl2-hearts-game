#ifndef GAME_GAMESTATE_HPP_
#define GAME_GAMESTATE_HPP_

#include <vector>

#include "SDL.h"

#include "../AN/ANDeclarations.hpp"
#include "GameDeclarations.hpp"
#include "Extras/ExtraDeclarations.hpp"

namespace game
{

class GameState
{
public:
    GameState(Game *);
    ~GameState();

    void setup(an::SDLData *);
    void cleanup();

    void handleEvent(SDL_Event *);
    void update();
    void render(an::SDLData *, CardSpriteManager *);
    bool can_play(std::vector<Card> &, Card &);
    bool is_over();

private:
    void generate_deck();
    void draw_center(an::SDLData *, int, SDL_Texture *, bool);
    bool is_broken(std::vector<Card> &);
    void end_round();
    SomeHand *get_somehand(int);
    SomeHand *get_somehand(DIRECTION);
    void draw_arrow(an::SDLData *, int, int);

    Game *g;
    SDL_Texture *tex_arrow;

    STATE state, state_next, state_prev;
    int anim_timer, rounds;
    DIRECTION player, starting;
    std::vector<Card> deck;
    std::vector<std::vector<Card>> rotations;
    std::vector<Card> choices;
    bool first_card, hearts_broken;
};

} // namespace game

#endif /* GAME_GAMESTATE_HPP_ */

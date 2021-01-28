#ifndef HEX_GAME_H
#define HEX_GAME_H

#include <memory>
#include <iostream>
#include <hex_board.h>
#include <hex_ai_player.h>
#include <hex_winner.h>

using namespace std;

class hex_game
{
public:
    /*
     * We need to know the board_size
     * and the number of Monte Carlo iterations
     * that we need to perform
     *
     */

    hex_game(short board_size, int num_mc_iterations);
    void init();
    void play();

private:
   short board_size = 5;
   int num_mc_iterations = 1000;
   shared_ptr<hex_board> board;
   shared_ptr<hex_ai_player> ai_player;
   shared_ptr<hex_winner> win;

   hex_value player_sign;
   hex_value ai_player_sign;

   void choose_sign();
   pair<short, short> get_player_next_move();
};

#endif // HEX_GAME_H

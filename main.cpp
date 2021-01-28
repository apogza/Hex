#include <iostream>

#include <hex_board.h>
#include <hex_winner.h>
#include <hex_ai_player.h>
#include <hex_game.h>

using namespace std;


int main()
{
    // the constructor takes two parameters
    // the board size and the number of MC iterations
    // performed by the AI player
    hex_game game(5, 1000);
    game.play();

    return 0;
}

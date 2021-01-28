#ifndef HEX_AI_PLAYER_H
#define HEX_AI_PLAYER_H

#include <hex_node.h>
#include <hex_board.h>
#include <memory>
#include <unordered_map>

using namespace std;

class hex_ai_player
{

public:
    hex_ai_player(shared_ptr<hex_board> board, hex_value sign, int num_mc_iterations);
    pair<short, short> get_next_move();

private:
    shared_ptr<hex_board> board;
    hex_value player_sign;
    int num_mc_iterations;
    shared_ptr<hex_board> eval_board;

    double evaluate_move(pair<short, short> move);
    void fill_eval_board();
};

#endif // HEX_AI_PLAYER_H

#include "hex_ai_player.h"
#include "hex_winner.h"
#include <algorithm>

hex_ai_player::hex_ai_player(shared_ptr<hex_board> board, hex_value sign, int num_mc_iterations)
{
    this->board = board;
    this->player_sign = sign;
    this->num_mc_iterations = num_mc_iterations;
    this->eval_board = shared_ptr<hex_board>(new hex_board(board->size()));
}

/*
 * Evaluate all possible moves
 * and select the one with highest score
 *
 */

pair<short, short> hex_ai_player::get_next_move()
{
    pair<short, short> next_move;
    double move_score = 0;

    for (short i = 0; i < this->board->size(); i++)
    {
        for (short j = 0; j < this->board->size(); j++)
        {
            if (this->board->get_value(i, j) == hex_value::Empty)
            {
                pair<short, short> tmp_move = make_pair(i, j);
                double tmp_score = evaluate_move(next_move);

                if (tmp_score > move_score)
                {
                    next_move = tmp_move;
                    move_score = tmp_score;
                }
            }
        }
    }

    return next_move;
}

/*
 * The method will give a statistical probablity for
 * the AI player to win the game by making this move
 *
 */

double hex_ai_player::evaluate_move(pair<short, short> move)
{
    double num_wins = 0;

    // create a deep copy of the given board

    //shared_ptr<hex_board> tmp_board (new hex_board(this->board->size()));
    for (int i = 0; i < num_mc_iterations; i++)
    {
        // reset the values to the original
        eval_board->copy_board(board);
        // make the move
        eval_board->set_value(move.first, move.second, player_sign);

        fill_eval_board();

        hex_winner winner(eval_board);
        auto winner_result = winner.has_winner();

        if (winner_result.first && winner_result.second == player_sign)
        {
            num_wins += 1;
        }
    }

    return num_wins / num_mc_iterations;
}

/*
 * Fill the board randomly by alternating between x and o signs
 *
 */
void hex_ai_player::fill_eval_board()
{

    // the move by the ai player has been made,
    // continue filling the board with the opponent's sign

    hex_value current_value = (this->player_sign == hex_value::x) ? hex_value::o : hex_value::x;
    vector<pair<short, short>> free_hexes = eval_board->get_free_hexes();

    if (free_hexes.size() == 0)
    {
        return;
    }

    random_shuffle(free_hexes.begin(), free_hexes.end());

    while (free_hexes.size() > 0)
    {
        pair<short, short> move = free_hexes.back();
        free_hexes.pop_back();

        eval_board->set_value(move.first, move.second, current_value);
        current_value = (current_value == hex_value::x) ? hex_value::o : hex_value::x;
    }
}


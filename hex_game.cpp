#include "hex_game.h"

hex_game::hex_game(short board_size, int num_mc_iterations)
{
    this->board_size = board_size;
    this->num_mc_iterations = num_mc_iterations;

    this->init();
}

void hex_game::init()
{
    choose_sign();

    board = shared_ptr<hex_board>(new hex_board(board_size));
    ai_player = shared_ptr<hex_ai_player>(new hex_ai_player(board, ai_player_sign, num_mc_iterations));
    win = shared_ptr<hex_winner>(new hex_winner(board));
}

/*
 * Ask the player choose their sign
 */

void hex_game::choose_sign()
{
    char x = 'c';

    cout << "The player with sign x needs to build a path vertically." << endl;
    cout << "The player with sign o needs to build a path horizontally." << endl;

    do
    {
        cout << "Please choose sign x or o: ";
        cin >> x;
        cout << endl;
    }
    while (x != 'x' && x != 'o');

    if (x == 'x')
    {
        player_sign = hex_value::x;
        ai_player_sign = hex_value::o;
    }
    else
    {
        player_sign = hex_value::o;
        ai_player_sign = hex_value::x;
    }
}

/*
 * Ask the player to make their next move
 */

pair<short, short> hex_game::get_player_next_move()
{
    short row;
    short col;
    bool is_input_valid = false;

    board->print();

    do
    {
        cout << "Select row: ";
        cin >> row;
        is_input_valid = row > 0 && row <= board_size;
    }
    while(!is_input_valid);

    is_input_valid = false;
    do
    {
        cout << "Select col: ";
        cin >> col;
        is_input_valid = col > 0 && col <= board_size;
    }
    while(!is_input_valid);

    return make_pair(row - 1, col - 1);
}

/*
 * This is the method that captures the game play.
 * The human player always plays first. Then it is the AI player turn
 * The game continues until there is a winner.
 * There is always a winner in Hex.
 *
 */
void hex_game::play()
{
    bool has_winner = false;
    hex_value winner = hex_value::Empty;

    while (!has_winner)
    {
        bool is_player_move_valid = false;
        while(!is_player_move_valid)
        {
            pair<short, short> player_move = get_player_next_move();
            is_player_move_valid = board->set_value(player_move.first, player_move.second, player_sign);
        }

        cout << "Your opponent is thinking..." << endl;
        pair<short, short> ai_player_move = ai_player->get_next_move();

        board->set_value(ai_player_move.first, ai_player_move.second, ai_player_sign);
        pair<bool, hex_value> win_result = win->has_winner();

        has_winner = win_result.first;
        winner = win_result.second;
    }

    board->print();

    if (winner == player_sign)
    {
        cout << "You win!" << endl;
    }

    if (winner == ai_player_sign)
    {
        cout << "AI player wins" << endl;
    }
}

#include <iostream>

#include <hex_board.h>
#include <hex_winner.h>

using namespace std;

void test_vertical_win()
{
    cout << "Testing vertical win" << endl;

    shared_ptr<hex_board> board(new hex_board(11));
    shared_ptr<hex_winner> hex_win(new hex_winner(board));

    board->set_value(0, 3, hex_value::x);
    board->set_value(1, 3, hex_value::x);
    board->set_value(2, 3, hex_value::x);
    board->set_value(3, 3, hex_value::x);
    board->set_value(4, 2, hex_value::x);
    board->set_value(5, 2, hex_value::x);
    board->set_value(5, 3, hex_value::x);
    board->set_value(6, 3, hex_value::x);

    cout << "Board:" << endl;
    board->print();

    auto win_result = hex_win->has_winner();
    if (win_result.first)
    {
        cout << "Winner: ";
        board->print_node_value(win_result.second);
    }
    else
    {
        cout << "No winner";
    }

    cout << endl;
}

void test_horizontal_win()
{
    cout << "Testing horizontal win" << endl;

    shared_ptr<hex_board> board(new hex_board(11));
    shared_ptr<hex_winner> hex_win(new hex_winner(board));

    board->set_value(3, 0, hex_value::o);
    board->set_value(3, 1, hex_value::o);
    board->set_value(3, 2, hex_value::o);
    board->set_value(4, 2, hex_value::o);
    board->set_value(4, 4, hex_value::o);
    board->set_value(4, 3, hex_value::o);
    board->set_value(4, 5, hex_value::o);
    board->set_value(4, 6, hex_value::o);

    cout << "Board:" << endl;
    board->print();

    auto win_result = hex_win->has_winner();

    if (win_result.first)
    {
        cout << "Winner: ";
        board->print_node_value(win_result.second);
    }
    cout << endl;
}

void test_user_input()
{
    cout << "Testing user input:" << endl;

    shared_ptr<hex_board> board(new hex_board(11));
    shared_ptr<hex_winner> hex_win(new hex_winner(board));

    board->print();

    cout << "Give me some coordinates to input x on the board." << endl;
    cout << "Type -1 to stop" << endl;

    bool should_loop = true;

    while (should_loop)
    {
        short x, y;
        cout << "X: ";
        cin >> x;


        if (x == -1)
        {
            should_loop = false;
            break;
        }

        cout << "Y: ";
        cin >> y;

        if (y == - 1)
        {
            should_loop = false;
            break;
        };

        if (!board->set_value(x, y, hex_value::x))
        {
            cout << "That's not a legal move!";
        }
    }

    board->print();
}

int main()
{
    test_vertical_win();
    test_horizontal_win();
    test_user_input();

    return 0;
}

#include <iostream>
#include <memory>
#include <stack>

#include "hex_board.h"

hex_board::hex_board(short board_size)
{
    this->board_size = board_size;

    init_nodes();
    init_node_neighbours();
}

short hex_board::size()
{
    return board_size;
}

hex_value hex_board::get_value(short row, short col) const
{
    return this->board[row][col]->get_value();
}

shared_ptr<hex_node> hex_board::get_node(short row, short col)
{
    return this->board[row][col];
}

/*
 * Before setting the value,
 * we first check whether the node is empty
 * The method returns whether the value has been set
 *
 */

bool hex_board::set_value(short row, short col, hex_value value)
{
    if (row >= board_size || col >= board_size)
    {
        return false;
    }

    auto hex_node = this->board[row][col];

    if (hex_node->get_value() == hex_value::Empty)
    {
        this->board[row][col]->set_value(value);
        return true;
    }

    return false;
}

/*
 * It prints the board to the console
 * Each line of nodes is followed by a
 * line of edges. That would only work with monospace fonts
 *
 */

void hex_board::print() const
{
    for (short i = 0; i < board_size; i++)
    {
        for (short k = 0; k <= i; k++)
        {
            cout << "  ";
        }

        // print nodes and horizontal edges
        for (short j = 0; j < board_size; j++)
        {
            print_node_value(board[i][j]->get_value());

            if (j < board_size - 1)
            {
                cout << " - ";
            }
        }

        // print edges below the node
        if (i < board_size - 1)
        {
            cout << endl;

            for (short k = 0; k <= i; k++)
            {
                cout << "  ";
            }

            for (short j = 0; j < board_size; j++)
            {
                if (j > 0)
                {
                    cout << "/";
                }

                cout << " \\ ";
            }
        }

        cout << endl;
    }
}

/*
 * Prints the enum value properly,
 * instead of printing it as an int
 *
 */

void hex_board::print_node_value(hex_value value) const
{
    switch (value)
    {
    case hex_value::o:
        cout << 'o';
        break;
    case hex_value::x:
        cout << 'x';
        break;
    default:
        cout << '.';
        break;
    }
}

/*
 * Create all the nodes - the essence of the board
 * The board is a two dimensional vector.
 * Or said otherwise - a vector of vectors.
 *
 */

void hex_board::init_nodes()
{
    int node_number = 0;
    for (short i = 0; i < board_size; i++)
    {
        this->board.push_back(vector<shared_ptr<hex_node>>());

        for (short j = 0; j < board_size; j++)
        {
            this->board[i].push_back(shared_ptr<hex_node>(new hex_node(i, j, node_number++)));
        }
    }
}

/*
 * Init the neighbours for every node.
 * Treat it as a undirected graph.
 *
 */

void hex_board::init_node_neighbours()
{
    for (short i = 0; i < board_size; i++)
    {
        for (short j = 0; j < board_size; j++)
        {
            shared_ptr<hex_node> node = board[i][j];

            // add edges only if they are within the board boundaries
            try_add_node_neighbours(node, i, j - 1);
            try_add_node_neighbours(node, i - 1 , j);
            try_add_node_neighbours(node, i - 1 , j + 1);
            try_add_node_neighbours(node, i , j + 1);
            try_add_node_neighbours(node, i + 1 , j);
            try_add_node_neighbours(node, i + 1 , j - 1);
        }
    }
}

/*
 * Add all possible neighbours.
 * The only condition is that they have to be on the board.
 *
 */

bool hex_board::try_add_node_neighbours(shared_ptr<hex_node> node, short row, short col)
{
    bool result = false;
    if (row >= 0 && row < board_size
            && col >= 0 && col < board_size)
    {
        node->add_neighbour(board[row][col]);
        result = true;
    }

    return result;
}

pair<bool, hex_value> hex_board::has_winner() const
{
    return make_pair(false, hex_value::Empty);
}

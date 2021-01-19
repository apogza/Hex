#include "hex_winner.h"

/* we need to work with a hex board
 * therefore, it is necessary for the constructor
 */

hex_winner::hex_winner(shared_ptr<hex_board> board)
{
   this->board = board;
}

/*
 * Check for each value whether there is a
 * path connecting opposite sides vertically
 * or horizontally
 *
 */

pair<bool, hex_value> hex_winner::has_winner()
{
    if (is_winner(direction::horizontal, hex_value::o))
    {
        return make_pair(true, hex_value::o);
    }

    if (is_winner(direction::vertical, hex_value::o))
    {
        return make_pair(true, hex_value::o);
    }

    if (is_winner(direction::horizontal, hex_value::x))
    {
        return make_pair(true, hex_value::x);
    }

    if (is_winner(direction::vertical, hex_value::x))
    {
        return make_pair(true, hex_value::x);
    }

    return make_pair(false, hex_value::Empty);
}

/*
 * Finding if there is a winner is traversing
 * the board from left to right and top to bottom
 * to find if there is a connected path
 *
 * Traversing the board horizontally means
 * going through all the edge nodes on the left
 * and try to find a winning path from it.
 * Constructing the path consists of adding all
 * newly visited nodes on a stack and keep popping
 * them until there are no more or we reach the end
 * of the board.
 *
 * Traversing top to bottom is analogous.
 * Therefore, we encapsulate the logic in one method
 * that serves both.
 *
 * Using Dijkstra in this context does not make
 * much sense. All the edges have the same weight.
 * What is more, running Dijsktra on all combinations
 * of opposite edge nodes, would have been quite consuming.
 *
 */

bool hex_winner::is_winner(direction dir, hex_value val)
{
    bool result = false;
    stack<shared_ptr<hex_node>> nodes;
    unordered_set<short> node_filter;

    for (short i = 0; i < board->size() && !result; i++)
    {
        shared_ptr<hex_node> current_node = (dir == direction::horizontal) ?
                    board->get_node(i, 0):
                    board->get_node(0, i);

        if (current_node->get_value() == val)
        {
            shared_ptr<hex_node> checked_node = current_node;

            // add adjacent nodes (neighbours)
            // that we have not added to the stack
            discover_node_neighbours(checked_node, node_filter, nodes, val);

            // keep looping until there are no more nodes to visit
            // or we reach the end of the board
            while (!nodes.empty() && !result)
            {
                result = (dir == direction::horizontal) ?
                            checked_node->get_col() == board->size() - 1:
                            checked_node->get_row() == board->size() - 1;

                if (!result)
                {
                    checked_node = nodes.top();
                    nodes.pop();

                    discover_node_neighbours(checked_node, node_filter, nodes, val);
                }
            }
        }

        // if there is a winning path, stop
        if (result)
        {
            break;
        }
    }

    return result;
}

void hex_winner::discover_node_neighbours(shared_ptr<hex_node> node,
                                          unordered_set<short>& set,
                                          stack<shared_ptr<hex_node>>& stack,
                                          hex_value val)
{
    for (shared_ptr<hex_node> node : node->get_neighbours())
    {
        if (node->get_value() == val && set.count(node->get_node_number()) == 0)
        {
            stack.push(node);
            set.insert(node->get_node_number());
        }
    }
}

#ifndef HEX_WINNER_H
#define HEX_WINNER_H

#include <unordered_set>
#include <stack>

#include <hex_node.h>
#include <hex_board.h>

enum direction { horizontal, vertical };

class hex_winner
{
public:
    hex_winner(shared_ptr<hex_board> board);
    pair<bool, hex_value> has_winner();

private:
    shared_ptr<hex_board> board;
    bool is_winner(direction dir, hex_value val);
    void discover_node_neighbours(shared_ptr<hex_node> node,
                                      unordered_set<short>& set,
                                      stack<shared_ptr<hex_node>>& stack,
                                      hex_value val);
};

#endif // HEX_WINNER_H

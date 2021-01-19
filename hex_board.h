#ifndef HEXBOARD_H
#define HEXBOARD_H

#include <memory>
#include <vector>
#include <hex_node.h>

using namespace std;

class hex_board
{
public:
    hex_board(short board_size);
    short size();
    hex_value get_value(short row, short col) const;
    shared_ptr<hex_node> get_node(short row, short col);

    // if the move is legal, the value is set on the board
    // if not, the method returns false
    bool set_value(short row, short col, hex_value value);

    void print() const;
    void print_node_value(hex_value value) const;
    pair<bool, hex_value> has_winner() const;

private:
    vector<vector<shared_ptr<hex_node>>> board;
    short board_size;
    void init_nodes();
    void init_node_neighbours();
    bool try_add_node_neighbours(shared_ptr<hex_node> node, short row, short col);
    bool is_vertical_winner(hex_value val);
    bool is_horizontal_winner(hex_value val);
};

#endif // HEXBOARD_H

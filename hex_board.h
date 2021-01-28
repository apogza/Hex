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
    vector<pair<short, short>> get_free_hexes() const;

    void copy_board(shared_ptr<hex_board> copy_board);

    void print() const;
    void print_node_value(hex_value value) const;
    pair<bool, hex_value> has_winner() const;

private:
    vector<vector<shared_ptr<hex_node>>> board;
    short board_size;
    int num_filled_hexes = 0;
    void init_nodes();
    void init_node_neighbours();
    bool try_add_node_neighbours(shared_ptr<hex_node> node, short row, short col);
};

#endif // HEXBOARD_H

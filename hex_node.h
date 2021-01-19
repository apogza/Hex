#ifndef HEX_NODE_H
#define HEX_NODE_H

#include <memory>
#include <vector>

using namespace std;

enum hex_value { Empty, x, o };

class hex_node
{
public:
    hex_node(short row, short col, int node_number);
    void set_value(hex_value value);
    hex_value get_value() const;
    void add_neighbour(shared_ptr<hex_node> neighbour);
    vector<shared_ptr<hex_node>> get_neighbours();
    short get_row() const;
    short get_col() const;
    short get_node_number() const;
private:
    hex_value value;
    short row;
    short col;
    int node_number;
    vector<shared_ptr<hex_node>> neighbours;
};

#endif // HEX_NODE_H

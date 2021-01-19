#include "hex_node.h"
#include <iostream>

/*
 * A node knows if its row, col and node number.
 * In addition, it is a recursive data structure -
 * it has a collection of its neighbours.
 */

hex_node::hex_node(short row, short col, int node_number)
{
    this->row = row;
    this->col = col;
    this->node_number = node_number;
    this->value = hex_value::Empty;
}

hex_value hex_node::get_value() const
{
    return value;
}

short hex_node::get_row() const
{
    return row;
}

short hex_node::get_col() const
{
    return col;
}

short hex_node::get_node_number() const
{
    return node_number;
}

void hex_node::set_value(hex_value value)
{
    this->value = value;
}

void hex_node::add_neighbour(shared_ptr<hex_node> neighbour)
{
    neighbours.push_back(neighbour);
}

/*
 * Using the shared_ptr smart pointer, which deallocates heap memory
 * automatically when the pointer is no longer used anywhere
 *
 */

vector<shared_ptr<hex_node>> hex_node::get_neighbours()
{
    return neighbours;
}

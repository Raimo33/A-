/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:39:53 by craimond          #+#    #+#             */
/*   Updated: 2024/06/13 14:24:41 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Node.hpp"
#include "headers/Grid.hpp"

using std::array;

Node::Node(const enum e_cell_type type, const int32_t x, const int32_t y) :
	Tile(type, x, y),
	_g_cost(0),
	_h_cost(0),
	_f_cost(0),
	_neighbors() {}

Node::Node(const Tile &src) :
	Tile(src),
	_g_cost(0),
	_h_cost(0),
	_f_cost(0),
	_neighbors() {}

Node::Node(const Node &src) :
	Tile(src),
	_g_cost(src._g_cost),
	_h_cost(src._h_cost),
	_f_cost(src._f_cost),
	_neighbors(src._neighbors) {}

Node::~Node(void) {}

bool	Node::operator==(const Node &other) const { return Cell::operator==(other) && _g_cost == other._g_cost && _h_cost == other._h_cost && _f_cost == other._f_cost; }

float						Node::getCostG(void) const { return _g_cost; }
void						Node::setCostG(const float cost) { _g_cost = cost; }
float						Node::getCostH(void) const { return _h_cost; }
void						Node::setCostH(const float cost) { _h_cost = cost; }
float						Node::getCostF(void) const { return _f_cost; }
void						Node::setCostF(const float cost) { _f_cost = cost; }
const array<Node *, 8>		&Node::getneighbors(void) const { return _neighbors; }
void						Node::setneighbors(const array<Node *, 8> &neighbors) { _neighbors = neighbors; }

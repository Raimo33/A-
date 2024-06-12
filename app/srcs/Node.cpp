/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:39:53 by craimond          #+#    #+#             */
/*   Updated: 2024/06/12 23:45:03 by craimond         ###   ########.fr       */
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
	_neighbours() {}

Node::Node(const Tile &src) :
	Tile(src),
	_g_cost(0),
	_h_cost(0),
	_f_cost(0),
	_neighbours() {}

Node::Node(const Node &src) :
	Tile(src),
	_g_cost(src._g_cost),
	_h_cost(src._h_cost),
	_f_cost(src._f_cost),
	_neighbours(src._neighbours) {}

Node::~Node(void) {}

bool	Node::operator==(const Node &other) const { return Cell::operator==(other) && _g_cost == other._g_cost && _h_cost == other._h_cost && _f_cost == other._f_cost; }

float						Node::getCostG(void) const { return _g_cost; }
void						Node::setCostG(const float g_cost) { _g_cost = g_cost; }
float						Node::getCostH(void) const { return _h_cost; }
void						Node::setCostH(const float h_cost) { _h_cost = h_cost; }
float						Node::getCostF(void) const { return _f_cost; }
void						Node::setCostF(const float f_cost) { _f_cost = f_cost; }
const array<Node *, 8>		&Node::getNeighbours(void) const { return _neighbours; }
void						Node::setNeighbours(const array<Node *, 8> &neighbours) { _neighbours = neighbours; }

void	Node::computeCostG(const Node &start) { _g_cost = computeCost(start); }
void	Node::computeCostH(const Node &end) { _h_cost = computeCost(end); }
void	Node::computeCostF(const Node &start, const Node &end) { _f_cost = computeCost(start) + computeCost(end); }

float	Node::computeCost(const Node &other) const { return Grid::computeDistance(*this, other); }
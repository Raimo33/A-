/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:39:53 by craimond          #+#    #+#             */
/*   Updated: 2024/06/12 18:54:44 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Node.hpp"

using array;

Node::Node(const enum e_cell_type type, const int32_t x, const int32_t y, const array<Node *, 8> &neighbours) :
	Cell(type, x, y),
	_g_cost(0),
	_h_cost(0),
	_f_cost(0),
	_neighbours(neighbours) {}

Node::Node(const Cell &src, const array<Node *, 8> &neighbours) :
	Cell(src),
	_g_cost(0),
	_h_cost(0),
	_f_cost(0),
	_neighbours() {}

Node::Node(const Node &src) :
	Cell(src),
	_g_cost(src._g_cost),
	_h_cost(src._h_cost),
	_f_cost(src._f_cost),
	_neighbours(src._neighbours) {}

Node::~Node(void) {}

int32_t						Node::getCostG(void) const { return _g_cost; }
void						Node::setCostG(const int32_t g_cost) { _g_cost = g_cost; }
int32_t						Node::getCostH(void) const { return _h_cost; }
void						Node::setCostH(const int32_t h_cost) { _h_cost = h_cost; }
int32_t						Node::getCostF(void) const { return _f_cost; }
void						Node::setCostF(const int32_t f_cost) { _f_cost = f_cost; }
const array<Node *, 8>		&Node::getNeighbours(void) const { return _neighbours; }
void						Node::setNeighbours(const array<Node *, 8> &neighbours) { _neighbours = neighbours; }

void	Node::computeCostG(const Node &start) { _g_cost = computeCost(start); }
void	Node::computeCostH(const Node &end) { _h_cost = computeCost(end); }
void	Node::computeCostF(const Node &start, const Node &end) { _f_cost = _g_cost + _h_cost; }

int32_t	Node::computeCost(const Node &other) const
{
	const Vector2D<int32_t>	&other_pos = other.getPos();

	int32_t x_distance = ::abs(_pos.x - other_pos.x);
	int32_t y_distance = ::abs(_pos.y - other_pos.y);
	return x_distance + y_distance;
}
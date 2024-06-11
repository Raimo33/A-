/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:39:53 by craimond          #+#    #+#             */
/*   Updated: 2024/06/11 14:29:21 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Node.hpp"

Node::Node(const enum e_cell type, const uint16_t x, const uint16_t y) :
	Cell(type),
	_g_cost(0),
	_h_cost(0),
	_f_cost(0),
	_pos({x, y}) {}

Node::Node(const Cell &src, const uint16_t x, const uint16_t y) :
	Cell(src),
	_g_cost(0),
	_h_cost(0),
	_f_cost(0),
	_pos({x, y}) {}

Node::Node(const Node &src) :
	Cell(src),
	_g_cost(src._g_cost),
	_h_cost(src._h_cost),
	_f_cost(src._f_cost),
	_pos(src._pos) {}

Node::~Node(void) {}

uint16_t					Node::getCostG(void) const { return _g_cost; }
uint16_t					Node::getCostH(void) const { return _h_cost; }
uint16_t					Node::getCostF(void) const { return _f_cost; }
const Vector2D<uint16_t>	&Node::getPos(void) const { return _pos; }

void	Node::computeCosts(const Node &start, const Node &end)
{
	_g_cost = computeCost(start);
	_h_cost = computeCost(end);
	_f_cost = _g_cost + _h_cost;
}

uint16_t	Node::computeCost(const Node &other) const
{
	const Vector2D<uint16_t>	&other_pos = other.getPos();

	uint16_t x_distance = std::abs(_pos.x - other_pos.x);
	uint16_t y_distance = std::abs(_pos.y - other_pos.y);
	return x_distance + y_distance;
}
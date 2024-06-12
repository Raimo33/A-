/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:39:53 by craimond          #+#    #+#             */
/*   Updated: 2024/06/12 15:42:14 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Node.hpp"

Node::Node(const enum e_cell type, const int32_t x, const int32_t y) :
	Cell(type, x, y),
	_g_cost(0),
	_h_cost(0),
	_f_cost(0) {}

Node::Node(const Cell &src) :
	Cell(src),
	_g_cost(0),
	_h_cost(0),
	_f_cost(0) {}

Node::Node(const Node &src) :
	Cell(src),
	_g_cost(src._g_cost),
	_h_cost(src._h_cost),
	_f_cost(src._f_cost) {}

Node::~Node(void) {}

int32_t					Node::getCostG(void) const { return _g_cost; }
int32_t					Node::getCostH(void) const { return _h_cost; }
int32_t					Node::getCostF(void) const { return _f_cost; }

void	Node::computeCosts(const Node &start, const Node &end)
{
	_g_cost = computeCost(start);
	_h_cost = computeCost(end);
	_f_cost = _g_cost + _h_cost;
}

int32_t	Node::computeCost(const Node &other) const
{
	const Vector2D<int32_t>	&other_pos = other.getPos();

	int32_t x_distance = ::abs(_pos.x - other_pos.x);
	int32_t y_distance = ::abs(_pos.y - other_pos.y);
	return x_distance + y_distance;
}
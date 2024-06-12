/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cell.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:38:46 by craimond          #+#    #+#             */
/*   Updated: 2024/06/12 17:23:50 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Cell.hpp"

Cell::Cell(const e_cell_type type, const int32_t x, const int32_t y) :
	_type(type),
	_pos(x, y) {}

Cell::Cell(const Cell &src) :
	_type(src._type),
	_pos(src._pos) {}

Cell::~Cell(void) {}

bool	Cell::operator==(const Cell &rhs) const { return _pos == rhs._pos && _type == rhs._type; }

const Vector2D<int32_t>	&Cell::getPos(void) const { return _pos; }
e_cell_type					Cell::getType(void) const { return _type; }
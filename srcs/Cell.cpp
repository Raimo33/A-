/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cell.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:38:46 by craimond          #+#    #+#             */
/*   Updated: 2024/06/10 02:51:28 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Cell.hpp"

Cell::Cell(const e_cell type) :
	_type(type),
	_color(cell_colors.at(type)) {}

Cell::Cell(const Cell &src) :
	_type(src._type),
	_color(src._color) {}

Cell::~Cell(void) {}

Cell		&Cell::operator=(const Cell &rhs)
{
	if (this == &rhs)
		return *this;
	_type = rhs._type;
	_color = rhs._color;
	return *this;
}

bool			Cell::operator==(const Cell &rhs) const { return _type == rhs._type; }

void			Cell::set_type(const e_cell type)
{
	_type = type;
	_color = cell_colors.at(type);
}

e_cell			Cell::get_type(void) const { return _type; }
const sf::Color	&Cell::get_color(void) const { return _color; }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cell.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:38:46 by craimond          #+#    #+#             */
/*   Updated: 2024/06/08 15:23:29 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Cell.hpp"

Cell::Cell(void) :
	_type(FREE) {}

Cell::Cell(const e_cell type) :
	_type(type) {}

Cell::Cell(const Cell &src) :
	_type(src._type) {}

Cell::~Cell(void) {}

Cell	&Cell::operator=(const Cell &rhs)
{
	if (this != &rhs)
		return *this;
	_type = rhs._type;
	return *this;
}

void		Cell::set_type(const e_cell type) { _type = type; }
enum e_cell	Cell::get_type(void) const { return _type; }

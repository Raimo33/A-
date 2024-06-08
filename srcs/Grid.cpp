/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:00:10 by craimond          #+#    #+#             */
/*   Updated: 2024/06/08 15:27:33 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Grid.hpp"

using std::vector;

Grid::Grid(const uint16_t n_cols, const uint16_t n_rows, const enum e_cell status) :
	_grid(n_cols, vector<Cell>(n_rows, Cell(status))) {}

Grid::Grid(const Grid &src) :
	_grid(src._grid) {}

Grid::Grid(Grid &&src) :
	_grid(std::move(src._grid)) {}

Grid::~Grid(void) {}

Grid	&Grid::operator=(const Grid &rhs)
{
	if (this != &rhs)
		_grid = rhs._grid;
	return *this;
}

Grid	&Grid::operator=(Grid &&rhs)
{
	if (this != &rhs)
		_grid = std::move(rhs._grid);
	return *this;
}

Cell		&Grid::operator()(const uint16_t x, const uint16_t y) { return _grid[x][y]; }
const Cell	&Grid::operator()(const uint16_t x, const uint16_t y) const { return _grid[x][y]; }

void		Grid::reset(void)
{
	for (auto &col : _grid)
		for (auto &cell : col)
			cell.set_type(FREE);
}
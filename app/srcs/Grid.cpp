/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:00:10 by craimond          #+#    #+#             */
/*   Updated: 2024/06/10 02:26:17 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Grid.hpp"

using std::vector;

Grid::Grid(const uint16_t n_cols, const uint16_t n_rows, const enum e_cell status) :
	_grid(n_cols, vector<Cell>(n_rows, Cell(status))) {}

Grid::~Grid(void) {}

Cell		&Grid::operator()(const uint16_t x, const uint16_t y) { return _grid[x][y]; }
const Cell	&Grid::operator()(const uint16_t x, const uint16_t y) const { return _grid[x][y]; }
uint16_t	Grid::getCols(void) const { return _grid.size(); }
uint16_t	Grid::getRows(void) const { return _grid.empty() ? 0 : _grid[0].size(); }

void		Grid::reset(void)
{
	for (auto &col : _grid)
		for (auto &cell : col)
			cell.set_type(FREE);
}
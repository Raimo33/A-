/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:00:10 by craimond          #+#    #+#             */
/*   Updated: 2024/06/12 16:11:33 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Grid.hpp"

using std::vector;

Grid::Grid(const int32_t n_cols, const int32_t n_rows, const enum e_cell status)
{
	_grid.resize(n_cols);
	for (int32_t x = 0; x < n_cols; x++)
	{
		_grid[x].resize(n_rows);
		for (int32_t y = 0; y < n_rows; y++)
			_grid[x][y] = new Tile(status, x, y);
	}
}

Grid::~Grid(void)
{
	for (auto &col : _grid)
		for (auto &cell : col)
			delete cell;
}

Tile		&Grid::operator()(const int32_t x, const int32_t y) { return *_grid[x][y]; }
const Tile	&Grid::operator()(const int32_t x, const int32_t y) const { return *_grid[x][y]; }
int32_t	Grid::getCols(void) const { return _grid.size(); }
int32_t	Grid::getRows(void) const { return _grid.empty() ? 0 : _grid[0].size(); }

void		Grid::reset(void)
{
	for (auto &col : _grid)
		for (auto &cell : col)
			cell->setType(FREE);
}

void		Grid::insertTile(const Tile &tile)
{
	const Vector2D<int32_t>	&pos = tile.getPos();

	delete _grid[pos.x][pos.y];
	_grid[pos.x][pos.y] = new Tile(tile);
}
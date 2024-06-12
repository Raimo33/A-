/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:00:10 by craimond          #+#    #+#             */
/*   Updated: 2024/06/13 00:31:06 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Grid.hpp"
#include "headers/Node.hpp"
#include "headers/Tile.hpp"

#include <cmath>

using std::array;

Grid::Grid(const int32_t n_cols, const int32_t n_rows, const enum e_cell_type status)
{
	_grid.resize(n_cols);
	for (int32_t x = 0; x < n_cols; x++)
	{
		_grid[x].resize(n_rows);
		for (int32_t y = 0; y < n_rows; y++)
			_grid[x][y] = new Node(status, x, y);
	}
	for (int32_t x = 0; x < n_cols; x++)
		for (int32_t y = 0; y < n_rows; y++)
			setNeighbours(*_grid[x][y]);
}

Grid::~Grid(void)
{
	for (auto &col : _grid)
		for (auto &cell : col)
			delete cell;
}

Cell		&Grid::operator()(const int32_t x, const int32_t y) { return *_grid[x][y]; }
const Cell	&Grid::operator()(const int32_t x, const int32_t y) const { return *_grid[x][y]; }
int32_t		Grid::getCols(void) const { return _grid.size(); }
int32_t		Grid::getRows(void) const { return _grid.empty() ? 0 : _grid[0].size(); }

Cell	&Grid::getStart(void) const
{
	for (auto &col : _grid)
		for (auto &cell : col)
			if (cell->getType() == START)
				return *cell;
	throw StartNotFoundException();
}

Cell	&Grid::getEnd(void) const
{
	for (auto &col : _grid)
		for (auto &cell : col)
			if (cell->getType() == END)
				return *cell;
	throw EndNotFoundException();
}

void	Grid::setNeighbours(Cell &cell) const
{
	array<Node *, 8>		neighbours;
	Node					&node = dynamic_cast<Node &>(cell);
	const Vector2D<int32_t>	&pos = cell.getPos();
	const int32_t			n_cols = getCols();
	const int32_t			n_rows = getRows();
	auto					it = neighbours.begin();

	for (int32_t x = pos.x - 1; x <= pos.x + 1; x++)
	{
		if (x < 0 || x >= n_cols)
			continue;
		for (int32_t y = pos.y - 1; y <= pos.y + 1; y++)
		{
			if (y < 0 || y >= n_rows || (x == pos.x && y == pos.y))
				continue;
			if (_grid[x][y]->getType() == OBSTACLE)
				continue;
			*it++ = dynamic_cast<Node *>(_grid[x][y]);
		}
	}
	node.setNeighbours(neighbours);
}

float	Grid::computeDistance(const Cell &a, const Cell &b)
{
	const Vector2D<int32_t>	&pos_a = a.getPos();
	const Vector2D<int32_t>	&pos_b = b.getPos();
	const int32_t			dx = ::abs(pos_a.x - pos_b.x);
	const int32_t			dy = ::abs(pos_a.y - pos_b.y);

	return sqrt(dx * dx + dy * dy);
}
//TODO fare heuristic

void	Grid::reset(void) //TODO fix
{
	for (auto &col : _grid)
		for (auto &cell : col)
			dynamic_cast<Tile *>(cell)->setType(FREE);
}

void	Grid::insertCell(const Cell &cell)
{
	const Vector2D<int32_t>	&pos = cell.getPos();

	delete _grid[pos.x][pos.y];
	_grid[pos.x][pos.y] = new Node(cell);
}

const char *Grid::StartNotFoundException::what(void) const throw() { return "Start not found"; }
const char *Grid::EndNotFoundException::what(void) const throw() { return "End not found"; }
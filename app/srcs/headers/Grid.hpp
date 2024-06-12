/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:55:47 by craimond          #+#    #+#             */
/*   Updated: 2024/06/12 19:18:38 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <memory>
#include <cstdint>

#include "Cell.hpp"

class Grid
{
	public:
		Grid(const int32_t n_cols, const int32_t n_rows, const enum e_cell_type status = FREE);
		~Grid(void);

		Cell								&operator()(const int32_t x, const int32_t y);
		const Cell							&operator()(const int32_t x, const int32_t y) const;

		int32_t								getCols(void) const;
		int32_t								getRows(void) const;
		Cell								&getStart(void) const;
		Cell								&getEnd(void) const;

		void								reset(void);
		void								insertCell(const Cell &tile);

		static float						computeDistance(const Cell &a, const Cell &b);

		class								StartNotFoundException;
		class								EndNotFoundException;

	private:
		void								setNeighbours(Cell &tile) const;

		std::vector<std::vector<Cell *>>	_grid;
};

class Grid::StartNotFoundException : public std::exception
{
	public:
		virtual const char	*what(void) const throw();
};

class Grid::EndNotFoundException : public std::exception
{
	public:
		virtual const char	*what(void) const throw();
};
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:55:47 by craimond          #+#    #+#             */
/*   Updated: 2024/06/12 16:11:30 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <memory>
#include <cstdint>

#include "Tile.hpp"

class Grid
{
	public:
		Grid(const int32_t n_cols, const int32_t n_rows, const enum e_cell status = FREE);
		~Grid(void);

		Tile		&operator()(const int32_t x, const int32_t y);
		const Tile	&operator()(const int32_t x, const int32_t y) const;

		int32_t		getCols(void) const;
		int32_t		getRows(void) const;
		bool		isEmpty(void) const;

		void		reset(void);
		void		insertTile(const Tile &tile);

	private:
		std::vector<std::vector<Tile *>>	_grid;
};
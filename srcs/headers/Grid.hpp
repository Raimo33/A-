/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:55:47 by craimond          #+#    #+#             */
/*   Updated: 2024/06/08 15:27:36 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <cstdint>

#include "Cell.hpp"

class Grid
{
	public:
		Grid(const uint16_t n_cols, const uint16_t n_rows, const enum e_cell status = FREE);
		Grid(const Grid &src);
		Grid(Grid &&src);
		~Grid(void);

		Grid		&operator=(const Grid &rhs);
		Grid		&operator=(Grid &&rhs);
		Cell		&operator()(const uint16_t x, const uint16_t y);
		const Cell	&operator()(const uint16_t x, const uint16_t y) const;

		void		reset(void);

	private:
		std::vector<std::vector<Cell>>	_grid;
};
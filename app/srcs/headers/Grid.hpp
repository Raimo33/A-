/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:55:47 by craimond          #+#    #+#             */
/*   Updated: 2024/06/10 02:20:20 by craimond         ###   ########.fr       */
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
		Grid(const uint16_t n_cols, const uint16_t n_rows, const enum e_cell status = FREE);
		~Grid(void);

		Cell		&operator()(const uint16_t x, const uint16_t y);
		const Cell	&operator()(const uint16_t x, const uint16_t y) const;

		uint16_t	getCols(void) const;
		uint16_t	getRows(void) const;
		bool		isEmpty(void) const;

		void		reset(void);

	private:
		std::vector<std::vector<Cell>>	_grid;
};
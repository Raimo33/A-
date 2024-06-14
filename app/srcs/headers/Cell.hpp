/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cell.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:35:55 by craimond          #+#    #+#             */
/*   Updated: 2024/06/14 12:45:03 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdint>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "constants.hpp"
#include "Vector2D.hpp"

enum e_cell_type : uint8_t
{
	FREE = 0,
	OBSTACLE = 1,
	START = 2,
	END = 3,
};

class Cell
{
	public:
		Cell(const enum e_cell_type type, const uint16_t x, const uint16_t y);
		Cell(const Cell &src);
		virtual ~Cell(void) = 0;

		bool					operator==(const Cell &rhs) const;

		const Vector2D<uint16_t>	&getPos(void) const;
		enum e_cell_type		getType(void) const;

	protected:
		enum e_cell_type		_type;
		const Vector2D<uint16_t>	_pos;
};
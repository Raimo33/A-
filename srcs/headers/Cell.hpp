/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cell.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:35:55 by craimond          #+#    #+#             */
/*   Updated: 2024/06/08 15:22:17 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdint>
#include <SFML/Graphics.hpp>

enum e_cell : uint8_t
{
	OBSTACLE = 0,
	FREE = 1,
	START = 2,
	END = 3,
};

class Cell
{
	public:
		Cell(void);
		Cell(const enum e_cell type = FREE);
		Cell(const Cell &src);
		~Cell(void);

		Cell				&operator=(const Cell &rhs);

		void				set_type(const enum e_cell type);
		enum e_cell			get_type(void) const;

	private:
		enum e_cell			_type;
};

static const std::unordered_map<e_cell, sf::Color> cell_colors = {
	{FREE, sf::Color::White},
	{OBSTACLE, sf::Color::Black},
	{START, sf::Color::Green},
	{END, sf::Color::Red},
};
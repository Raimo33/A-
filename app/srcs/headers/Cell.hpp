/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cell.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:35:55 by craimond          #+#    #+#             */
/*   Updated: 2024/06/10 02:51:19 by craimond         ###   ########.fr       */
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
	INIT_TYPE = 4 // used in display_grid to display first time
};

class Cell
{
	public:
		Cell(const enum e_cell type = FREE);
		Cell(const Cell &src);
		~Cell(void);

		Cell				&operator=(const Cell &rhs);
		bool				operator==(const Cell &rhs) const;

		enum e_cell			get_type(void) const;
		void				set_type(const enum e_cell type);
		const sf::Color		&get_color(void) const;

	private:
		enum e_cell			_type;
		sf::Color			_color;
};

static const std::unordered_map<e_cell, const sf::Color> cell_colors = {
	{FREE, sf::Color::White},
	{OBSTACLE, sf::Color::Black},
	{START, sf::Color::Green},
	{END, sf::Color::Red},
	{INIT_TYPE, sf::Color::White}
};
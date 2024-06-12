/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tile.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:38:22 by craimond          #+#    #+#             */
/*   Updated: 2024/06/12 18:37:11 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdint>

#include <SFML/Graphics.hpp>
#include "Vector2D.hpp"
#include "Cell.hpp"

class Tile : public Cell
{
	public:
		Tile(const enum e_cell_type type, const int32_t x, const int32_t y);
		Tile(const Cell &src);
		Tile(const Tile &src);
		~Tile(void);

		bool						operator==(const Tile &rhs) const;

		const sf::Color				&getColor(void) const;
		void						setColor(const sf::Color &color);
		const sf::RectangleShape	&getSprite(void) const;
		void						setType(const enum e_cell_type type);

	private:
		sf::RectangleShape			initSprite(void) const;

		sf::Color					_color;
		sf::RectangleShape			_sprite;
};

static const std::unordered_map<e_cell_type, sf::Color> tile_colors = {
	{FREE, WHITE},
	{OBSTACLE, BLACK},
	{START, GREEN},
	{END, RED}
};
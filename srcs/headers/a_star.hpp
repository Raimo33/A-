/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:49:01 by craimond          #+#    #+#             */
/*   Updated: 2024/06/08 13:42:40 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//TODO fix valgrind errors

#include <cstdint>
#include <array>
#include <SFML/Graphics.hpp>
#include <cstring>

constexpr uint8_t TILE_SIZE = 30; // Size of a tile in pixels
constexpr uint8_t COLS = 30; // Number of columns
constexpr uint8_t ROWS = 20; // Number of rows

enum e_cell : uint8_t
{
	OBSTACLE = 0, //needs to stay at 0 for the automatic static initializaton of previous_grid in display_grid
	FREE = 1,
	START = 2,
	END = 3,
};

static const std::unordered_map<e_cell, sf::Color> cell_colors = {
	{FREE, sf::Color::White},
	{OBSTACLE, sf::Color::Black},
	{START, sf::Color::Green},
	{END, sf::Color::Red},
};
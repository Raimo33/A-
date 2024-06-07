/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:08:21 by craimond          #+#    #+#             */
/*   Updated: 2024/06/07 19:04:41 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SFML/Graphics.hpp>
#include "headers/constants.hpp"
#include <iostream>

using std::array, std::pair;

static void				init_window(sf::RenderWindow &window);
static void				display_grid(sf::RenderWindow &window, bool grid[COLS][ROWS]);

int main(void)
{
	sf::RenderWindow	window;
	bool				grid[COLS][ROWS] = {0};
	sf::Vector2i		mouse_pos;
	sf::Vector2i		tile;
	sf::Event			event;

	init_window(window);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				mouse_pos = sf::Mouse::getPosition(window);
				tile.x = mouse_pos.x / TILE_SIZE;
				tile.y = mouse_pos.y / TILE_SIZE;
				grid[tile.x][tile.y] = !grid[tile.x][tile.y];
			}
		}
		display_grid(window, grid);
	}
	window.clear();
}

static void init_window(sf::RenderWindow &window)
{
	constexpr uint16_t win_width = COLS * TILE_SIZE;
	constexpr uint16_t win_height = ROWS * TILE_SIZE;

	window.create(sf::VideoMode(win_width, win_height), "A* Pathfinding");
	window.setFramerateLimit(15);
}

static void	display_grid(sf::RenderWindow &window, bool grid[COLS][ROWS])
{
	sf::RectangleShape	rect(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	sf::Color			color;

	for (uint16_t i = 0; i < COLS; i++)
	{
		for (uint16_t j = 0; j < ROWS; j++)
		{
			color = (grid[i][j] == 0) ? sf::Color::Red : sf::Color::Black;
			rect.setFillColor(color);
			rect.setPosition(i * TILE_SIZE, j * TILE_SIZE);
			window.draw(rect);
		}
	}
	window.display();
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:08:21 by craimond          #+#    #+#             */
/*   Updated: 2024/06/08 11:59:42 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SFML/Graphics.hpp>
#include "headers/constants.hpp"
#include <iostream>
#include <cstring>

using std::array, std::pair;

static void	init_window(sf::RenderWindow &window);
static void	display_grid(sf::RenderWindow &window, bool grid[COLS][ROWS]);
static void	fill_map(sf::RenderWindow &window, bool grid[COLS][ROWS]);

int main(void)
{
	sf::RenderWindow	window;
	bool				grid[COLS][ROWS] = {0};
	sf::Event			event;
	bool				simulation_started = false;

	init_window(window);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				goto cleanup;
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
				simulation_started = true;
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				simulation_started = false;
				std::memset(grid, 0, sizeof(grid));
				display_grid(window, grid);
			}
		}
		if (simulation_started)
			visualize_pathfinding(window, grid); //blocca il programma fino alla fine della simulazione (dopo di puo premere x o r)
		else
			fill_map(window, grid);
	}
cleanup:
	window.clear();
	window.close();
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
			rect.setPosition(i * TILE_SIZE, j * TILE_SIZE); //TODO ottimizzabilissimo (constexpr)
			window.draw(rect);
		}
	}
	window.display();
}

static void	fill_map(sf::RenderWindow &window, bool grid[COLS][ROWS])
{
	const bool				left_click = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	const bool				right_click = sf::Mouse::isButtonPressed(sf::Mouse::Right);
	static sf::Vector2i		mouse_pos;
	static sf::Vector2i		tile; //TODO ottimizzabile con pair

	if (!left_click && !right_click)
		return ;
	mouse_pos = sf::Mouse::getPosition(window);
	tile.x = mouse_pos.x / TILE_SIZE;
	tile.y = mouse_pos.y / TILE_SIZE;
	if (tile.x >= 0 && tile.x < COLS && tile.y >= 0 && tile.y < ROWS)
	{
		grid[tile.x][tile.y] = left_click ? 1 : 0;
		display_grid(window, grid);
	}
}


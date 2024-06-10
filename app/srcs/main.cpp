/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:08:21 by craimond          #+#    #+#             */
/*   Updated: 2024/06/10 13:09:36 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SFML/Graphics.hpp>
#include "headers/Grid.hpp"
#include "headers/Cell.hpp"
#include "headers/constants.hpp"
#include "headers/exceptions.hpp"
#include "headers/utils.hpp"

using std::array, std::pair;

static void	init_window(sf::RenderWindow &window);
static void	display_grid(sf::RenderWindow &window, const Grid &grid);
static void	set_obstacles(sf::RenderWindow &window, Grid &grid);
static void	set_pointed_cell(Grid &grid, const enum e_cell status, sf::RenderWindow &window);
static void	update_start_end(Grid &grid, sf::RenderWindow &window, const enum e_cell status);
static void	visualize_pathfinding(sf::RenderWindow &window, Grid &grid);

int main(void)
{
	sf::RenderWindow	window;
	Grid				grid(COLS, ROWS);
	sf::Event			event;
	bool				simulation_started = false;

	init_window(window);
	display_grid(window, grid);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				goto cleanup;
			if (!simulation_started)
			{
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
					update_start_end(grid, window, START);
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
					update_start_end(grid, window, END);
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
				{
					simulation_started = true;
					visualize_pathfinding(window, grid);
				}
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				simulation_started = false;
				grid.reset();
				display_grid(window, grid);
			}
		}
		if (!simulation_started)
			set_obstacles(window, grid);
	}
cleanup:
	window.close();
}

static void init_window(sf::RenderWindow &window)
{
	window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "A* Pathfinding");
	window.setFramerateLimit(60);
}

static void	display_grid(sf::RenderWindow &window, const Grid &to_draw_grid)
{
	const uint16_t		n_cols = to_draw_grid.getCols();
	const uint16_t		n_rows = to_draw_grid.getRows();
	static Grid			previous_grid(n_cols, n_rows, INIT_TYPE);
	sf::RectangleShape	rect(sf::Vector2f(TILE_SIZE, TILE_SIZE));

	rect.setOutlineThickness(1);
	rect.setOutlineColor(sf::Color::Black);
	for (uint16_t x = 0; x < n_cols; x++)
	{
		for (uint16_t y = 0; y < n_rows; y++)
		{
			const Cell &cell = to_draw_grid(x, y);
			const Cell &previous_cell = previous_grid(x, y);

			if (cell == previous_cell)
				continue;
			rect.setPosition(x * TILE_SIZE, y * TILE_SIZE);
			rect.setFillColor(cell.get_color());
			window.draw(rect);
			previous_grid(x, y) = cell;
		}
	}
	window.display();
}

static void	set_obstacles(sf::RenderWindow &window, Grid &grid)
{
	const bool	left_click = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	const bool	right_click = sf::Mouse::isButtonPressed(sf::Mouse::Right);

	if (!left_click && !right_click)
		return ;

	const enum e_cell	status = (left_click) ? OBSTACLE : FREE;

	set_pointed_cell(grid, status, window);
}

static void update_start_end(Grid &grid, sf::RenderWindow &window, const enum e_cell status)
{
	static Cell			*old_start = nullptr;
	static Cell			*old_end = nullptr;
	const sf::Vector2i	mouse_pos = sf::Mouse::getPosition(window);

	if (status != START && status != END)
		throw InternalErrorException("update_start_end: status must be either START or END");

	if (!is_mouse_in_window(window, mouse_pos))
		return ;

	const sf::Vector2i	tile = {mouse_pos.x / TILE_SIZE, mouse_pos.y / TILE_SIZE};
	Cell				*old_cell = (status == START) ? old_start : old_end;
	Cell				*new_cell = &grid(tile.x, tile.y);

	if (old_cell == new_cell)
		return ;
	new_cell->set_type(status);
	if (old_cell)
		old_cell->set_type(FREE);
	(status == START) ? old_start = new_cell : old_end = new_cell;
	display_grid(window, grid);
}

static void	set_pointed_cell(Grid &grid, const enum e_cell status, sf::RenderWindow &window)
{
	const sf::Vector2i	mouse_pos = sf::Mouse::getPosition(window);

	if (!is_mouse_in_window(window, mouse_pos))
		return ;

	const sf::Vector2i	tile = {mouse_pos.x / TILE_SIZE, mouse_pos.y / TILE_SIZE};
	Cell				&cell = grid(tile.x, tile.y);

	if (cell.get_type() == status)
		return ;
	cell.set_type(status);
	display_grid(window, grid);
}

static void visualize_pathfinding(sf::RenderWindow &window, Grid &grid)
{

	(void)window;
	(void)grid;
	//TODO
}


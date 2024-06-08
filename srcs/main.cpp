/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:08:21 by craimond          #+#    #+#             */
/*   Updated: 2024/06/08 15:39:22 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	grid.reset();
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

static void	display_grid(sf::RenderWindow &window, const Grid &grid)
{
	static Grid			previous_grid(COLS, ROWS, OBSTACLE);
	sf::RectangleShape	rect(sf::Vector2f(TILE_SIZE, TILE_SIZE));

	rect.setOutlineThickness(1);
	rect.setOutlineColor(sf::Color::Black);
	for (uint16_t i = 0; i < COLS; i++)
	{
		for (uint16_t j = 0; j < ROWS; j++)
		{
			if (grid(i, j).get_type() == previous_grid(i, j).get_type())
				continue ;
			rect.setFillColor(cell_colors.at(grid(i, j).get_type()));
			rect.setPosition(i * TILE_SIZE, j * TILE_SIZE);
			printf("Drawing cell at (%d, %d)\n", i, j);
			window.draw(rect);
		}
	}
	previous_grid = grid;
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
	static sf::Vector2i	start_cell_pos = {-1, -1};
	static sf::Vector2i	end_cell_pos = {-1, -1};
	const sf::Vector2i	mouse_pos = sf::Mouse::getPosition(window);

	if (status != START && status != END)
		throw InternalErrorException("update_start_end: status must be either START or END");

	if (!is_mouse_in_window(window, mouse_pos))
		return ;

	const sf::Vector2i	tile = {mouse_pos.x / TILE_SIZE, mouse_pos.y / TILE_SIZE};
	sf::Vector2i		&changed_cell_pos = (status == START) ? start_cell_pos : end_cell_pos;

	printf("DEB1\n");
	grid(changed_cell_pos.x, changed_cell_pos.y).set_type(FREE);
	printf("DEB2\n");
	grid(tile.x, tile.y).set_type(status);
	printf("DEB3\n");
	changed_cell_pos.x = tile.x;
	printf("DEB4\n");
	changed_cell_pos.y = tile.y;
	printf("DEB5\n");
	display_grid(window, grid);
}

static void	set_pointed_cell(Grid &grid, const enum e_cell status, sf::RenderWindow &window)
{
	const sf::Vector2i	mouse_pos = sf::Mouse::getPosition(window);

	if (!is_mouse_in_window(window, mouse_pos))
		return ;

	const sf::Vector2i	tile = {mouse_pos.x / TILE_SIZE, mouse_pos.y / TILE_SIZE};

	grid(tile.x, tile.y).set_type(status);
	display_grid(window, grid);
}

static void visualize_pathfinding(sf::RenderWindow &window, Grid &grid)
{

	(void)window;
	(void)grid;
	//TODO
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:08:21 by craimond          #+#    #+#             */
/*   Updated: 2024/06/12 16:20:55 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO type correctness (uint16_t, uint8_t, Vector2D ovunque)

#include <SFML/Graphics.hpp>
#include "headers/Vector2D.hpp"
#include "headers/Grid.hpp"
#include "headers/Cell.hpp"
#include "headers/constants.hpp"
#include "headers/exceptions.hpp"
#include "headers/utils.hpp"

static void	init_window(sf::RenderWindow &window);
static void	put_tile_on_window(sf::RenderWindow &window, const Tile &tile);
static void	put_grid_on_window(sf::RenderWindow &window, const Grid &grid);
static void	set_obstacles(sf::RenderWindow &window, Grid &grid);
static void	set_pointed_cell(Grid &grid, const enum e_cell status, sf::RenderWindow &window);
static void	update_start_end(Grid &grid, sf::RenderWindow &window, const enum e_cell status);
static void	visualize_pathfinding(sf::RenderWindow &window, Grid &grid);

int main(void)
{
	sf::RenderWindow	window;
	Grid				grid(N_COLS, N_ROWS);
	sf::Event			event;
	bool				simulation_started = false;

	init_window(window);
	put_grid_on_window(window, grid);
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
				put_grid_on_window(window, grid);
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

static void	put_tile_on_window(sf::RenderWindow &window, const Tile &tile)
{
	window.draw(tile.getSprite());
	window.display();
}

static void	put_grid_on_window(sf::RenderWindow &window, const Grid &grid)
{
	for (uint8_t i = 0; i < N_COLS; i++)
		for (uint8_t j = 0; j < N_ROWS; j++)
			window.draw(grid(i, j).getSprite());
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
	static Tile	*old_start = nullptr;
	static Tile	*old_end = nullptr;

	if (status != START && status != END)
		throw InternalErrorException("update_start_end: status must be either START or END");

	const Vector2D<int32_t>		mouse_pos = sf::Mouse::getPosition(window);

	if (!is_mouse_in_window(window, mouse_pos))
		return ;

	const Vector2D<int32_t>	tile_pos = {mouse_pos.x / TILE_SIZE, mouse_pos.y / TILE_SIZE};

	Tile	*old_tile = (status == START) ? old_start : old_end;
	Tile	*new_tile = &grid(tile_pos.x, tile_pos.y);

	new_tile->setType(status);
	put_tile_on_window(window, *new_tile);
	(status == START) ? old_start = new_tile : old_end = new_tile;
	if (!old_tile)
		return ;
	old_tile->setType(FREE);
	put_tile_on_window(window, *old_tile);
}

static void	set_pointed_cell(Grid &grid, const enum e_cell status, sf::RenderWindow &window)
{
	const Vector2D<int32_t>			mouse_pos = sf::Mouse::getPosition(window);

	if (!is_mouse_in_window(window, mouse_pos))
		return ;

	const Vector2D<int32_t>			tile_pos = {mouse_pos.x / TILE_SIZE, mouse_pos.y / TILE_SIZE};
	Tile							&tile = grid(tile_pos.x, tile_pos.y);

	if (tile.getType() == status)
		return ;
	tile.setType(status);
	put_tile_on_window(window, tile);
}

static void visualize_pathfinding(sf::RenderWindow &window, Grid &grid)
{

	(void)window;
	(void)grid;
	//TODO
}


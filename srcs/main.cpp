/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:08:21 by craimond          #+#    #+#             */
/*   Updated: 2024/06/08 13:08:07 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/a_star.hpp"

using std::array, std::pair;

static void	init_window(sf::RenderWindow &window);
static void	display_grid(sf::RenderWindow &window, enum e_cell grid[COLS][ROWS]);
static void	set_obstacles(sf::RenderWindow &window, enum e_cell grid[COLS][ROWS]);
static void	set_pointed_cell(enum e_cell grid[COLS][ROWS], const enum e_cell status, sf::RenderWindow &window);
static void	update_start(enum e_cell grid[COLS][ROWS], sf::RenderWindow &window);
static void	update_end(enum e_cell grid[COLS][ROWS], sf::RenderWindow &window);
static void	visualize_pathfinding(sf::RenderWindow &window, enum e_cell grid[COLS][ROWS]);

int main(void)
{
	sf::RenderWindow	window;
	enum e_cell	grid[COLS][ROWS] = {FREE}; //0 = free, 1 = obstacle, 2 = start, 3 = end, gradients = costs
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
					update_start(grid, window);
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
					update_end(grid, window);
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
				{
					simulation_started = true;
					visualize_pathfinding(window, grid);
				}
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				simulation_started = false;
				std::memset(grid, 0, sizeof(grid));
				display_grid(window, grid);
			}
		}
		if (!simulation_started)
			set_obstacles(window, grid);
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

static void	display_grid(sf::RenderWindow &window, enum e_cell grid[COLS][ROWS])
{
	sf::RectangleShape	rect(sf::Vector2f(TILE_SIZE, TILE_SIZE));

	for (uint16_t i = 0; i < COLS; i++)
	{
		for (uint16_t j = 0; j < ROWS; j++)
		{
			rect.setFillColor(cell_colors.at(grid[i][j]));
			rect.setPosition(i * TILE_SIZE, j * TILE_SIZE); //TODO ottimizzabilissimo (constexpr)
			window.draw(rect);
		}
	}
	window.display();
}

static void	set_obstacles(sf::RenderWindow &window, enum e_cell grid[COLS][ROWS])
{
	const bool	left_click = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	const bool	right_click = sf::Mouse::isButtonPressed(sf::Mouse::Right);

	if (!left_click && !right_click)
		return ;

	const enum e_cell	status = (left_click) ? OBSTACLE : FREE;

	set_pointed_cell(grid, status, window);
}

static void update_start(enum e_cell grid[COLS][ROWS], sf::RenderWindow &window)
{
	static sf::Vector2i	start = {-1, -1};
	const sf::Vector2i	mouse_pos = sf::Mouse::getPosition(window);
	const sf::Vector2i	tile = {mouse_pos.x / TILE_SIZE, mouse_pos.y / TILE_SIZE};

	grid[start.x][start.y] = FREE;
	grid[tile.x][tile.y] = START;
	start.x = tile.x;
	start.y = tile.y;
	display_grid(window, grid);
}

static void update_end(enum e_cell grid[COLS][ROWS], sf::RenderWindow &window)
{
	static sf::Vector2i	end = {-1, -1};
	const sf::Vector2i	mouse_pos = sf::Mouse::getPosition(window);
	const sf::Vector2i	tile = {mouse_pos.x / TILE_SIZE, mouse_pos.y / TILE_SIZE};

	grid[end.x][end.y] = FREE;
	grid[tile.x][tile.y] = END;
	end.x = tile.x;
	end.y = tile.y;
	display_grid(window, grid);
}

static void	set_pointed_cell(enum e_cell grid[COLS][ROWS], const enum e_cell status, sf::RenderWindow &window)
{
	const sf::Vector2i	mouse_pos = sf::Mouse::getPosition(window);
	const sf::Vector2i	tile = {mouse_pos.x / TILE_SIZE, mouse_pos.y / TILE_SIZE};

	grid[tile.x][tile.y] = status;
	display_grid(window, grid);
}

static void visualize_pathfinding(sf::RenderWindow &window, enum e_cell grid[COLS][ROWS])
{

	(void)window;
	(void)grid;
	//TODO
}


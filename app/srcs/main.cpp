/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:08:21 by craimond          #+#    #+#             */
/*   Updated: 2024/06/14 13:41:02 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SFML/Graphics.hpp>
#include <iostream>

#include "headers/Grid.hpp"
#include "headers/pathfinding.hpp"
#include "headers/window_utils.hpp"

using std::array, std::vector, std::unordered_map, std::cerr, std::endl;

void set_obstacles(Grid &grid, sf::RenderWindow &window);
void set_start(Grid &grid, sf::RenderWindow &window);
void set_end(Grid &grid, sf::RenderWindow &window);
void reset_grid(Grid &grid, sf::RenderWindow &window);
void set_pointed_cell(Grid &grid, const enum e_cell_type status, sf::RenderWindow &window);

using Handler = void (*)(Grid&, sf::RenderWindow&);

bool visualization_in_progress = false;

int main(void)
{
	sf::RenderWindow								window;
	Grid											grid(N_COLS, N_ROWS);
	sf::Event										event;
	const unordered_map<sf::Keyboard::Key, Handler>	key_handlers =
	{
		{sf::Keyboard::Key::S, set_start},
		{sf::Keyboard::Key::E, set_end},
		{sf::Keyboard::Key::R, reset_grid},
		{sf::Keyboard::Key::Space, visualize_pathfinding}
	};

	init_window(window);
	put_grid_on_window(window, grid);
	while (window.isOpen() && !visualization_in_progress)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				goto cleanup;
			if (event.type == sf::Event::KeyPressed && key_handlers.find(event.key.code) != key_handlers.end())
			{
				try
				{
					key_handlers.at(event.key.code)(grid, window);
				}
				catch (const std::exception &e)
				{
					cerr << e.what() << endl;
				}
			}
		}
		set_obstacles(grid, window);
		window.display();
	}
cleanup:
	window.close();
}

void	set_start(Grid &grid, sf::RenderWindow &window)
{
	static Tile				*old_start = nullptr; //TODO set to nullptr again when resetgrid is called
	const Vector2D<int16_t>	mouse_pos = sf::Mouse::getPosition(window);

	if (!is_mouse_in_window(window, mouse_pos))
		return ;

	const Vector2D<uint16_t>	pointed_tile_pos = {static_cast<uint16_t>(mouse_pos.x / TILE_SIZE), static_cast<uint16_t>(mouse_pos.y / TILE_SIZE)};
	Tile						*new_start = dynamic_cast<Tile *>(&grid(pointed_tile_pos.x, pointed_tile_pos.y));

	if (new_start->getType() == START)
		return ;
	
	new_start->setType(START);
	put_tile_on_window(window, *new_start);
	if (old_start)
	{
		old_start->setType(FREE);
		put_tile_on_window(window, *old_start);
	}
	old_start = new_start;
}

void	set_end(Grid &grid, sf::RenderWindow &window)
{
	static Tile				*old_end = nullptr; //TODO set to nullptr again when resetgrid is called
	const Vector2D<int16_t>	mouse_pos = sf::Mouse::getPosition(window);

	if (!is_mouse_in_window(window, mouse_pos))
		return ;
	
	const Vector2D<uint16_t>	pointed_tile_pos = {static_cast<uint16_t>(mouse_pos.x / TILE_SIZE), static_cast<uint16_t>(mouse_pos.y / TILE_SIZE)};
	Tile						*new_end = dynamic_cast<Tile *>(&grid(pointed_tile_pos.x, pointed_tile_pos.y));

	if (new_end->getType() == END)
		return ;
	
	new_end->setType(END);
	put_tile_on_window(window, *new_end);
	if (old_end)
	{
		old_end->setType(FREE);
		put_tile_on_window(window, *old_end);
	}
	old_end = new_end;
}

void	reset_grid(Grid &grid, sf::RenderWindow &window)
{
	grid.reset();
	put_grid_on_window(window, grid);
}

void	set_obstacles(Grid &grid, sf::RenderWindow &window)
{
	const bool	left_click = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	const bool	right_click = sf::Mouse::isButtonPressed(sf::Mouse::Right);

	if (!left_click && !right_click)
		return ;

	const Vector2D<int16_t>	mouse_pos = sf::Mouse::getPosition(window);

	if (!is_mouse_in_window(window, mouse_pos))
		return ;

	const Vector2D<uint16_t>	pointed_tile_pos = {static_cast<uint16_t>(mouse_pos.x / TILE_SIZE), static_cast<uint16_t>(mouse_pos.y / TILE_SIZE)};
	Tile						&tile = dynamic_cast<Tile &>(grid(pointed_tile_pos.x, pointed_tile_pos.y));

	(left_click ? tile.setType(OBSTACLE) : tile.reset());
	put_tile_on_window(window, tile);
}

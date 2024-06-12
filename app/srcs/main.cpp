/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:08:21 by craimond          #+#    #+#             */
/*   Updated: 2024/06/12 19:34:05 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO type correctness (uint16_t, uint8_t, Vector2D ovunque)
//TODO splittare il main.cpp in più file
//TODO una volta trovata la migliore path, visualizzarla con la transparency che va e viene (3 celle per volta tipo dallo start fino all'end e poi torna indietro, molto dinamica, in un loop)

#include <SFML/Graphics.hpp>
#include "headers/Vector2D.hpp"
#include "headers/Grid.hpp"
#include "headers/Cell.hpp"
#include "headers/constants.hpp"
#include "headers/exceptions.hpp"
#include "headers/utils.hpp"
#include "headers/Node.hpp"
#include "headers/Tile.hpp"

using std::array, std::vector;

static void	init_window(sf::RenderWindow &window);
static void	put_tile_on_window(sf::RenderWindow &window, const Tile &tile);
static void	put_grid_on_window(sf::RenderWindow &window, const Grid &grid);
static void	set_obstacles(sf::RenderWindow &window, Grid &grid);
static void	set_pointed_cell(Grid &grid, const enum e_cell_type status, sf::RenderWindow &window);
static void	update_start_end(Grid &grid, sf::RenderWindow &window, const enum e_cell_type status);
static void	visualize_pathfinding(sf::RenderWindow &window, Grid &grid);
static const sf::Color compute_color(const int32_t f_cost);

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
	{
		for (uint8_t j = 0; j < N_ROWS; j++)
		{
			const Tile	&tile = dynamic_cast<const Tile &>(grid(i, j));
			window.draw(tile.getSprite());
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

	const enum e_cell_type	status = (left_click) ? OBSTACLE : FREE;

	set_pointed_cell(grid, status, window);
}

static void update_start_end(Grid &grid, sf::RenderWindow &window, const enum e_cell_type status)
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
	Tile	*new_tile = dynamic_cast<Tile *>(&grid(tile_pos.x, tile_pos.y));

	new_tile->setType(status);
	put_tile_on_window(window, *new_tile);
	(status == START) ? old_start = new_tile : old_end = new_tile;
	if (!old_tile)
		return ;
	old_tile->setType(FREE);
	put_tile_on_window(window, *old_tile);
}

static void	set_pointed_cell(Grid &grid, const enum e_cell_type status, sf::RenderWindow &window)
{
	const Vector2D<int32_t>	mouse_pos = sf::Mouse::getPosition(window);

	if (!is_mouse_in_window(window, mouse_pos))
		return ;

	const Vector2D<int32_t>	tile_pos = {mouse_pos.x / TILE_SIZE, mouse_pos.y / TILE_SIZE};
	Tile					&tile = dynamic_cast<Tile &>(grid(tile_pos.x, tile_pos.y));

	if (tile.getType() == status)
		return ;
	tile.setType(status);
	put_tile_on_window(window, tile);
}

static void visualize_pathfinding(sf::RenderWindow &window, Grid &grid)
{
	Node 			&start = dynamic_cast<Node &>(grid.getStart());
	Node 			&end = dynamic_cast<Node &>(grid.getEnd());
	vector<Node *>	open_set, closed_set;

	open_set.push_back(&start);
	while (!open_set.empty())
	{
		// Find the node with the lowest f_cost
		int32_t best_idx = 0;
		int32_t open_set_size = open_set.size();
		for (int32_t i = 0; i < open_set_size; i++)
		{
			open_set[i]->computeCostG(start);
			open_set[i]->computeCostH(end);
			open_set[i]->computeCostF(start, end);
			if (open_set[i]->getCostF() < open_set[best_idx]->getCostF())
				best_idx = i;
		}

		Node &current = *open_set[best_idx];
		// If the current node is the end node, we have found the path
		if (current == end)
			break;

		open_set.erase(open_set.begin() + best_idx);
		closed_set.push_back(&current);

		const array<Node *, 8>	&neighbors = current.getNeighbours();
		for (Node *neighbor : neighbors)
		{
			if (!neighbor)
				continue;
			// If the neighbor is in the closed set, skip it
			if (std::find(closed_set.begin(), closed_set.end(), neighbor) != closed_set.end())
				continue;

			int32_t tentative_g_cost = current.getCostG() + Grid::computeDistance(current, *neighbor);
			
			// If the neighbor is not in the open set, add it
			if (std::find(open_set.begin(), open_set.end(), neighbor) == open_set.end())
				open_set.push_back(neighbor);
			// If the new path to neighbor is shorter or the neighbor is not in the open set
			else if (tentative_g_cost >= neighbor->getCostG())
				continue; // This is not a better path

			// This path is the best until now. Record it
			// neighbor->setParent(current);
			neighbor->setCostG(tentative_g_cost);
			neighbor->computeCostH(end);
			neighbor->computeCostF(start, end);

			Tile			&tile = dynamic_cast<Tile &>(*neighbor); //altrimenti dynamic_cast<Tile &>(grid(neighbor->getPos().x, neighbor->getPos().y));
			const sf::Color	&color = compute_color(neighbor->getCostF()); //TODO maximum f_cost = N_COLS + N_ROWS
			tile.setColor(color);
			put_tile_on_window(window, tile);
		}
	}
	// Optionally, visualize or use the path here
}

static const sf::Color compute_color(const int32_t f_cost)
{
	static const int32_t	max_f_cost = N_COLS + N_ROWS;

	if (f_cost < 0 || f_cost > max_f_cost)
		throw InternalErrorException("compute_color: f_cost out of bounds");
	
	const float	normalized_f_cost = static_cast<float>(f_cost) / static_cast<float>(max_f_cost);
	const int32_t gradient_value = static_cast<int32_t>(normalized_f_cost * 255);
	return GRADIENTS[gradient_value];
}

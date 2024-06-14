/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:50:59 by craimond          #+#    #+#             */
/*   Updated: 2024/06/14 13:27:08 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/pathfinding.hpp"
#include "headers/Node.hpp"
#include "headers/window_utils.hpp"

#include <cfloat>
#include <vector>
#include <array>
#include <chrono>
#include <thread>

using std::vector, std::array;

static void				init_nodes(Grid &grid, Node &start, Node &end);
static void				set_neighbors(Node &node, Grid &grid);
static const sf::Color	compute_color(const float h_cost);
static vector<Node *>	reconstruct_path(Node &end);
static void				display_path(vector<Node *> &path, sf::RenderWindow &window);

void visualize_pathfinding(Grid &grid, sf::RenderWindow &window)
{
	Node 			&start = dynamic_cast<Node &>(grid.getStart());
	Node 			&end = dynamic_cast<Node &>(grid.getEnd());
	vector<Node *>	open_set, closed_set;
	sf::Event		event;

	init_nodes(grid, start, end);
	open_set.push_back(&start);
	while (window.isOpen() && !open_set.empty())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return;
			}
		}
		// Find the node with the lowest f_cost
		uint16_t best_idx = 0;
		uint16_t open_set_size = open_set.size();
		for (uint16_t i = 0; i < open_set_size; i++)
			if (open_set[i]->getCostF() < open_set[best_idx]->getCostF())
				best_idx = i;

		Node &current = *open_set[best_idx];
		if (current == end)
			break;

		open_set.erase(open_set.begin() + best_idx);
		closed_set.push_back(&current);

		const array<Node *, 8>	&neighbors = current.getneighbors();
		for (Node *neighbor : neighbors)
		{
			// If the neighbor is in the closed set, skip it
			if (!neighbor || std::find(closed_set.begin(), closed_set.end(), neighbor) != closed_set.end())
				continue;

			float tentative_g_cost = current.getCostG() + Grid::computeDistance(current, *neighbor);
			// If the neighbor is not in the open set, add it
			if (std::find(open_set.begin(), open_set.end(), neighbor) == open_set.end())
				open_set.push_back(neighbor);
			// If the new path to neighbor is shorter or the neighbor is not in the open set
			else if (tentative_g_cost >= neighbor->getCostG())
				continue; // This is not a better path

			neighbor->setParent(&current);
			neighbor->setCostG(tentative_g_cost);
			neighbor->setCostF(neighbor->getCostG() + neighbor->getCostH());

			if (neighbor == &end)
				continue;
			const sf::Color	&color = compute_color(neighbor->getCostH());
			neighbor->setColor(color);
			put_tile_on_window(window, *neighbor);
			window.display();
			std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
		}
	}
	vector<Node *>	path = reconstruct_path(end);
	display_path(path, window);
}

static void	init_nodes(Grid &grid, Node &start, Node &end)
{
	const uint16_t	n_cols = grid.getCols();
	const uint16_t	n_rows = grid.getRows();

	for (uint16_t x = 0; x < n_cols; x++)
	{
		for (uint16_t y = 0; y < n_rows; y++)
		{
			Node &node = dynamic_cast<Node &>(grid(x, y));
			if (node.getType() == OBSTACLE)
				continue;
			set_neighbors(node, grid);
			node.setCostH(Grid::computeDistance(node, end));
			node.setCostG(FLT_MAX);
			node.setCostF(FLT_MAX);
		}
	}
	start.setCostG(0);
	start.setCostF(start.getCostH());
	start.setParent(nullptr);
}

static void set_neighbors(Node &node, Grid &grid)
{
	array<Node *, 8>			neighbors;
	const Vector2D<uint16_t>	&pos = node.getPos();
	const uint16_t				n_cols = grid.getCols();
	const uint16_t				n_rows = grid.getRows();
	auto						it = neighbors.begin();

	std::fill(neighbors.begin(), neighbors.end(), nullptr);
	for (int16_t x = pos.x - 1; x <= pos.x + 1; x++)
	{
		if (x < 0 || x >= n_cols)
			continue;
		for (int16_t y = pos.y - 1; y <= pos.y + 1; y++)
		{
			if (y < 0 || y >= n_rows || (x == pos.x && y == pos.y))
				continue;
			Cell &cell = grid(x, y);
			if (cell.getType() == OBSTACLE)
				continue;
			*it++ = dynamic_cast<Node *>(&cell);
		}
	}
	node.setneighbors(neighbors);
}

static const sf::Color compute_color(const float h_cost)
{
	static float max_h_cost_encountered = h_cost;

	if (h_cost > max_h_cost_encountered)
		max_h_cost_encountered = h_cost;

	float	clamped_h_cost = std::clamp(h_cost, 0.0f, max_h_cost_encountered);
	float	normalized_h_cost = clamped_h_cost / (max_h_cost_encountered + 1.0f);
	uint8_t	gradient_value = static_cast<uint8_t>(normalized_h_cost * 255.0f);

	return GRADIENTS[gradient_value];
}

static vector<Node *>	reconstruct_path(Node &end)
{
	vector<Node *>	path;
	Node			*current = &end;

	while (current != nullptr)
	{
		path.push_back(current);
		current = current->getParent();
	}
	std::reverse(path.begin(), path.end());
	return path;
}

static void	display_path(vector<Node *> &path, sf::RenderWindow &window)	
{
	for (Node *node : path)
	{
		Tile &tile = dynamic_cast<Tile &>(*node);
		sf::RectangleShape &sprite = tile.getSprite();
		sprite.setOutlineColor(sf::Color::Green);
		sprite.setOutlineThickness(2);
		put_tile_on_window(window, *node);
	}
}

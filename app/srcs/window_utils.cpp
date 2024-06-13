/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:52:00 by craimond          #+#    #+#             */
/*   Updated: 2024/06/14 00:38:26 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/window_utils.hpp"

void	init_window(sf::RenderWindow &window)
{
	window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "A* Pathfinding");
	window.setFramerateLimit(FPS);
}

void	put_tile_on_window(sf::RenderWindow &window, const Tile &tile)
{
	window.draw(tile.getSprite());
}

void	put_grid_on_window(sf::RenderWindow &window, const Grid &grid)
{
	window.clear();
	for (int32_t i = 0; i < N_COLS; i++)
	{
		for (int32_t j = 0; j < N_ROWS; j++)
		{
			const Tile	&tile = dynamic_cast<const Tile &>(grid(i, j));
			window.draw(tile.getSprite());
		}
	}
}

bool	is_mouse_in_window(const sf::RenderWindow &window, const Vector2D<int32_t> &mouse_pos)
{
	const int32_t win_width = window.getSize().x;
	const int32_t win_height = window.getSize().y;

	return (mouse_pos.x >= 0 && mouse_pos.x < win_width && mouse_pos.y >= 0 && mouse_pos.y < win_height);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:53:15 by craimond          #+#    #+#             */
/*   Updated: 2024/06/14 00:37:47 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <SFML/Graphics.hpp>

#include "Grid.hpp"
#include "Tile.hpp"

void	init_window(sf::RenderWindow &window);
void	put_tile_on_window(sf::RenderWindow &window, const Tile &tile);
void	put_grid_on_window(sf::RenderWindow &window, const Grid &grid);
bool	is_mouse_in_window(const sf::RenderWindow &window, const Vector2D<int32_t> &mouse_pos);

extern bool	visualization_in_progress;
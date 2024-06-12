/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:49:01 by craimond          #+#    #+#             */
/*   Updated: 2024/06/12 23:55:06 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//TODO fix valgrind errors

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <array>

constexpr uint8_t						FPS = 15;
constexpr float							TICK_RATE = 1.0f / FPS;
constexpr uint8_t						TILE_SIZE = 30;
constexpr uint8_t						N_COLS = 30;
constexpr uint8_t						N_ROWS = 20;
constexpr int32_t						WIN_WIDTH = N_COLS * TILE_SIZE;
constexpr int32_t						WIN_HEIGHT = N_ROWS * TILE_SIZE;
extern const std::array<sf::Color, 255>	GRADIENTS;
extern const sf::Color					WHITE;
extern const sf::Color					BLACK;
extern const sf::Color					GREEN;
extern const sf::Color					RED;
extern const sf::Color					GRAY;

const std::array<sf::Color, 255>		precompute_gradients(void);

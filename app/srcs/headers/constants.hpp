/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:49:01 by craimond          #+#    #+#             */
/*   Updated: 2024/06/13 20:44:57 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//TODO fix valgrind errors

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <array>

constexpr uint8_t						STEPS_PER_SECOND = 15;
constexpr uint16_t						SLEEP_TIME = 1000 / STEPS_PER_SECOND;
constexpr uint8_t						FPS = 60;
constexpr uint8_t						TILE_SIZE = 20;
constexpr uint8_t						N_COLS = 40;
constexpr uint8_t						N_ROWS = 25;
constexpr int32_t						WIN_WIDTH = N_COLS * TILE_SIZE;
constexpr int32_t						WIN_HEIGHT = N_ROWS * TILE_SIZE;
extern const std::array<sf::Color, 255>	GRADIENTS;

const std::array<sf::Color, 255>		precompute_gradients(void);

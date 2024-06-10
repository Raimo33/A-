/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:49:01 by craimond          #+#    #+#             */
/*   Updated: 2024/06/10 03:00:31 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//TODO fix valgrind errors

#include <cstdint>
#include <array>
#include <SFML/Graphics.hpp>
#include <cstring>

constexpr uint8_t	TILE_SIZE = 30;
constexpr uint8_t	COLS = 30;
constexpr uint8_t	ROWS = 20;
constexpr uint16_t	WIN_WIDTH = COLS * TILE_SIZE;
constexpr uint16_t	WIN_HEIGHT = ROWS * TILE_SIZE;
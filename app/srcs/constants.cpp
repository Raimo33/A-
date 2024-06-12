/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:39:16 by craimond          #+#    #+#             */
/*   Updated: 2024/06/12 14:27:43 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/constants.hpp"

const sf::Color	WHITE = sf::Color(255, 255, 255);
const sf::Color	BLACK = sf::Color(0, 0, 0);
const sf::Color	GREEN = sf::Color(0, 255, 0);
const sf::Color	RED = sf::Color(255, 0, 0);
const sf::Color	GRAY = sf::Color(128, 128, 128);

const std::array<sf::Color, GRADIENT_RESOLUTION>	precompute_gradient(void)
{
	std::array<sf::Color, GRADIENT_RESOLUTION>	colors;

	for (uint8_t i = 0; i < GRADIENT_RESOLUTION; i++)
		colors[i] = sf::Color(i, i, i);
	return (colors);
}
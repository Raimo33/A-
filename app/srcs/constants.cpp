/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:39:16 by craimond          #+#    #+#             */
/*   Updated: 2024/06/13 20:15:25 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/constants.hpp"

const std::array<sf::Color, 255>	precompute_gradients(void)
{
	std::array<sf::Color, 255>	colors;

	for (uint8_t i = 0; i < 255; i++)
		colors[i] = sf::Color(255 - i, i, 0);
	return (colors);
}

const std::array<sf::Color, 255>	GRADIENTS = precompute_gradients();
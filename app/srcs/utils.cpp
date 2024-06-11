/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:15:32 by craimond          #+#    #+#             */
/*   Updated: 2024/06/11 14:02:00 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/utils.hpp"
#include "headers/Vector2D.hpp"

#include <cstdint>

bool	is_mouse_in_window(const sf::RenderWindow &window, const Vector2D<uint16_t> &mouse_pos)
{
	const uint16_t win_width = window.getSize().x;
	const uint16_t win_height = window.getSize().y;

	return (mouse_pos.x >= 0 && mouse_pos.x < win_width && mouse_pos.y >= 0 && mouse_pos.y < win_height);
}

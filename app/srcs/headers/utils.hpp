/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:18:53 by craimond          #+#    #+#             */
/*   Updated: 2024/06/11 14:30:22 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <SFML/Graphics.hpp>

class Vector2D<uint16_t>;

bool	is_mouse_in_window(const sf::RenderWindow &window, const Vector2D<uint16_t> &mouse_pos);
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:18:53 by craimond          #+#    #+#             */
/*   Updated: 2024/06/12 13:23:23 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <SFML/Graphics.hpp>
#include "Vector2D.hpp"

bool	is_mouse_in_window(const sf::RenderWindow &window, const Vector2D<int32_t> &mouse_pos);

template <typename T>
T		abs(const T &val);
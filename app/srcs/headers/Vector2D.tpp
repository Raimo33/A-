/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector2D.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:58:58 by craimond          #+#    #+#             */
/*   Updated: 2024/06/11 12:09:34 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

template <typename T, typename T2>
Vector2D<T, T2>::Vector2D(const T x, const T y) : x(x), y(y) {}

template <typename T, typename T2>
Vector2D<T, T2>::Vector2D(const Vector2D &src) : x(src.x), y(src.y) {}

template <typename T, typename T2>
Vector2D<T, T2>::Vector2D(const sf::Vector2<T2> &src) : x(const_cast<T>(src.x), const_cast<T>(src.y)) {}

template <typename T, typename T2>
Vector2D<T, T2>::~Vector2D(void) {}

template <typename T, typename T2>
Vector2D<T, T2>		&Vector2D<T, T2>::operator=(const Vector2D &rhs)
{
	if (this == &rhs)
		return *this;
	x = rhs.x;
	y = rhs.y;
	return *this;
}

template <typename T, typename T2>
bool			Vector2D<T, T2>::operator==(const Vector2D &rhs) const { return x == rhs.x && y == rhs.y; }
template <typename T, typename T2>
bool			Vector2D<T, T2>::operator!=(const Vector2D &rhs) const { return !(*this == rhs); }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector2D.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:58:58 by craimond          #+#    #+#             */
/*   Updated: 2024/06/12 12:50:43 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

template <typename T>
Vector2D<T>::Vector2D(const T x, const T y) : x(x), y(y) {}

template <typename T>
Vector2D<T>::Vector2D(const Vector2D &src) : x(src.x), y(src.y) {}

template <typename T>
template <typename sfT>
Vector2D<T>::Vector2D(const sf::Vector2<sfT> &src) : x(static_cast<T>(src.x)), y(static_cast<T>(src.y)) {}

template <typename T>
Vector2D<T>::~Vector2D(void) {}

template <typename T>
Vector2D<T>		&Vector2D<T>::operator=(const Vector2D &rhs)
{
	if (this == &rhs)
		return *this;
	x = rhs.x;
	y = rhs.y;
	return *this;
}

template <typename T>
bool			Vector2D<T>::operator==(const Vector2D &rhs) const { return x == rhs.x && y == rhs.y; }
template <typename T>
bool			Vector2D<T>::operator!=(const Vector2D &rhs) const { return !(*this == rhs); }
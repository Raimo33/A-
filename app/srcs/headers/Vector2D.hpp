/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector2D.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:46:35 by craimond          #+#    #+#             */
/*   Updated: 2024/06/12 13:12:43 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdint>
#include <SFML/System/Vector2.hpp>

template <typename T>
class Vector2D
{
	public:
		Vector2D(const T x = 0, const T y = 0);
		Vector2D(const Vector2D &src);
		template <typename sfT>
		Vector2D(const sf::Vector2<sfT> &src);
		~Vector2D(void);

		Vector2D		&operator=(const Vector2D &rhs);
		bool			operator==(const Vector2D &rhs) const;
		bool			operator!=(const Vector2D &rhs) const;

		T				x;
		T				y;
};

#include "Vector2D.tpp"
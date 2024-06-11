/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:28:30 by craimond          #+#    #+#             */
/*   Updated: 2024/06/11 14:28:43 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdint>

#include "Cell.hpp"
#include "Vector2D.hpp"

class Node : public Cell
{
	public:
		Node(const enum e_cell type, const uint16_t x, const uint16_t y);
		Node(const Cell &src, const uint16_t x, const uint16_t y);
		Node(const Node &src);
		~Node(void);

		uint16_t					getCostG(void) const;
		uint16_t					getCostH(void) const;
		uint16_t					getCostF(void) const;
		const Vector2D<uint16_t>	&getPos(void) const;

		void						computeCosts(const Node &start, const Node &end);

	private:
		uint16_t					computeCost(const Node &other) const;

		uint16_t					_g_cost;
		uint16_t					_h_cost;
		uint16_t					_f_cost;
		const Vector2D<uint16_t>	_pos;
};
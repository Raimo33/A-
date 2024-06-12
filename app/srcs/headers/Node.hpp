/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:28:30 by craimond          #+#    #+#             */
/*   Updated: 2024/06/12 18:55:04 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdint>

#include "Cell.hpp"
#include "Vector2D.hpp"

class Node : public Cell
{
	public:
		Node(const enum e_cell_type type, const int32_t x, const int32_t y);
		Node(const Cell &src);
		Node(const Node &src);
		~Node(void);

		bool						operator==(const Node &rhs) const;

		int32_t						getCostG(void) const;
		void						setCostG(const int32_t g_cost);
		int32_t						getCostH(void) const;
		void						setCostH(const int32_t h_cost);
		int32_t						getCostF(void) const;
		void						setCostF(const int32_t f_cost);
		const std::array<Node *, 8>	&getNeighbours(void) const;
		void						setNeighbours(const std::array<Node *, 8> &neighbours);

		void						computeCostG(const Node &start);
		void						computeCostH(const Node &end);
		void						computeCostF(const Node &start, const Node &end);

	private:
		int32_t						computeCost(const Node &other) const;

		int32_t						_g_cost;
		int32_t						_h_cost;
		int32_t						_f_cost;
		std::array<Node *, 8>		_neighbours;
};
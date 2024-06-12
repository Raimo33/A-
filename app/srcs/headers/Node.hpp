/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:28:30 by craimond          #+#    #+#             */
/*   Updated: 2024/06/12 23:44:10 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdint>

#include "Tile.hpp"
#include "Vector2D.hpp"

class Node : public Tile
{
	public:
		Node(const enum e_cell_type type, const int32_t x, const int32_t y);
		Node(const Tile &src);
		Node(const Node &src);
		~Node(void);

		bool						operator==(const Node &rhs) const;

		float						getCostG(void) const;
		void						setCostG(const float g_cost);
		float						getCostH(void) const;
		void						setCostH(const float h_cost);
		float						getCostF(void) const;
		void						setCostF(const float f_cost);
		const std::array<Node *, 8>	&getNeighbours(void) const;
		void						setNeighbours(const std::array<Node *, 8> &neighbours);

		void						computeCostG(const Node &start);
		void						computeCostH(const Node &end);
		void						computeCostF(const Node &start, const Node &end);

	private:
		float						computeCost(const Node &other) const;

		float						_g_cost;
		float						_h_cost;
		float						_f_cost;
		std::array<Node *, 8>		_neighbours;
};
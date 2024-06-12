/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:28:30 by craimond          #+#    #+#             */
/*   Updated: 2024/06/12 15:42:46 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdint>

#include "Cell.hpp"
#include "Vector2D.hpp"

class Node : public Cell
{
	public:
		Node(const enum e_cell type, const int32_t x, const int32_t y);
		Node(const Cell &src);
		Node(const Node &src);
		~Node(void);

		bool	operator==(const Node &rhs) const;

		int32_t	getCostG(void) const;
		int32_t	getCostH(void) const;
		int32_t	getCostF(void) const;

		void	computeCosts(const Node &start, const Node &end);

	private:
		int32_t	computeCost(const Node &other) const;

		int32_t	_g_cost;
		int32_t	_h_cost;
		int32_t	_f_cost;
};
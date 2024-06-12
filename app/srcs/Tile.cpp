/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tile.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:04:34 by craimond          #+#    #+#             */
/*   Updated: 2024/06/13 00:22:02 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Tile.hpp"

Tile::Tile(const enum e_cell_type type, const int32_t x, const int32_t y) :
	Cell(type, x, y),
	_color(tile_colors.at(type)),
	_sprite(initSprite()) {}

Tile::Tile(const Cell &src) :
	Cell(src),
	_color(tile_colors.at(src.getType())),
	_sprite(initSprite()) {}

Tile::Tile(const Tile &src) :
	Cell(src),
	_color(src._color),
	_sprite(src._sprite) {}

Tile::~Tile(void) {}

bool	Tile::operator==(const Tile &rhs) const { return Cell::operator==(rhs); }

const sf::Color	&Tile::getColor(void) const { return _color; }

void	Tile::setColor(const sf::Color &color)
{
	_color = color;
	_sprite.setFillColor(_color);
}

const sf::RectangleShape	&Tile::getSprite(void) const { return _sprite; }

void	Tile::setType(const enum e_cell_type type)
{
	_type = type;
	_color = tile_colors.at(type);
	_sprite.setFillColor(_color);
}

sf::RectangleShape	Tile::initSprite(void) const
{
	sf::RectangleShape	sprite(sf::Vector2f(TILE_SIZE, TILE_SIZE));

	sprite.setOutlineThickness(1);
	sprite.setOutlineColor(GRAY);
	sprite.setPosition(_pos.x * TILE_SIZE, _pos.y * TILE_SIZE);
	sprite.setFillColor(_color);

	return sprite;
}


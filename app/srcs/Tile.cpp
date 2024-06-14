/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tile.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:04:34 by craimond          #+#    #+#             */
/*   Updated: 2024/06/14 12:51:34 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Tile.hpp"

Tile::Tile(const enum e_cell_type type, const uint16_t x, const uint16_t y) :
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

sf::RectangleShape			&Tile::getSprite(void) { return _sprite; }
const sf::RectangleShape	&Tile::getSprite(void) const { return _sprite; }

void	Tile::setType(const enum e_cell_type type)
{
	_type = type;
	_color = tile_colors.at(type);
	_sprite.setFillColor(_color);
}

void	Tile::reset(void)
{
	_type = FREE;
	_color = tile_colors.at(FREE);
	_sprite.setFillColor(_color);
	_sprite.setOutlineColor(sf::Color::Black);
	_sprite.setOutlineThickness(1);
}

sf::RectangleShape	Tile::initSprite(void) const
{
	sf::RectangleShape		sprite(sf::Vector2f(TILE_SIZE, TILE_SIZE));

	sprite.setOutlineThickness(1);
	sprite.setOutlineColor(sf::Color::Black);
	sprite.setPosition(_pos.x * TILE_SIZE, _pos.y * TILE_SIZE);
	sprite.setFillColor(_color);

	return sprite;
}

const std::unordered_map<enum e_cell_type, sf::Color>	tile_colors =
{
	{ FREE, sf::Color::White },
	{ OBSTACLE, sf::Color::Black },
	{ START, sf::Color::Green },
	{ END, sf::Color::Red }
};

#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"

class Level
{
private:
	sf::Vector2u _size;
	sf::Vector2i _item;

	int _blockSize;

	sf::CircleShape _appleShape;
	sf::RectangleShape _bounds[4];
public:
	Level(sf::Vector2u size);
	~Level();

	int getBlockSize();

	void respawnApple();

	void update(Player& player);
	void render(sf::RenderWindow& _wnd);
};
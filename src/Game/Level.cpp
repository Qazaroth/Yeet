#include "Level.h"

//Private

//Public
Level::Level(sf::Vector2u size)
{
	_blockSize = 16;
	_size = size;

	respawnApple();
	_appleShape.setFillColor(sf::Color::Red);
	_appleShape.setRadius(_blockSize / 2);

	for (int i = 0; i < 4; i++)
	{
		_bounds[i].setFillColor(sf::Color(150, 0, 0));

		if (!((i + 1) % 2))
		{
			_bounds[i].setSize(sf::Vector2f(_size.x, _blockSize));
		}
		else
		{
			_bounds[i].setSize(sf::Vector2f(_blockSize, _size.y));
		}

		if (i < 2)
		{
			_bounds[i].setPosition(0, 0);
		}
		else
		{
			_bounds[i].setOrigin(_bounds[i].getSize());
			_bounds[i].setPosition(sf::Vector2f(_size));
		}
	}
}

Level::~Level() {}

int Level::getBlockSize()
{
	return _blockSize;
}

void Level::respawnApple()
{
	int maxX = (_size.x / _blockSize) - 2;
	int maxY = (_size.y / _blockSize) - 2;

	_item = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
	_appleShape.setPosition(
		_item.x * _blockSize,
		_item.y * _blockSize
	);
}

void Level::update(Player &player)
{
	if (player.getPosition() == _item)
	{
		player.extend();
		player.increaseScore();

		respawnApple();
	}

	int gridSize_X = _size.x / _blockSize;
	int gridSize_y = _size.y / _blockSize;

	if (player.getPosition().x <= 0 ||
		player.getPosition().y <= 0 ||
		player.getPosition().x >= gridSize_X - 1 ||
		player.getPosition().y >= gridSize_y - 1)
	{
		player.lose();
	}
}

void Level::render(sf::RenderWindow &window)
{
	for (int i = 0; i < 4; i++)
	{
		window.draw(_bounds[i]);
	}
	window.draw(_appleShape);
}
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Textbox.h"

struct PlayerSegment
{
	PlayerSegment(int x, int y) : position(x, y) {}
	sf::Vector2i position;
};

enum class Direction
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

using PlayerContainer = std::vector<PlayerSegment>;

class Player
{
private:
	PlayerContainer _plrBody;
	Direction _dir;

	sf::RectangleShape _bodyRect;
	Textbox *_log;

	int _size;
	int _speed;
	int _lives;
	int _score;

	bool _lost;

	void checkCollision();
public:
	Player(int size, Textbox *log);
	~Player();

	void lose();

	void setDirection(Direction dir);
	void increaseScore();
	void toggleLost();

	int getLives();
	int getScore();
	int getSpeed();
	bool hasLost();
	sf::Vector2i getPosition();
	Direction getDirection();
	Direction getPhysicalDirection();

	void extend();
	void reset();

	void move();
	void tick();
	void cut(int segments);
	void render(sf::RenderWindow &wnd);
};
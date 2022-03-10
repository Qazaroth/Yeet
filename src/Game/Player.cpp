#include "Player.h"

// Private
void Player::checkCollision()
{
	if (_plrBody.size() < 5) return;

	PlayerSegment &head = _plrBody.front();

	for (auto itr = _plrBody.begin() + 1; itr != _plrBody.end(); itr++)
	{
		if (itr->position == head.position)
		{
			int segm = _plrBody.end() - itr;
			cut(segm);
			break;
		}
	}
}
// Public
Player::Player(int size, Textbox *log)
{
	_log = log;
	_size = size;

	_bodyRect.setSize(sf::Vector2f(_size - 1, _size - 1));
	reset();
}

Player::~Player() {}

void Player::lose()
{
	_lost = true;
}

void Player::setDirection(Direction dir)
{
	_dir = dir;
}

void Player::increaseScore()
{
	_score += 10;
	_log->add("You ate an apple. Score: " + std::to_string((long long) _score));
}

void Player::toggleLost()
{
	_lost = !_lost;
}

int Player::getLives()
{
	return _lives;
}

int Player::getScore()
{
	return _score;
}

int Player::getSpeed()
{
	return _speed;
}

bool Player::hasLost()
{
	return _lost;
}

sf::Vector2i Player::getPosition()
{
	return (!_plrBody.empty() ? _plrBody.front().position : sf::Vector2i(1, 1));
}

Direction Player::getDirection()
{
	return _dir;
}

Direction Player::getPhysicalDirection()
{
	if (_plrBody.size() <= 1) return Direction::NONE;

	PlayerSegment &head = _plrBody[0];
	PlayerSegment &neck = _plrBody[1];

	if (head.position.x == neck.position.x)
	{
		return (head.position.y > neck.position.y ? Direction::DOWN : Direction::UP);
	}
	else if (head.position.y == neck.position.y)
	{
		return (head.position.y > neck.position.y ? Direction::RIGHT : Direction::LEFT);
	}

	return Direction::NONE;
}

void Player::extend()
{
	if (_plrBody.empty()) return;

	PlayerSegment &tailHead = _plrBody[_plrBody.size() - 1];

	if (_plrBody.size() > 1)
	{
		PlayerSegment &tailBone = _plrBody[_plrBody.size() - 2];

		if (tailHead.position.x == tailBone.position.x)
		{
			if (tailHead.position.y > tailBone.position.y)
			{
				_plrBody.push_back(PlayerSegment(tailHead.position.x, tailHead.position.y + 1));
			}
			else
			{
				_plrBody.push_back(PlayerSegment(tailHead.position.x, tailHead.position.y - 1));
			}
		}
		else if (tailHead.position.y == tailBone.position.y)
		{
			if (tailHead.position.x > tailBone.position.x)
			{
				_plrBody.push_back(PlayerSegment(tailHead.position.x + 1, tailHead.position.y));
			}
			else
			{
				_plrBody.push_back(PlayerSegment(tailHead.position.x - 1, tailHead.position.y));
			}
		}
	}
	else
	{
		if (_dir == Direction::UP)
		{
			_plrBody.push_back(PlayerSegment(tailHead.position.x, tailHead.position.y + 1));
		}
		else if (_dir == Direction::DOWN)
		{
			_plrBody.push_back(PlayerSegment(tailHead.position.x, tailHead.position.y - 1));
		}
		else if (_dir == Direction::LEFT)
		{
			_plrBody.push_back(PlayerSegment(tailHead.position.x + 1, tailHead.position.y));
		}
		else if (_dir == Direction::RIGHT)
		{
			_plrBody.push_back(PlayerSegment(tailHead.position.x - 1, tailHead.position.y));
		}
	}
}

void Player::reset()
{
	_plrBody.clear();
	_plrBody.push_back(PlayerSegment(5, 7));
	_plrBody.push_back(PlayerSegment(5, 6));
	_plrBody.push_back(PlayerSegment(5, 5));

	setDirection(Direction::NONE);

	_speed = 15;
	_lives = 3;
	_score = 0;
	_lost = false;
}

void Player::move()
{
	for (int i = _plrBody.size() - 1; i > 0; i--)
	{
		_plrBody[i].position = _plrBody[i - 1].position;
	}

	if (_dir == Direction::LEFT) 
	{
		_plrBody[0].position.x--;
	}
	else if (_dir == Direction::RIGHT) 
	{
		_plrBody[0].position.x++;
	}
	else if (_dir == Direction::UP)
	{
		_plrBody[0].position.y--;
	}
	else if (_dir == Direction::DOWN) 
	{
		_plrBody[0].position.y++;
	}
}

void Player::tick()
{
	if (_plrBody.empty()) return;
	if (_dir == Direction::NONE) return;

	move();
	checkCollision();
}

void Player::cut(int segm)
{
	for (int i = 0; i < segm; i++)
	{
		_plrBody.pop_back();
	}

	_lives--;

	if (!_lives)
	{
		lose();
		return;
	}

	_log->add("You have lost a life! Lives left: " + std::to_string((long long) _lives));
}

void Player::render(sf::RenderWindow &wind)
{
	if (_plrBody.empty()) return;

	auto head = _plrBody.begin();
	_bodyRect.setFillColor(sf::Color::Red);
	_bodyRect.setPosition(head->position.x * _size, head->position.y * _size);
	wind.draw(_bodyRect);

	_bodyRect.setFillColor(sf::Color::White);
	for (auto itr = _plrBody.begin() + 1; itr != _plrBody.end(); itr++)
	{
		_bodyRect.setPosition(itr->position.x * _size, itr->position.y * _size);
		wind.draw(_bodyRect);
	}
}
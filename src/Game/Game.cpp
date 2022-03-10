#include "Game.h"

// Private

//Public
Game::Game() : _window("Yeet", sf::Vector2u(800, 600)), _plr(_lvl.getBlockSize(), &_txtbox), _lvl(sf::Vector2u(800, 600))
{
	_clock.restart();
	srand(time(nullptr));

	_txtbox.setup(5, 14, 350, sf::Vector2f(225, 0));
	_elapsed = 0.0f;

	_txtbox.add("Seeded random number generator with: " + std::to_string(time(nullptr)));
}

Game::~Game() {}

Window *Game::getWindow()
{
	return &_window;
}

sf::Time Game::getElapsed()
{
	return _clock.getElapsedTime();
}

void Game::restartClock()
{
	_elapsed += _clock.restart().asSeconds();
}

void Game::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
		_plr.getPhysicalDirection() != Direction::DOWN)
	{
		_plr.setDirection(Direction::UP);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
		_plr.getPhysicalDirection() != Direction::UP)
	{
		_plr.setDirection(Direction::DOWN);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
		_plr.getPhysicalDirection() != Direction::RIGHT)
	{
		_plr.setDirection(Direction::LEFT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
		_plr.getPhysicalDirection() != Direction::LEFT)
	{
		_plr.setDirection(Direction::RIGHT);
	}
}

void Game::update()
{
	_window.update();
	float timeStep = 1.0f / _plr.getSpeed();

	if (_elapsed >= timeStep)
	{
		_plr.tick();
		_lvl.update(_plr);
		_elapsed -= timeStep;

		if (_plr.hasLost())
		{
			_txtbox.add("Game Over! Score: " + std::to_string((long long)_plr.getScore()));
			_plr.reset();
		}
	}
}

void Game::render()
{
	_window.beginDraw();
	_lvl.render(*_window.getRenderWindow());
	_plr.render(*_window.getRenderWindow());
	_txtbox.render(*_window.getRenderWindow());
	_window.endDraw();
}
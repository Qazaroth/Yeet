#include "Game.h"

// Private
void Game::movePlayer()
{
	sf::Vector2u _wndSize = _window.getWindowSize();
	sf::Vector2u _txtSize = _plrTexture.getSize();

	if ((_plr.getPosition().x > _wndSize.x - _txtSize.x && _inc.x > 0) ||
		(_plr.getPosition().x < 0 && _inc.x < 0))
	{
		_inc.x = -_inc.x;
	}

	if ((_plr.getPosition().y > _wndSize.y - _txtSize.y && _inc.y > 0) ||
		(_plr.getPosition().y < 0 && _inc.y < 0))
	{
		_inc.y = -_inc.y;
	}

	float fElapsed = _elapsed.asSeconds();

	_plr.setPosition(
		_plr.getPosition().x + (_inc.x * fElapsed),
		_plr.getPosition().y + (_inc.y * fElapsed)
	);
}

//Public
Game::Game() : _window("Yeet", sf::Vector2u(800, 600))
{
	restartClock();
	srand(time(NULL));

	_plrTexture.loadFromFile("Mushroom.png");
	_plr.setTexture(_plrTexture);
	_inc = sf::Vector2i(400, 400);
}

Game::~Game() {}

Window *Game::getWindow()
{
	return &_window;
}

sf::Time Game::getElapsed()
{
	return _elapsed;
}

void Game::restartClock()
{
	_elapsed = _clock.restart();
}

void Game::handleInput()
{
	// TODO: Handle Input
}

void Game::update()
{
	_window.update();
	movePlayer();
}

void Game::render()
{
	_window.beginDraw();
	_window.draw(_plr);
	_window.endDraw();
}
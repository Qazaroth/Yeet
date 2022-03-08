#pragma once

#include "../Graphics/Window/Window.h"

class Game
{
private:
	Window _window;

	sf::Clock _clock;
	sf::Time _elapsed;

	sf::Texture _plrTexture;
	sf::Sprite _plr;
	sf::Vector2i _inc;

	void movePlayer();
public:
	Game();
	~Game();

	Window *getWindow();
	sf::Time getElapsed();

	void restartClock();

	void handleInput();
	void update();
	void render();
};


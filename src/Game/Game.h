#pragma once

#include "Graphics/Window/Window.h"
#include "Level.h"
#include "Player.h"
#include "Textbox.h"

class Game
{
private:
	Window _window;
	Level _lvl;
	Player _plr;
	Textbox _txtbox;

	sf::Clock _clock;
	float _elapsed;
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


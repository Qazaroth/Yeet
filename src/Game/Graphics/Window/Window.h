#pragma once

#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Window
{
private:
	sf::RenderWindow _window;
	sf::Vector2u _size;
	std::string _title;

	bool _isDone;
	bool _isFullscreen;

	void setup(const std::string title, const sf::Vector2u &size);
	void create();
	void destroy();
public:
	Window();
	Window(const std::string &title, const sf::Vector2u &size);
	~Window();

	void beginDraw();
	void endDraw();
	void update();

	void toggleFullscreen();
	void draw(sf::Drawable &drawable);

	bool isDone();
	bool isFullscreen();
	sf::Vector2u getWindowSize();
	sf::RenderWindow *getRenderWindow();
};


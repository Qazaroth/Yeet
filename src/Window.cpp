#include "Window.h"

// Private functions
void Window::setup(const std::string title, const sf::Vector2u &size)
{
	_title = title;
	_size = size;
	_isFullscreen = false;
	_isDone = false;
	_window.setFramerateLimit(60);

	create();
}

void Window::create()
{
	auto style = (_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	_window.create({_size.x, _size.y, 32}, _title, style);
}

void Window::destroy()
{
	_window.close();
}

// Public functions
Window::Window()
{
	setup("Window", sf::Vector2u(800, 600));
}

Window::Window(const std::string &title, const sf::Vector2u &size)
{
	setup(title, size);
}

Window::~Window()
{
	destroy();
}

void Window::beginDraw()
{
	_window.clear(sf::Color::Black);
}

void Window::endDraw()
{
	_window.display();
}

void Window::update()
{
	sf::Event e;

	while (_window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			_isDone = true;
		}
		else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::F5)
		{
			toggleFullscreen();
		}
	}
}

void Window::toggleFullscreen()
{
	_isFullscreen = !_isFullscreen;
	destroy();
	create();
}

void Window::draw(sf::Drawable &_drawable)
{
	_window.draw(_drawable);
}

bool Window::isDone()
{
	return _isDone;
}

bool Window::isFullscreen()
{
	return _isFullscreen;
}

sf::Vector2u Window::getWindowSize()
{
	return _size;
}
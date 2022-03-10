#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using MessageContainer = std::vector<std::string>;

class Textbox
{
private:
	MessageContainer _msgs;

	int _numVisible;

	sf::RectangleShape _backdrop;
	sf::Font _font;
	sf::Text _content;
public:
	Textbox();
	Textbox(int _visible, int _charSize, int _width, sf::Vector2f _screenPos);
	~Textbox();

	void setup(int _visible, int _charSize, int _width, sf::Vector2f _screenPos);
	void add(std::string _msg);
	void clear();

	void render(sf::RenderWindow& _wnd);
};
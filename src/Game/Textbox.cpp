#include "Textbox.h"

// Private
// Public
Textbox::Textbox()
{
	setup(5, 9, 200, sf::Vector2f(0,0));
}

Textbox::Textbox(int visible, int charSize, int width, sf::Vector2f screenPos)
{
	setup(visible, charSize, width, screenPos);
}

Textbox::~Textbox()
{
	clear();
}

void Textbox::setup(int visible, int charSize, int width, sf::Vector2f screenPos)
{
	_numVisible = visible;

	sf::Vector2f _offset(2.0f, 2.0f);

	_font.loadFromFile("arial.ttf");
	_content.setFont(_font);
	_content.setString("");
	_content.setCharacterSize(charSize);
	_content.setFillColor(sf::Color::White);
	_content.setPosition(screenPos + _offset);

	_backdrop.setSize(sf::Vector2f(width, (visible * (charSize * 1.2f))));
	_backdrop.setFillColor(sf::Color(90, 90, 90, 90));
	_backdrop.setPosition(screenPos);
}

void Textbox::add(std::string _msg)
{
	_msgs.push_back(_msg);

	if (_msgs.size() < 6) { return; }

	_msgs.erase(_msgs.begin());
}

void Textbox::clear()
{
	_msgs.clear();
}

void Textbox::render(sf::RenderWindow &_wnd)
{
	std::string content;

	for (auto &itr : _msgs)
	{
		content.append(itr + "\n");
	}

	if (content != "")
	{
		_content.setString(content);
		_wnd.draw(_backdrop);
		_wnd.draw(_content);
	}
}
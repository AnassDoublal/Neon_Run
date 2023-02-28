#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"

class DoubleKill
{
public:
	void init(sf::RenderWindow&);
	void update(sf::RenderWindow&);
	void render(sf::RenderWindow&);
	sf::Text& getText();
private:
	sf::Font m_font;
	sf::Text m_text;
};
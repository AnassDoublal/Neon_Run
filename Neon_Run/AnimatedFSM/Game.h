#pragma once
#include "SFML/Graphics.hpp"

class Game {
public:
	void init(sf::RenderWindow&);
	void update(sf::RenderWindow&);
	void render(sf::RenderWindow&);
};
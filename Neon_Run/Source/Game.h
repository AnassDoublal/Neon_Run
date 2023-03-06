#pragma once
#include "SFML/Graphics.hpp"
#include "GameState.h"
#include "Audio.h"
#include "Defines.h"

class Game {
public:
	void init(sf::RenderWindow&, Audio&);
	void update(sf::RenderWindow&, GAME_STATE&, Audio&);
	void render(sf::RenderWindow&);
};
#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "GameState.h"
#include "Audio.h"

class Menu {
public:
	void init();
	void update(sf::RenderWindow&, GAME_STATE&, Game&, Audio&);
	void render(sf::RenderWindow&);
private:
	sf::Texture bg;
	sf::Texture exit;
	sf::Texture exitClicked;
	sf::Texture exitHovered;
	sf::Texture play;
	sf::Texture playClicked;
	sf::Texture playHovered;

	sf::Sprite sBg;
	sf::Sprite sExit;
	sf::Sprite sExitClicked;
	sf::Sprite sExitHovered;
	sf::Sprite sPlay;
	sf::Sprite sPlayClicked;
	sf::Sprite sPlayHovered;

	bool isHoveringExit = false;
	bool isClickingExit = false;

	bool isHoveringPlay = false;
	bool isClickingPlay = false;

	Audio m_audio;
};
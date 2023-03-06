#pragma once

#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Game.h"

class EndScreen
{
public:
	void init(sf::RenderWindow&, Player&);
	void update(sf::RenderWindow&, int, Player&, Game&);
	void render(sf::RenderWindow&);
	void restart(sf::RenderWindow&, Game&);
private:
	sf::RectangleShape m_bg;
	//sf::RectangleShape m_panel;

	sf::Texture m_panelTexture;
	sf::Sprite m_panel;

	sf::Texture m_gameOverTexture;
	sf::Sprite m_gameOver;

	sf::Texture m_restartTexture;
	sf::Sprite m_restart;

	sf::Texture m_restartTextureHovered;
	sf::Sprite m_restartHovered;

	sf::Texture m_restartTextureClicked;
	sf::Sprite m_restartClicked;

	bool isHoveringButton = false;
	bool isClickingButton = false;

	sf::Font m_font;
	sf::Text m_gameOverText;
	sf::Text m_scoreText;
	sf::Text m_accuarcyText;

	int m_accuracy = 0;

	sf::RectangleShape m_restartButton;
	sf::Text m_restartText;

	sf::Vector2i m_restartButtonPosMin;
	sf::Vector2i m_restartButtonPosMax;
};
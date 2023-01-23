#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class EndScreen
{
public:
	EndScreen(sf::RenderWindow& window, Player& t_player);
	void init(sf::RenderWindow& window);
	void update(sf::RenderWindow& window, int enemiesHit);
	void render(sf::RenderWindow& window);
	void restart(sf::RenderWindow& window);
private:
	sf::RectangleShape m_bg;
	//sf::RectangleShape m_panel;

	sf::Texture m_panelTexture;
	sf::Sprite m_panel;

	sf::Font m_font;
	sf::Text m_gameOverText;
	sf::Text m_scoreText;
	sf::Text m_accuarcyText;

	sf::RectangleShape m_restartButton;
	sf::Text m_restartText;

	sf::Vector2i m_restartButtonPosMin;
	sf::Vector2i m_restartButtonPosMax;

	Player& m_player;
};
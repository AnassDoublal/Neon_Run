#include "SFML/Graphics.hpp"
#include "iostream"
#include "EndScreen.h"

void EndScreen::init(sf::RenderWindow& window, Player& t_player)
{
	m_bg.setPosition(0, 0);
	m_bg.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	m_bg.setFillColor(sf::Color::Color(0, 0, 0, 127));

	if (!m_panelTexture.loadFromFile("assets/endScreen/bamboo.png"))
	{
		// Error
	}

	m_panel.setTexture(m_panelTexture);
	m_panel.setScale(.8f, .8f);
	m_panel.setPosition(window.getSize().x/2.0f - m_panel.getGlobalBounds().width / 2.0f, window.getSize().y / 2.0f - m_panel.getGlobalBounds().height / 2.0f);
	/*m_panel.setSize(sf::Vector2f(400, 400));
	m_panel.setFillColor(sf::Color::White);*/

	if (!m_font.loadFromFile("assets/fonts/ninja.otf"))
	{
		// Error
	}

	m_gameOverText.setFont(m_font);
	m_gameOverText.setString("Game Over");
	m_gameOverText.setCharacterSize(24);
	m_gameOverText.setFillColor(sf::Color::Black);
	//m_gameOverText.setPosition(m_panel.getPosition().x + m_panel.getSize().x / 2.0f - m_gameOverText.getGlobalBounds().width / 2.0f, m_panel.getPosition().y + 20);
	m_gameOverText.setPosition(m_panel.getPosition().x + m_panel.getGlobalBounds().width / 2.0f - m_gameOverText.getGlobalBounds().width / 2.0f, m_panel.getPosition().y + 110.0f);

	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(24);
	m_scoreText.setFillColor(sf::Color::Black);

	m_accuarcyText.setFont(m_font);
	m_accuarcyText.setString("Dagger accuarcy : 0 %");
	m_accuarcyText.setCharacterSize(24);
	m_accuarcyText.setFillColor(sf::Color::Black);

	m_restartButton.setSize(sf::Vector2f(200, 50));
	m_restartButton.setPosition(m_panel.getPosition().x + m_panel.getGlobalBounds().width / 2.0f - m_restartButton.getGlobalBounds().width / 2.0f, m_panel.getPosition().y + m_panel.getGlobalBounds().height - m_restartButton.getGlobalBounds().height - 120.0f);
	m_restartButton.setFillColor(sf::Color::Black);

	m_restartText.setFont(m_font);
	m_restartText.setString("Restart");
	m_restartText.setCharacterSize(24);
	m_restartText.setFillColor(sf::Color::White);
	m_restartText.setPosition(m_restartButton.getPosition().x + m_restartButton.getSize().x / 2.0f - m_restartText.getGlobalBounds().width / 2.0f, m_restartButton.getPosition().y + m_restartButton.getSize().y / 2.0f - 17.0f);

	m_restartButtonPosMin.x = m_restartButton.getPosition().x;
	m_restartButtonPosMax.x = m_restartButton.getPosition().x + m_restartButton.getSize().x;

	m_restartButtonPosMin.y = m_restartButton.getPosition().y;
	m_restartButtonPosMax.y = m_restartButton.getPosition().y + m_restartButton.getSize().y;
}

void EndScreen::update(sf::RenderWindow& window, int score, Player& t_player, Game& game)
{
	m_scoreText.setString("Score : " + std::to_string(score));

	if (t_player.m_totalShots != 0)
		m_accuracy = t_player.m_shotsHit * 100 / t_player.m_totalShots;

	if (t_player.m_totalShots != 0)
		m_accuarcyText.setString("Shot accuracy : " + std::to_string(m_accuracy) + " %");

	m_scoreText.setPosition(m_panel.getPosition().x + m_panel.getGlobalBounds().width / 2.0f - m_scoreText.getGlobalBounds().width / 2.0f, m_panel.getPosition().y + m_panel.getGlobalBounds().height / 2.0f - m_gameOverText.getGlobalBounds().height - 20);
	m_accuarcyText.setPosition(m_panel.getPosition().x + m_panel.getGlobalBounds().width / 2.0f - m_accuarcyText.getGlobalBounds().width / 2.0f, m_panel.getPosition().y + m_panel.getGlobalBounds().height / 2.0f - m_gameOverText.getGlobalBounds().height + 20);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (sf::Mouse::getPosition(window).x > m_restartButtonPosMin.x
			&& sf::Mouse::getPosition(window).x < m_restartButtonPosMax.x
			&& sf::Mouse::getPosition(window).y > m_restartButtonPosMin.y
			&& sf::Mouse::getPosition(window).y < m_restartButtonPosMax.y)
		{
			restart(window, game);
		}
	}

}

void EndScreen::render(sf::RenderWindow& window)
{
	window.draw(m_bg);
	window.draw(m_panel);
	window.draw(m_gameOverText);
	window.draw(m_scoreText);
	window.draw(m_accuarcyText);
	window.draw(m_restartButton);
	window.draw(m_restartText);
}

void EndScreen::restart(sf::RenderWindow& window, Game& game)
{
	//window.close();
	game.init(window);
}

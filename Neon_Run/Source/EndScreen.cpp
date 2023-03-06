#include "SFML/Graphics.hpp"
#include "iostream"
#include "EndScreen.h"

void EndScreen::init(sf::RenderWindow& window, Player& t_player)
{
	m_bg.setPosition(0, 0);
	m_bg.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	m_bg.setFillColor(sf::Color::Color(0, 0, 0, 127));

	if (!m_panelTexture.loadFromFile("assets/endScreen/bg.png"))
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

	m_gameOverTexture.loadFromFile("assets/endScreen/gameOver.png");
	m_gameOver.setTexture(m_gameOverTexture);
	m_gameOver.setScale(.3f, .3f);
	m_gameOver.setPosition(m_panel.getPosition().x + m_panel.getGlobalBounds().width / 2.0f - m_gameOver.getGlobalBounds().width / 2.0f, m_panel.getPosition().y + 80.0f);

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

	m_restartTexture.loadFromFile("assets/endScreen/restart.png");
	m_restartTextureHovered.loadFromFile("assets/endScreen/restartHovered.png");
	m_restartTextureClicked.loadFromFile("assets/endScreen/restartClicked.png");

	m_restart.setTexture(m_restartTexture);
	m_restartHovered.setTexture(m_restartTextureHovered);
	m_restartClicked.setTexture(m_restartTextureClicked);

	m_restart.setScale(.5f, .5f);
	m_restart.setPosition(m_panel.getPosition().x + m_panel.getGlobalBounds().width / 2.0f - m_restart.getGlobalBounds().width / 2.0f, m_panel.getPosition().y + m_panel.getGlobalBounds().height - m_restart.getGlobalBounds().height - 100.0f);
	m_restartHovered.setScale(.5f, .5f);
	m_restartHovered.setPosition(m_panel.getPosition().x + m_panel.getGlobalBounds().width / 2.0f - m_restartHovered.getGlobalBounds().width / 2.0f, m_panel.getPosition().y + m_panel.getGlobalBounds().height - m_restartHovered.getGlobalBounds().height - 100.0f);
	m_restartClicked.setScale(.5f, .5f);
	m_restartClicked.setPosition(m_panel.getPosition().x + m_panel.getGlobalBounds().width / 2.0f - m_restartClicked.getGlobalBounds().width / 2.0f, m_panel.getPosition().y + m_panel.getGlobalBounds().height - m_restartClicked.getGlobalBounds().height - 100.0f);

	m_restartButton.setSize(sf::Vector2f(200, 50));
	m_restartButton.setPosition(m_panel.getPosition().x + m_panel.getGlobalBounds().width / 2.0f - m_restartButton.getGlobalBounds().width / 2.0f, m_panel.getPosition().y + m_panel.getGlobalBounds().height - m_restartButton.getGlobalBounds().height - 120.0f);
	m_restartButton.setFillColor(sf::Color::Black);

	m_restartText.setFont(m_font);
	m_restartText.setString("Restart");
	m_restartText.setCharacterSize(24);
	m_restartText.setFillColor(sf::Color::White);
	m_restartText.setPosition(m_restartButton.getPosition().x + m_restartButton.getSize().x / 2.0f - m_restartText.getGlobalBounds().width / 2.0f, m_restartButton.getPosition().y + m_restartButton.getSize().y / 2.0f - 17.0f);

	m_restartButtonPosMin.x = m_restart.getPosition().x;
	m_restartButtonPosMax.x = m_restart.getPosition().x + m_restart.getGlobalBounds().width;

	m_restartButtonPosMin.y = m_restart.getPosition().y;
	m_restartButtonPosMax.y = m_restart.getPosition().y + m_restart.getGlobalBounds().height;
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

	if (sf::Mouse::getPosition(window).x > m_restartButtonPosMin.x
		&& sf::Mouse::getPosition(window).x < m_restartButtonPosMax.x
		&& sf::Mouse::getPosition(window).y > m_restartButtonPosMin.y
		&& sf::Mouse::getPosition(window).y < m_restartButtonPosMax.y)
	{
		isHoveringButton = true;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			isClickingButton = true;
			restart(window, game);
		}
	}
	else
	{
		isHoveringButton = false;
		isClickingButton = false;
	}
}

void EndScreen::render(sf::RenderWindow& window)
{
	//window.draw(m_bg);
	window.draw(m_panel);
	window.draw(m_gameOver);
	//window.draw(m_gameOverText);
	window.draw(m_scoreText);
	window.draw(m_accuarcyText);
	window.draw(m_restart);
		if(isHoveringButton)
	window.draw(m_restartHovered);
		if (isClickingButton)
	window.draw(m_restartClicked);
	/*window.draw(m_restartButton);
	window.draw(m_restartText);*/
}

void EndScreen::restart(sf::RenderWindow& window, Game& game)
{
	//window.close();
	game.init(window, audio);
}

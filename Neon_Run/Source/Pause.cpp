#include "Pause.h"

void Pause::init(sf::RenderWindow& window)
{
	// Textures

	m_panelTexture.loadFromFile("assets/pause/bg.png");

	m_pausedTexture.loadFromFile("assets/pause/Paused-banner.png");

	m_continueTexture.loadFromFile("assets/pause/ContinueButton.png");
	m_continueTextureHovered.loadFromFile("assets/pause/continueButton-hover.png");
	m_continueTextureClicked.loadFromFile("assets/pause/continuebutton-onclick.png");

	m_restartTexture.loadFromFile("assets/pause/RestartButton.png");
	m_restartTextureHovered.loadFromFile("assets/pause/restartButton-hover.png");
	m_restartTextureClicked.loadFromFile("assets/pause/restartbutton-onclick.png");

	m_exitTexture.loadFromFile("assets/pause/ExitButton.png");
	m_exitTextureHovered.loadFromFile("assets/pause/exitButton-hover.png");
	m_exitTextureClicked.loadFromFile("assets/pause/exitButton-onclick.png");

	// Sprites

	m_panel.setTexture(m_panelTexture);

	m_paused.setTexture(m_pausedTexture);

	m_continue.setTexture(m_continueTexture);
	m_continueHovered.setTexture(m_continueTextureHovered);
	m_continueClicked.setTexture(m_continueTextureClicked);

	m_restart.setTexture(m_restartTexture);
	m_restartHovered.setTexture(m_restartTextureHovered);
	m_restartClicked.setTexture(m_restartTextureClicked);

	m_exit.setTexture(m_exitTexture);
	m_exitHovered.setTexture(m_exitTextureHovered);
	m_exitClicked.setTexture(m_exitTextureClicked);

	// Config

	m_panel.setScale(.8f, .8f);
	m_panel.setPosition(window.getSize().x / 2.0f - m_panel.getGlobalBounds().width / 2.0f, window.getSize().y / 2.0f - m_panel.getGlobalBounds().height / 2.0f);

	m_paused.setScale(.3f, .3f);
	m_paused.setPosition(m_panel.getPosition().x + m_panel.getGlobalBounds().width / 2.0f - m_paused.getGlobalBounds().width / 2.0f, m_panel.getPosition().y + 80.0f);

	m_continue.setScale(.5f, .5f);
	m_continue.setPosition(m_panel.getPosition().x + m_panel.getGlobalBounds().width / 2.0f - m_continue.getGlobalBounds().width / 2.0f, m_panel.getPosition().y + m_panel.getGlobalBounds().height / 2.0f - m_continue.getGlobalBounds().height);
	m_continueHovered.setScale(.5f, .5f);
	m_continueHovered.setPosition(m_panel.getPosition().x + m_panel.getGlobalBounds().width / 2.0f - m_continue.getGlobalBounds().width / 2.0f, m_panel.getPosition().y + m_panel.getGlobalBounds().height / 2.0f - m_continue.getGlobalBounds().height);
	m_continueClicked.setScale(.5f, .5f);
	m_continueClicked.setPosition(m_panel.getPosition().x + m_panel.getGlobalBounds().width / 2.0f - m_continue.getGlobalBounds().width / 2.0f, m_panel.getPosition().y + m_panel.getGlobalBounds().height / 2.0f - m_continue.getGlobalBounds().height);

	m_restart.setScale(.5f, .5f);
	m_restart.setPosition(m_panel.getPosition().x + m_panel.getGlobalBounds().width / 2.0f - m_restart.getGlobalBounds().width / 2.0f, m_panel.getPosition().y + m_panel.getGlobalBounds().height / 2.0f);
	m_restartHovered.setScale(.5f, .5f);
	m_restartHovered.setPosition(m_panel.getPosition().x + m_panel.getGlobalBounds().width / 2.0f - m_restart.getGlobalBounds().width / 2.0f, m_panel.getPosition().y + m_panel.getGlobalBounds().height / 2.0f);
	m_restartClicked.setScale(.5f, .5f);
	m_restartClicked.setPosition(m_panel.getPosition().x + m_panel.getGlobalBounds().width / 2.0f - m_restart.getGlobalBounds().width / 2.0f, m_panel.getPosition().y + m_panel.getGlobalBounds().height / 2.0f);

	m_exit.setScale(.5f, .5f);
	m_exit.setPosition(m_panel.getPosition().x + m_panel.getGlobalBounds().width / 2.0f - m_exit.getGlobalBounds().width / 2.0f, m_panel.getPosition().y + m_panel.getGlobalBounds().height / 2.0f + m_exit.getGlobalBounds().height);
	m_exitHovered.setScale(.5f, .5f);
	m_exitHovered.setPosition(m_panel.getPosition().x + m_panel.getGlobalBounds().width / 2.0f - m_exit.getGlobalBounds().width / 2.0f, m_panel.getPosition().y + m_panel.getGlobalBounds().height / 2.0f + m_exit.getGlobalBounds().height);
	m_exitClicked.setScale(.5f, .5f);
	m_exitClicked.setPosition(m_panel.getPosition().x + m_panel.getGlobalBounds().width / 2.0f - m_exit.getGlobalBounds().width / 2.0f, m_panel.getPosition().y + m_panel.getGlobalBounds().height / 2.0f + m_exit.getGlobalBounds().height);
}

void Pause::update(GAME_STATE& gameState, Game& game, sf::RenderWindow& window, Audio& audio)
{
	if (m_continue.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y))
	{
		isHoveringContinue = true;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			isClickingContinue = true;
			gameState = GAME_STATE::GAME;
		}
	}
	else
	{
		isHoveringContinue = false;
		isClickingContinue = false;
	}

	if (m_restart.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y))
	{
		isHoveringRestart = true;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			isClickingRestart = true;
			game.init(window, audio);
			gameState = GAME_STATE::GAME;
		}
	}
	else
	{
		isHoveringRestart = false;
		isClickingRestart = false;
	}

	if (m_exit.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y))
	{
		isHoveringExit = true;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			audio.m_bgMusic.stop();
			audio.m_menuMusic.play();
			isClickingExit = true;
			gameState = GAME_STATE::MENU;
		}
	}
	else
	{
		isHoveringExit = false;
		isClickingExit = false;
	}

}

void Pause::render(sf::RenderWindow& window)
{
	window.draw(m_panel);

	window.draw(m_paused);

	window.draw(m_continue);
	if(isHoveringContinue)
		window.draw(m_continueHovered);
	if (isClickingContinue)
		window.draw(m_continueClicked);

	window.draw(m_restart);
	if (isHoveringRestart)
		window.draw(m_restartHovered);
	if (isClickingRestart)
		window.draw(m_restartClicked);

	window.draw(m_exit);
	if (isHoveringExit)
		window.draw(m_exitHovered);
	if (isClickingExit)
		window.draw(m_exitClicked);
}

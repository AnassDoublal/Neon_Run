#pragma once
#include "SFML/Graphics.hpp"
#include "GameState.h"
#include "Game.h"
#include "Audio.h"

class Pause {
public:
	void init(sf::RenderWindow&);
	void update(GAME_STATE&, Game&, sf::RenderWindow&, Audio&);
	void render(sf::RenderWindow&);
private:
	sf::Texture m_panelTexture;
	sf::Sprite m_panel;

	sf::Texture m_pausedTexture;
	sf::Sprite m_paused;

	sf::Texture m_continueTexture;
	sf::Sprite m_continue;
	sf::Texture m_continueTextureHovered;
	sf::Sprite m_continueHovered;
	bool isHoveringContinue = false;
	sf::Texture m_continueTextureClicked;
	sf::Sprite m_continueClicked;
	bool isClickingContinue = false;

	sf::Texture m_restartTexture;
	sf::Sprite m_restart;
	sf::Texture m_restartTextureHovered;
	sf::Sprite m_restartHovered;
	bool isHoveringRestart = false;
	sf::Texture m_restartTextureClicked;
	sf::Sprite m_restartClicked;
	bool isClickingRestart = false;

	sf::Texture m_exitTexture;
	sf::Sprite m_exit;
	sf::Texture m_exitTextureHovered;
	sf::Sprite m_exitHovered;
	bool isHoveringExit = false;
	sf::Texture m_exitTextureClicked;
	sf::Sprite m_exitClicked;
	bool isClickingExit = false;
};
#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"

class Player;

class ExtraKunais
{
public:
	void init(sf::RenderWindow&);
	void update(sf::RenderWindow&, Player*);
	void render(sf::RenderWindow&);
	sf::Sprite& getSprite();
	void displayExtraKunais(sf::RenderWindow&, Player*);

	bool m_isPlayerDead = false;

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	float m_friction = .2f;
	sf::Font m_font;
	sf::Text m_text;
	sf::Clock m_textClock;
	bool m_hasRestartedClock = false;
	float m_speed = .1f;
};
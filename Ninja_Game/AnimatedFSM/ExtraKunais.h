#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Player;

class ExtraKunais
{
public:
	void init(sf::RenderWindow& window);
	void update(sf::RenderWindow& window, Player* player);
	void render(sf::RenderWindow& window);
	sf::Sprite& getSprite();

	bool m_isPlayerDead = false;

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	float m_friction = .2f;
};
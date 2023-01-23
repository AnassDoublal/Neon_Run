#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "circle.h"
#include "rectangle.h"
#include "Enemy.h"
#include "Medkit.h"
#include "ExtraKunais.h"

class Player;

class Tiles
{
	public:
		virtual void init(sf::Texture& texture, sf::RenderWindow& window) = 0;
		virtual void update(sf::RenderWindow& window, Player* player) = 0;
		virtual void render(sf::RenderWindow& window) = 0;
		virtual std::vector<sf::Sprite>& getTiles() = 0;
		virtual Enemy& getEnemy() = 0;
		virtual Medkit& getMedkit() = 0;
		virtual ExtraKunais& getExtraKunais() = 0;
		//virtual Circle& getEnemyCircle() = 0;
		//virtual Rectangle& getEnemyRectangle() = 0;

		int m_hits = 0;
};
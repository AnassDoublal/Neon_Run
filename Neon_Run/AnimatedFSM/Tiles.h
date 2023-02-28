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
		virtual void init(sf::Texture&, sf::RenderWindow&) = 0;
		virtual void update(sf::RenderWindow&, Player*) = 0;
		virtual void render(sf::RenderWindow&) = 0;
		virtual std::vector<sf::Sprite>& getTiles() = 0;
		virtual Enemy& getEnemy() = 0;
		virtual Medkit& getMedkit() = 0;
		virtual ExtraKunais& getExtraKunais() = 0;
		virtual float getEnemyX() = 0;
		virtual sf::Vector2f getNewEnemyPos() = 0;
		//virtual Circle& getEnemyCircle() = 0;
		//virtual Rectangle& getEnemyRectangle() = 0;

		int m_hits = 0;
};
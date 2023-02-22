#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"
#include "EnemyState.h"
#include "AnimatedSpriteEnemy.h"
#include "circle.h"
#include "Rectangle.h"

class Player;

class Enemy
{
	public:
		void init(sf::RenderWindow& window, float posX, float posY);
		void update(sf::RenderWindow& window, Player* player);
		void render(sf::RenderWindow& window);

		EnemyState* m_state;
		AnimatedSpriteEnemy m_animated_sprite;

		AnimatedSpriteEnemy& getAnimatedSprite();
		AnimatedSpriteEnemy& getAnimatedSpriteFrame();

		EnemyState* getEnemyState();
		void setEnemyState(EnemyState*);

		//Circle m_circle;
		Rectangle m_rectangle;

		sf::Texture m_daggerTexture;

		std::vector<sf::Sprite> m_daggers;
		bool m_daggerThrow;

		bool m_isDead = false;
		bool m_isPlayerDead = false;

		std::vector<Rectangle> m_daggers_rectangles;
	private:
		sf::Texture m_texture;
		//sf::Sprite m_sprite;

		//sf::CircleShape m_circle_rep;
		sf::RectangleShape m_rectangle_rep;

		float m_friction = .2f;
};
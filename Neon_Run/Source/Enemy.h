#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"
#include "EnemyState.h"
#include "AnimatedSpriteEnemy.h"
#include "circle.h"
#include "Rectangle.h"
#include "Candle/RadialLight.hpp"

class Player;

class Enemy
{
	public:
		void init(sf::RenderWindow&, float, float, sf::Texture&);
		void update(sf::RenderWindow&, Player*);
		void render(sf::RenderWindow&);

		EnemyState* m_state;
		AnimatedSpriteEnemy m_animated_sprite;

		AnimatedSpriteEnemy& getAnimatedSprite();
		AnimatedSpriteEnemy& getAnimatedSpriteFrame();

		EnemyState* getEnemyState();
		void setEnemyState(EnemyState*);

		//Circle m_circle;
		Rectangle m_rectangle;
		Rectangle m_headRectangle;

		sf::Texture m_daggerTexture;

		std::vector<sf::Sprite> m_daggers;
		bool m_daggerThrow;

		bool m_isDead = false;
		bool m_isPlayerDead = false;

		std::vector<Rectangle> m_daggers_rectangles;

		enum class Action { SWORD, THROW };
		Action m_action = Action::THROW;

		bool m_isAttacking = false;

		candle::RadialLight& getLight();

	private:
		sf::Texture m_texture;
		//sf::Sprite m_sprite;

		//sf::CircleShape m_circle_rep;
		sf::RectangleShape m_rectangle_rep;

		float m_friction = .2f;

		candle::RadialLight m_light;
};
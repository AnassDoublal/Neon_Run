#pragma once
#include "Tiles.h"

// Two platforms
class Set1 : public Tiles{
	public:
		virtual void init(sf::Texture& texture, sf::RenderWindow& window);
		virtual void update(sf::RenderWindow& window, Player* player);
		virtual void render(sf::RenderWindow& window);
		virtual std::vector<sf::Sprite>& getTiles();
		virtual Enemy& getEnemy();
		virtual Medkit& getMedkit();
		virtual ExtraKunais& getExtraKunais();
		virtual float getEnemyX();
		virtual sf::Vector2f getNewEnemyPos();
		/*virtual Circle& getEnemyCircle();
		virtual Rectangle& getEnemyRectangle();*/
	private:
		sf::Sprite m_sprite_edge_left;
		std::vector<sf::Sprite> m_sprites_middle;
		float m_PosX;
		sf::Sprite m_sprite_edge_right;

		sf::Sprite m_sprite_edge_left_top;
		std::vector<sf::Sprite> m_sprites_middle_top;
		float m_PosX_top;
		sf::Sprite m_sprite_edge_right_top;

		std::vector<sf::Sprite> m_sprites;

		Enemy enemy;
		Medkit medkit;
		ExtraKunais extraKunais;

		float m_friction = .2f;

		float m_enemyX = 400.0f;

		sf::Vector2f m_positions[3];
};
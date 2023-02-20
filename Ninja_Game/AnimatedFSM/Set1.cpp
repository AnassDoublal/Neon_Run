#include "Set1.h"
#include "Player.h"

void Set1::init(sf::Texture& texture, sf::RenderWindow& window)
{
	m_sprite_edge_left.setTexture(texture);
	m_sprite_edge_left.setTextureRect(sf::IntRect(32*4, 32, 32, 32));
	m_sprite_edge_left.setPosition(sf::Vector2f(window.getSize().x, 775.0f));

	m_PosX = window.getSize().x + 31.99f;

	for (int i = 0; i < 23; i++)
	{
		sf::Sprite sprite_middle;
		sprite_middle.setTexture(texture);
		sprite_middle.setTextureRect(sf::IntRect(32 * 5, 32, 32, 32));
		sprite_middle.setPosition(sf::Vector2f(m_PosX, 775.0f));
		m_sprites_middle.push_back(sprite_middle);
		m_PosX += 31.99f;
	}

	m_sprite_edge_right.setTexture(texture);
	m_sprite_edge_right.setTextureRect(sf::IntRect(32 * 6, 32, 32, 32));
	m_sprite_edge_right.setPosition(sf::Vector2f(m_sprites_middle[m_sprites_middle.size()-1].getPosition().x + 31.99f, 775.0f));

	m_sprite_edge_left_top = m_sprite_edge_left;
	m_sprite_edge_left_top.setPosition(sf::Vector2f(window.getSize().x + 500.0f, 600.0f));

	m_PosX_top = 31.99f;

	for (int i = 0; i < 15; i++)
	{
		sf::Sprite sprite_middle;
		sprite_middle.setTexture(texture);
		sprite_middle.setTextureRect(sf::IntRect(32 * 5, 32, 32, 32));
		sprite_middle.setPosition(sf::Vector2f(m_sprite_edge_left_top.getPosition().x + m_PosX_top, m_sprite_edge_left_top.getPosition().y));
		m_sprites_middle_top.push_back(sprite_middle);
		m_PosX_top += 31.99f;
	}

	m_sprite_edge_right_top = m_sprite_edge_right;
	m_sprite_edge_right_top.setPosition(sf::Vector2f(m_sprites_middle_top[m_sprites_middle_top.size() - 1].getPosition().x + 31.99f, m_sprite_edge_left_top.getPosition().y));

	m_sprites.push_back(m_sprite_edge_left);

	for (auto& sprite : m_sprites_middle)
	{
		m_sprites.push_back(sprite);
	}

	m_sprites.push_back(m_sprite_edge_right);

	m_sprites.push_back(m_sprite_edge_left_top);

	for (auto& sprite : m_sprites_middle_top)
	{
		m_sprites.push_back(sprite);
	}

	m_sprites.push_back(m_sprite_edge_right_top);

	for (int i = 0; i < m_sprites.size(); i++)
	{
		m_sprites[i].setScale(.0f, .0f);
	}

	enemy.init(window, 400.0f, 645.0f);
	medkit.init(window);
	extraKunais.init(window);
}

void Set1::update(sf::RenderWindow& window, Player* player)
{
	//std::cout << "SET 1 X : " << m_sprites[m_sprites.size() - 1].getPosition().x << "\n\n";

	if(player->m_isDead)
		m_friction *= .999f;

	for (int i=0; i<m_sprites.size(); i++)
	{
		if (!player->m_isDead)
		{
			m_sprites[i].move(-player->m_speed, .0f);
		}
		else
		{
			m_sprites[i].move(-m_friction, .0f);
		}
	}

	enemy.update(window, player);
	medkit.update(window, player);
	extraKunais.update(window, player);
}

void Set1::render(sf::RenderWindow& window)
{
	for (auto& sprite : m_sprites)
		window.draw(sprite);

	enemy.render(window);
	medkit.render(window);
	extraKunais.render(window);
}

std::vector<sf::Sprite>& Set1::getTiles()
{
	//std::cout << "SET 1 ZONE\n";

	return m_sprites;
}

Enemy& Set1::getEnemy() 
{
	return enemy;
}

Medkit& Set1::getMedkit()
{
	return medkit;
}

ExtraKunais& Set1::getExtraKunais()
{
	return extraKunais;
}

//Circle& Set1::getEnemyCircle()
//{
//	return enemy.m_circle;
//}

//Rectangle& Set1::getEnemyRectangle()
//{
//	return enemy.m_rectangle;
//}

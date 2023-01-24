#include "Set2.h"
#include "Player.h"

void Set2::init(sf::Texture& texture, sf::RenderWindow& window)
{
	// Left tiles

	m_sprite_edge_left.setTexture(texture);
	m_sprite_edge_left.setTextureRect(sf::IntRect(32 * 4, 32, 32, 32));
	m_sprite_edge_left.setPosition(sf::Vector2f(window.getSize().x, 380.0f));

	m_PosX = window.getSize().x + 31.99f;

	for (int i = 0; i < 5; i++)
	{
		sf::Sprite sprite_middle;
		sprite_middle.setTexture(texture);
		sprite_middle.setTextureRect(sf::IntRect(32 * 5, 32, 32, 32));
		sprite_middle.setPosition(sf::Vector2f(m_PosX, 380.0f));
		m_sprites_middle.push_back(sprite_middle);
		m_PosX += 31.99f;
	}

	m_sprite_edge_right.setTexture(texture);
	m_sprite_edge_right.setTextureRect(sf::IntRect(32 * 6, 32, 32, 32));
	m_sprite_edge_right.setPosition(sf::Vector2f(m_sprites_middle[m_sprites_middle.size() - 1].getPosition().x + 31.99f, 380.0f));

	// Top tiles

	m_sprite_edge_left_top = m_sprite_edge_left;
	m_sprite_edge_left_top.setPosition(sf::Vector2f(window.getSize().x + 300.0f, 200.0f));

	m_PosX_top = 31.99f;

	for (int i = 0; i < 5; i++)
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

	// Right tiles

	m_sprite_edge_left_right.setTexture(texture);
	m_sprite_edge_left_right.setTextureRect(sf::IntRect(32 * 4, 32, 32, 32));
	m_sprite_edge_left_right.setPosition(sf::Vector2f(window.getSize().x + 600.0f, 380.0f));

	m_PosX_right = window.getSize().x + 600.0f + 31.99f;

	for (int i = 0; i < 5; i++)
	{
		sf::Sprite sprite_middle;
		sprite_middle.setTexture(texture);
		sprite_middle.setTextureRect(sf::IntRect(32 * 5, 32, 32, 32));
		sprite_middle.setPosition(sf::Vector2f(m_PosX_right, 380.0f));
		m_sprites_middle_right.push_back(sprite_middle);
		m_PosX_right += 31.99f;
	}

	m_sprite_edge_right_right.setTexture(texture);
	m_sprite_edge_right_right.setTextureRect(sf::IntRect(32 * 6, 32, 32, 32));
	m_sprite_edge_right_right.setPosition(sf::Vector2f(m_sprites_middle_right[m_sprites_middle_right.size() - 1].getPosition().x + 31.99f, 380.0f));

	// Left tiles

	m_sprites.push_back(m_sprite_edge_left);

	for (auto& sprite : m_sprites_middle)
	{
		m_sprites.push_back(sprite);
	}

	m_sprites.push_back(m_sprite_edge_right);

	// Top tiles

	m_sprites.push_back(m_sprite_edge_left_top);

	for (auto& sprite : m_sprites_middle_top)
	{
		m_sprites.push_back(sprite);
	}

	m_sprites.push_back(m_sprite_edge_right_top);

	// Right tiles

	m_sprites.push_back(m_sprite_edge_left_right);

	for (auto& sprite : m_sprites_middle_right)
	{
		m_sprites.push_back(sprite);
	}

	m_sprites.push_back(m_sprite_edge_right_right);

	for (int i = 0; i < m_sprites.size(); i++)
	{
		m_sprites[i].setScale(.0f, .0f);
	}

	enemy.init(window);
}

void Set2::update(sf::RenderWindow& window, Player* player)
{
	if (player->m_isDead)
		m_friction *= .999f;

	for (int i = 0; i < m_sprites.size(); i++)
	{
		if (!player->m_isDead)
		{
			m_sprites[i].move(-.2f, .0f);
		}
		else
		{
			m_sprites[i].move(-m_friction, .0f);
		}

		if (m_sprites[i].getPosition().x <= -m_sprites[i].getGlobalBounds().width)
		{
			m_sprites[i].setPosition(m_sprites[i].getPosition().x + window.getSize().x * 3, m_sprites[i].getPosition().y);
		}
	}

	enemy.update(window, player);
}

void Set2::render(sf::RenderWindow& window)
{
	for (auto& sprite : m_sprites)
		window.draw(sprite);

	enemy.render(window);
}

std::vector<sf::Sprite>& Set2::getTiles()
{
	return m_sprites;
}

Enemy& Set2::getEnemy()
{
	return enemy;
}

Medkit& Set2::getMedkit()
{
	return medkit;
}

ExtraKunais& Set2::getExtraKunais()
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
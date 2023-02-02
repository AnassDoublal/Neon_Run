#include "Set3.h"
#include "Player.h"

void Set3::init(sf::Texture& texture, sf::RenderWindow& window)
{
	// Left tiles

	m_sprite_edge_left.setTexture(texture);
	m_sprite_edge_left.setTextureRect(sf::IntRect(32 * 4, 32, 32, 32));
	m_sprite_edge_left.setPosition(sf::Vector2f(window.getSize().x, 820.0f));

	m_PosX = window.getSize().x + 31.99f;

	for (int i = 0; i < 8; i++)
	{
		sf::Sprite sprite_middle;
		sprite_middle.setTexture(texture);
		sprite_middle.setTextureRect(sf::IntRect(32 * 5, 32, 32, 32));
		sprite_middle.setPosition(sf::Vector2f(m_PosX, 820.0f));
		m_sprites_middle.push_back(sprite_middle);
		m_PosX += 31.99f;
	}

	m_sprite_edge_right.setTexture(texture);
	m_sprite_edge_right.setTextureRect(sf::IntRect(32 * 6, 32, 32, 32));
	m_sprite_edge_right.setPosition(sf::Vector2f(m_sprites_middle[m_sprites_middle.size() - 1].getPosition().x + 31.99f, 820.0f));

	// Middle tiles

	m_sprite_edge_left_middle = m_sprite_edge_left;
	m_sprite_edge_left_middle.setPosition(sf::Vector2f(window.getSize().x + 275.0f, 700.0f));

	m_PosX_middle = 31.99f;

	for (int i = 0; i < 25; i++)
	{
		sf::Sprite sprite_middle;
		sprite_middle.setTexture(texture);
		sprite_middle.setTextureRect(sf::IntRect(32 * 5, 32, 32, 32));
		sprite_middle.setPosition(sf::Vector2f(m_sprite_edge_left_middle.getPosition().x + m_PosX_middle, m_sprite_edge_left_middle.getPosition().y));
		m_sprites_middle_middle.push_back(sprite_middle);
		m_PosX_middle += 31.99f;
	}

	m_sprite_edge_right_middle = m_sprite_edge_right;
	m_sprite_edge_right_middle.setPosition(sf::Vector2f(m_sprites_middle_middle[m_sprites_middle_middle.size() - 1].getPosition().x + 31.99f, m_sprite_edge_left_middle.getPosition().y));

	// Top tiles

	m_sprite_edge_left_top = m_sprite_edge_left;
	m_sprite_edge_left_top.setPosition(sf::Vector2f(window.getSize().x + 700.0f, 575.0f));

	m_PosX_top = 31.99f;

	for (int i = 0; i < 22; i++)
	{
		sf::Sprite sprite_top;
		sprite_top.setTexture(texture);
		sprite_top.setTextureRect(sf::IntRect(32 * 5, 32, 32, 32));
		sprite_top.setPosition(sf::Vector2f(m_sprite_edge_left_top.getPosition().x + m_PosX_top, m_sprite_edge_left_top.getPosition().y));
		m_sprites_middle_top.push_back(sprite_top);
		m_PosX_top += 31.99f;
	}

	m_sprite_edge_right_top = m_sprite_edge_right;
	m_sprite_edge_right_top.setPosition(sf::Vector2f(m_sprites_middle_top[m_sprites_middle_top.size() - 1].getPosition().x + 31.99f, m_sprite_edge_left_top.getPosition().y));

	// Right tiles

	m_sprite_edge_left_right.setTexture(texture);
	m_sprite_edge_left_right.setTextureRect(sf::IntRect(32 * 4, 32, 32, 32));
	m_sprite_edge_left_right.setPosition(sf::Vector2f(window.getSize().x + 900.0f, 820.0f));

	m_PosX_right = window.getSize().x + 900.0f + 31.99f;

	for (int i = 0; i < 15; i++)
	{
		sf::Sprite sprite_middle;
		sprite_middle.setTexture(texture);
		sprite_middle.setTextureRect(sf::IntRect(32 * 5, 32, 32, 32));
		sprite_middle.setPosition(sf::Vector2f(m_PosX_right, 820.0f));
		m_sprites_middle_right.push_back(sprite_middle);
		m_PosX_right += 31.99f;
	}

	m_sprite_edge_right_right.setTexture(texture);
	m_sprite_edge_right_right.setTextureRect(sf::IntRect(32 * 6, 32, 32, 32));
	m_sprite_edge_right_right.setPosition(sf::Vector2f(m_sprites_middle_right[m_sprites_middle_right.size() - 1].getPosition().x + 31.99f, 820.0f));

	// Left tiles

	m_sprites.push_back(m_sprite_edge_left);

	for (auto& sprite : m_sprites_middle)
	{
		m_sprites.push_back(sprite);
	}

	m_sprites.push_back(m_sprite_edge_right);

	// Middle tiles

	m_sprites.push_back(m_sprite_edge_left_middle);

	for (auto& sprite : m_sprites_middle_middle)
	{
		m_sprites.push_back(sprite);
	}

	m_sprites.push_back(m_sprite_edge_right_middle);

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

	// Top tiles

	m_sprites.push_back(m_sprite_edge_left_top);

	for (auto& sprite : m_sprites_middle_top)
	{
		m_sprites.push_back(sprite);
	}

	m_sprites.push_back(m_sprite_edge_right_top);

	enemy.init(window, 1400.0f, 445.0f);
}

void Set3::update(sf::RenderWindow& window, Player* player)
{
	if (player->m_isDead)
		m_friction *= .999f;

	for (int i = 0; i < m_sprites.size(); i++)
	{
		if (!player->m_isDead)
		{
			m_sprites[i].move(-.5f, .0f);

		}
		else
		{
			m_sprites[i].move(-m_friction, .0f);
		}
	}

	enemy.update(window, player);
}

void Set3::render(sf::RenderWindow& window)
{
	for (auto& sprite : m_sprites)
		window.draw(sprite);

	enemy.render(window);
}

std::vector<sf::Sprite>& Set3::getTiles()
{
	return m_sprites;
}

Enemy& Set3::getEnemy()
{
	return enemy;
}

Medkit& Set3::getMedkit()
{
	return medkit;
}

ExtraKunais& Set3::getExtraKunais()
{
	return extraKunais;
}

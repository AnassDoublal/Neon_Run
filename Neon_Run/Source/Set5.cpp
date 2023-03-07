#include "Set5.h"
#include "Player.h"

void Set5::init(sf::Texture& texture, sf::RenderWindow& window, sf::Texture& enemyTexture)
{
	srand(time(NULL));

	m_friction = .2f;

	m_sprites_middle.clear();
	m_sprites_middle_bottom.clear();
	m_sprites_middle_right.clear();
	m_sprites.clear();

	// Bottom tiles

	//m_sprite_edge_left_bottom = m_sprite_edge_left;
	m_sprite_edge_left_bottom.setTexture(texture);
	m_sprite_edge_left_bottom.setTextureRect(sf::IntRect(32 * 4, 32, 32, 32));
	m_sprite_edge_left_bottom.setPosition(sf::Vector2f(window.getSize().x, 775.0f));

	m_PosX_bottom = 31.99f;

	for (int i = 0; i < 8; i++)
	{
		sf::Sprite sprite_bottom;
		sprite_bottom.setTexture(texture);
		sprite_bottom.setTextureRect(sf::IntRect(32 * 5, 32, 32, 32));
		sprite_bottom.setPosition(sf::Vector2f(m_sprite_edge_left_bottom.getPosition().x + m_PosX_bottom, m_sprite_edge_left_bottom.getPosition().y));
		m_sprites_middle_bottom.push_back(sprite_bottom);
		m_PosX_bottom += 31.99f;
	}

	//m_sprite_edge_right_bottom = m_sprite_edge_right;
	m_sprite_edge_right_bottom.setTexture(texture);
	m_sprite_edge_right_bottom.setTextureRect(sf::IntRect(32 * 6, 32, 32, 32));
	m_sprite_edge_right_bottom.setPosition(sf::Vector2f(m_sprites_middle_bottom[m_sprites_middle_bottom.size() - 1].getPosition().x + 31.99f, m_sprite_edge_left_bottom.getPosition().y));

	// Left tiles

	m_sprite_edge_left = m_sprite_edge_left_bottom;
	m_sprite_edge_left.setPosition(sf::Vector2f(m_sprite_edge_right_bottom.getPosition().x + 100.0f, 575.0f));

	m_PosX = m_sprite_edge_left.getPosition().x + 31.99f;

	for (int i = 0; i < 8; i++)
	{
		sf::Sprite sprite_middle;
		sprite_middle.setTexture(texture);
		sprite_middle.setTextureRect(sf::IntRect(32 * 5, 32, 32, 32));
		sprite_middle.setPosition(sf::Vector2f(m_PosX, m_sprite_edge_left.getPosition().y));
		m_sprites_middle.push_back(sprite_middle);
		m_PosX += 31.99f;
	}

	m_sprite_edge_right = m_sprite_edge_right_bottom;
	m_sprite_edge_right.setPosition(sf::Vector2f(m_sprites_middle[m_sprites_middle.size() - 1].getPosition().x + 31.99f, m_sprite_edge_left.getPosition().y));

	// Right tiles

	m_sprite_edge_left_right = m_sprite_edge_left_bottom;
	m_sprite_edge_left_right.setPosition(sf::Vector2f(m_sprite_edge_right.getPosition().x + 100.0f, 375.0f));

	m_PosX_right = m_sprite_edge_left_right.getPosition().x + 31.99f;

	for (int i = 0; i < 8; i++)
	{
		sf::Sprite sprite_middle;
		sprite_middle.setTexture(texture);
		sprite_middle.setTextureRect(sf::IntRect(32 * 5, 32, 32, 32));
		sprite_middle.setPosition(sf::Vector2f(m_PosX_right, m_sprite_edge_left_right.getPosition().y));
		m_sprites_middle_right.push_back(sprite_middle);
		m_PosX_right += 31.99f;
	}

	m_sprite_edge_right_right = m_sprite_edge_right_bottom;
	m_sprite_edge_right_right.setPosition(sf::Vector2f(m_sprites_middle_right[m_sprites_middle_right.size() - 1].getPosition().x + 31.99f, m_sprite_edge_left_right.getPosition().y));

	// Bottom tiles

	m_sprites.push_back(m_sprite_edge_left_bottom);

	for (auto& sprite : m_sprites_middle_bottom)
	{
		m_sprites.push_back(sprite);
	}

	m_sprites.push_back(m_sprite_edge_right_bottom);

	// Left tiles

	m_sprites.push_back(m_sprite_edge_left);

	for (auto& sprite : m_sprites_middle)
	{
		m_sprites.push_back(sprite);
	}

	m_sprites.push_back(m_sprite_edge_right);

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

	m_positions[0] = { 550.0f, m_sprite_edge_left.getPosition().y };
	m_positions[1] = { 200.0f, m_sprite_edge_left_bottom.getPosition().y };
	m_positions[2] = { 950.0f, m_sprite_edge_left_right.getPosition().y };
	m_positions[3] = { 1050.0f, 900.0f };
	sf::Vector2f enemyPos = getNewEnemyPos();
	enemy.init(window, enemyPos.x, enemyPos.y, enemyTexture);
}

void Set5::update(sf::RenderWindow& window, Player* player)
{
	if (player->m_isDead)
		m_friction *= .999f;

	for (int i = 0; i < m_sprites.size(); i++)
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
}

void Set5::render(sf::RenderWindow& window)
{
	for (auto& sprite : m_sprites)
		window.draw(sprite);

	enemy.render(window);
}

std::vector<sf::Sprite>& Set5::getTiles()
{
	return m_sprites;
}

Enemy& Set5::getEnemy()
{
	return enemy;
}

Medkit& Set5::getMedkit()
{
	return medkit;
}

ExtraKunais& Set5::getExtraKunais()
{
	return extraKunais;
}

float Set5::getEnemyX()
{
	return m_enemyX;
}

sf::Vector2f Set5::getNewEnemyPos()
{
	int r = rand() % (sizeof(m_positions) / sizeof(sf::Vector2f));
	return m_positions[r];
}

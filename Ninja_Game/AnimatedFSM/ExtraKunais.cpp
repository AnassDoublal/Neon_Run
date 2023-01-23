#include "ExtraKunais.h"
#include "Player.h"

void ExtraKunais::init(sf::RenderWindow& window)
{
	if (!m_texture.loadFromFile("assets/images/extraKunais.png"))
	{
		// Error
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(.5f, .5f);
	m_sprite.setPosition(window.getSize().x + 620.0f, 255.0f);
}

void ExtraKunais::update(sf::RenderWindow& window, Player* player)
{
	if (!player->m_isDead)
	{
		m_sprite.move(-.2f, .0f);
	}
	else
	{
		m_friction *= .999f;
		m_sprite.move(-m_friction, .0f);

		m_isPlayerDead = true;
	}

	if (m_sprite.getPosition().x <= -m_sprite.getGlobalBounds().width)
	{
		m_sprite.setScale(.5f, .5f);
		m_sprite.setPosition(m_sprite.getPosition().x + window.getSize().x * 3, m_sprite.getPosition().y);
	}
}

void ExtraKunais::render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

sf::Sprite& ExtraKunais::getSprite()
{
	return m_sprite;
}

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
	m_sprite.setPosition(window.getSize().x + 620.0f, 655.0f);

	m_sprite.setScale(.0f, .0f);
}

void ExtraKunais::update(sf::RenderWindow& window, Player* player)
{
	if (!player->m_isDead)
	{
		m_sprite.move(-.5f, .0f);
	}
	else
	{
		m_friction *= .999f;
		m_sprite.move(-m_friction, .0f);

		m_isPlayerDead = true;
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

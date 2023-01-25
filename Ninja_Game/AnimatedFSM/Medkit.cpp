#include "Medkit.h"
#include "Player.h"

void Medkit::init(sf::RenderWindow& window)
{
	if (!m_texture.loadFromFile("assets/images/medkit.png"))
	{
		// Error
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(.1f, .1f);
	m_sprite.setPosition(window.getSize().x + 850.0f, 153.0f);

	m_sprite.setScale(.0f, .0f);
}

void Medkit::update(sf::RenderWindow& window, Player* player)
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
		m_sprite.setScale(.1f, .1f);
		m_sprite.setPosition(m_sprite.getPosition().x + window.getSize().x * 3, m_sprite.getPosition().y);
	}
}

void Medkit::render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

sf::Sprite& Medkit::getSprite()
{
	return m_sprite;
}

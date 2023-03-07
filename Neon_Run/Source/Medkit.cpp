#include "Medkit.h"
#include "Player.h"

void Medkit::init(sf::RenderWindow& window)
{
	m_friction = .2f;

	if (!m_texture.loadFromFile("assets/images/health.png"))
	{
		// Error
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(.4f, .4f);
	m_sprite.setPosition(window.getSize().x + 850.0f, 500.0f);

	m_sprite.setScale(.0f, .0f);

	if (!m_font.loadFromFile("assets/fonts/ninja.otf"))
	{
		std::cout << "Couldn't load ninja font";
	}

	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color::Green);
	m_text.setOutlineThickness(.6);
	m_text.setOutlineColor(sf::Color::Black);
	m_text.setCharacterSize(30);
	m_text.setString("+1 life");
}

void Medkit::update(sf::RenderWindow& window, Player* player)
{
	if (!player->m_isDead)
	{
		m_sprite.move(-player->m_speed, .0f);
	}
	else
	{
		m_friction *= .999f;
		m_sprite.move(-m_friction, .0f);

		m_isPlayerDead = true;
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

void Medkit::displayExtraLife(sf::RenderWindow& window, Player* player)
{
	if (!m_hasRestartedClock)
	{
		m_textClock.restart();
		m_hasRestartedClock = true;
	}

	m_text.setPosition(player->getAnimatedSprite().getPosition().x + m_text.getGlobalBounds().width / 2.0f,
					   player->getAnimatedSprite().getPosition().y - 50.0f - m_speed);

	m_speed += .1f;

	window.draw(m_text);

	if (m_textClock.getElapsedTime().asSeconds() > 1.5f)
	{
		player->m_hasCollectedMedkit = false;
		m_hasRestartedClock = false;
		m_speed = .1f;
		m_textClock.restart();
	}
}

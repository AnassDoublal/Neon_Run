#include "Light.h"

candle::LightingArea fog(candle::LightingArea::FOG,
	sf::Vector2f(0.f, 0.f),
	sf::Vector2f(64, 36));

void Light::init()
{
	m_light.setRange(150);

	fog.setAreaColor(sf::Color::Color(0, 0, 0, 127));
	fog.setScale(30.0f, 30.0f);
}

void Light::update(Player& t_player)
{
	m_light.setPosition(t_player.getAnimatedSprite().getPosition().x + t_player.getAnimatedSprite().getGlobalBounds().width / 2.0f,
						t_player.getAnimatedSprite().getPosition().y + t_player.getAnimatedSprite().getGlobalBounds().height / 2.0f);
}

void Light::render(sf::RenderWindow& t_window)
{
	fog.clear();
	fog.draw(m_light);
	fog.display();

	t_window.draw(fog);
}

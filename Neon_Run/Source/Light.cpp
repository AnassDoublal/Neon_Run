#include "Light.h"

candle::LightingArea fog(candle::LightingArea::FOG,
	sf::Vector2f(0.f, 0.f),
	sf::Vector2f(64, 36));

void Light::init()
{
	m_light.setRange(150);
	m_light.setIntensity(.5f);

	fog.setAreaColor(sf::Color::Color(0, 0, 0, 127));
	fog.setScale(30.0f, 30.0f);
}

void Light::update(Player& t_player)
{
	m_light.setPosition(t_player.getAnimatedSprite().getPosition().x + t_player.getAnimatedSprite().getGlobalBounds().width / 2.0f,
						t_player.getAnimatedSprite().getPosition().y + t_player.getAnimatedSprite().getGlobalBounds().height / 2.0f);

}

void Light::render(sf::RenderWindow& t_window, std::vector<candle::RadialLight>& t_lights)
{
	fog.clear();
	fog.draw(m_light);
	for (size_t i = 0; i < t_lights.size(); i++)
		fog.draw(t_lights[i]);
	fog.display();

	t_window.draw(fog);
}

#include "EnemyScore.h"

EnemyScore::EnemyScore(float t_scoreBonus)
{
	if (!m_font.loadFromFile("assets/fonts/ninja.otf"))
	{
		std::cout << "Couldn't load ninja font";
	}

	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color::Red);
	m_text.setOutlineThickness(.6);
	m_text.setOutlineColor(sf::Color::Black);
	m_text.setCharacterSize(30);
	m_text.setString("+" + std::to_string(static_cast<int>(t_scoreBonus)));
}

void EnemyScore::update(Enemy* enemy, std::vector<std::shared_ptr<EnemyScore>>& vector, std::vector<int>& hitEnemies)
{
	if (!m_hasRestartedClock)
	{
		m_textClock.restart();
		m_hasRestartedClock = true;
	}

	m_text.setPosition(enemy->getAnimatedSprite().getPosition().x - m_text.getGlobalBounds().width,
					   enemy->getAnimatedSprite().getPosition().y - 50.0f - m_speed);

	if (m_text.getPosition().x > 1920.0f)
		m_text.setScale(.0f, .0f);

	m_speed += .05f;

	if (m_textClock.getElapsedTime().asSeconds() > 1.5f)
	{
		vector.erase(vector.begin());
		hitEnemies.erase(hitEnemies.begin());
		m_hasRestartedClock = false;
		m_speed = .1f;
		m_textClock.restart();
	}
}

void EnemyScore::render(sf::RenderWindow& window)
{
	window.draw(m_text);
}

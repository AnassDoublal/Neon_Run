#include "Score.h"

void Score::init(sf::RenderWindow& window)
{
	if (!m_font.loadFromFile("assets/fonts/ninja.otf"))
	{
		std::cout << "Couldn't load ninja font";
	}

	m_score = 0;
	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(30.0f);
	m_scoreText.setString(std::to_string(m_score));
	m_scoreText.setPosition(window.getSize().x - m_scoreText.getGlobalBounds().width - 20.0f, 20.0f);
	m_scoreText.setFillColor(sf::Color::Black);
}

void Score::update(sf::RenderWindow& window, float speed)
{
	m_score += .1;

	m_scoreText.setString("Score : " + std::to_string(static_cast<int>(m_score)));
	m_scoreText.setPosition(window.getSize().x - m_scoreText.getGlobalBounds().width - 20.0f, 20.0f);
}

void Score::render(sf::RenderWindow& window)
{
	window.draw(m_scoreText);
}

void Score::bonus(float t_bonus)
{
	m_score += t_bonus;
}

int Score::getScore()
{
	return static_cast<int>(m_score);
}

#include "Reward.h"

void Reward::init(sf::RenderWindow& window, int t_place)
{
	if (!m_font.loadFromFile("assets/fonts/ninja.otf"))
	{
		std::cout << "Couldn't load ninja font";
	}

	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color(255, 255, 255, 0));
	m_text.setCharacterSize(30);

	m_place = t_place;

	m_text.setPosition(window.getSize().x / 2.0f - m_text.getGlobalBounds().width / 2.0f, 50.0f * m_place + 50 * (m_place - 1));
}

void Reward::update(sf::RenderWindow& window, std::vector<std::shared_ptr<Reward>>& rewards, int i)
{
	if (m_alpha <= 255.0f)
		m_alpha += .5f;
		
	m_text.setFillColor(sf::Color(255, 255, 255, m_alpha));

	if (m_text.getPosition().y >= 25.0f + 100 * (m_place - 1))
		m_text.setPosition(m_text.getPosition().x, m_text.getPosition().y - .2f);
	else
	{
		if (i == 0)
			m_text.setPosition(m_text.getPosition().x, 25.0f);
		else
			m_text.setPosition(m_text.getPosition().x, 25.0f + 100.0f * i);
	}

	if (!m_hasResetRewardClock)
	{
		m_rewardClock.restart();
		m_hasResetRewardClock = true;
	}

	if (m_rewardClock.getElapsedTime().asSeconds() > 3.0f)
	{
		m_text.setFillColor(sf::Color(255, 255, 255, 0));
		rewards.erase(rewards.begin() + i);
	}
}

void Reward::render(sf::RenderWindow& window)
{
	window.draw(m_text);
}

sf::Text& Reward::getText()
{
	return m_text;
}

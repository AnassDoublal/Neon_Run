#include "DoubleKill.h"

void DoubleKill::init(sf::RenderWindow& window)
{
	if (!m_font.loadFromFile("assets/fonts/ninja.otf"))
	{
		std::cout << "Couldn't load ninja font";
	}

	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color::Yellow);
	m_text.setOutlineThickness(2);
	m_text.setOutlineColor(sf::Color::Black);
	m_text.setCharacterSize(40);
	m_text.setString("DOUBLE KILL\n     +2000");
	m_text.setOrigin(m_text.getGlobalBounds().width / 2.0f, m_text.getGlobalBounds().height / 2.0f);
	m_text.setPosition(window.getSize().x / 2.0f, 100.0f);
	m_text.setScale(.0f, .0f);
}

void DoubleKill::update(sf::RenderWindow& window)
{
	if(m_text.getScale().x <= 1.0f)
		m_text.setScale(m_text.getScale().x +.001f, m_text.getScale().y + .001f);
}

void DoubleKill::render(sf::RenderWindow& window)
{
	window.draw(m_text);
}

sf::Text& DoubleKill::getText()
{
	return m_text;
}

#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"

class Score
{
public:
	void init(sf::RenderWindow&);
	void update(sf::RenderWindow&, float);
	void render(sf::RenderWindow&);
	void bonus(float);
	int getScore();
private:
	sf::Font m_font;
	sf::Text m_scoreText;
	float m_score;
};
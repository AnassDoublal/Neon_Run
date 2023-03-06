#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"

class Reward
{
public:
	void init(sf::RenderWindow&, int);
	void update(sf::RenderWindow&, std::vector<std::shared_ptr<Reward>>&, int);
	void render(sf::RenderWindow&);
	sf::Text& getText();
private:
	sf::Font m_font;
	sf::Text m_text;
	float m_alpha = .0f;
	sf::Clock m_rewardClock;
	bool m_hasResetRewardClock = false;
	int m_place;
};
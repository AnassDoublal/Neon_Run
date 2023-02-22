#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"
#include "Enemy.h"

class EnemyScore {
public:
	EnemyScore(float);
	void update(Enemy*, std::vector<std::shared_ptr<EnemyScore>>&, std::vector<int>&);
	void render(sf::RenderWindow&);
private:
	sf::Font m_font;
	sf::Text m_text;
	sf::Clock m_textClock;
	bool m_hasRestartedClock = false;
	float m_speed = .1f;
};
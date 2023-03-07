#pragma once
#include "SFML/Graphics.hpp"
#include "Candle/RadialLight.hpp"
#include "Candle/LightingArea.hpp"
#include "Player.h"
#include "Enemy.h"

class Light
{
public:
	void init();
	void update(Player&);
	void render(sf::RenderWindow&, std::vector<candle::RadialLight>&);
private:
	candle::RadialLight m_light;
};
#pragma once
#include "SFML/Graphics.hpp"
#include "Candle/RadialLight.hpp"
#include "Candle/LightingArea.hpp"
#include "Player.h"

class Light
{
public:
	void init();
	void update(Player&);
	void render(sf::RenderWindow&);
private:
	candle::RadialLight m_light;
};
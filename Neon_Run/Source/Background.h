#pragma once
#include "SFML/Graphics.hpp"

class Background {
public:
	void init();
	void update();
	void render(sf::RenderWindow&);
private:
	int m_nbLayers = 8;
	int m_nbSplit = 3;

	sf::Texture m_textures[8][3];
	sf::Sprite m_layers[8][3];
};
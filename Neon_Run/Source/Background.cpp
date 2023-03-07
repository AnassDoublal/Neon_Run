#include "Background.h"

void Background::init()
{
	for (size_t i = 0; i < m_nbLayers; i++)
	{
		for (size_t j = 0; j < m_nbSplit; j++)
		{
			if (!m_textures[i][j].loadFromFile("assets/background/" + std::to_string(i+1) + "/" + std::to_string(j+1) + ".png"))
			{
				// Error
			}

			m_layers[i][j].setTexture(m_textures[i][j]);
			m_layers[i][j].setScale(4.0f, 4.0f);
			m_layers[i][j].setPosition(1920.0f / 4.0f * j, .0f);
		}
	}
}

void Background::update()
{
}

void Background::render(sf::RenderWindow& window)
{
	for (size_t i = 0; i < m_nbLayers; i++)
	{
		for (size_t j = 0; j < m_nbSplit; j++)
		{
			window.draw(m_layers[i][j]);
		}
	}
}

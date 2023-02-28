#include "SFML/Graphics.hpp"
#include "Game.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Player Finite State Machine");

	Game game;
	game.init(window);

	while (window.isOpen())
	{
		game.update(window);
		game.render(window);
	}
}
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Menu.h"
#include "GameState.h"
#include "Pause.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Neon Rush");

	Menu menu;
	Game game;
	Pause pause;

	GAME_STATE gameState = GAME_STATE::MENU;

	menu.init();
	pause.init(window);

	audio.playMenuMusic();

	while (window.isOpen())
	{
		window.clear();

		switch (gameState)
		{
			case GAME_STATE::MENU:
				menu.update(window, gameState, game, audio);
				menu.render(window);
				break;

			case GAME_STATE::GAME:
				game.update(window, gameState, audio);
				game.render(window);
				break;

			case GAME_STATE::PAUSE:
				pause.update(gameState, game, window, audio);
				game.render(window);
				pause.render(window);
				break;
		}

		window.display();
	}
}

//#include <SFML/Graphics.hpp>
//#include <Candle/RadialLight.hpp>
//
//int main() {
//    // create window
//    sf::RenderWindow w(sf::VideoMode(400, 400), "app");
//
//    // create a light source
//    candle::RadialLight light;
//    light.setRange(150);
//
//    // create an edge pool
//    candle::EdgeVector edges;
//    edges.emplace_back(sf::Vector2f(200.f, 100.f),
//        sf::Vector2f(200.f, 300.f));
//
//    // main loop
//    while (w.isOpen()) {
//        sf::Event e;
//        while (w.pollEvent(e)) {
//            if (e.type == sf::Event::Closed) {
//                w.close();
//            }
//            else if (e.type == sf::Event::MouseMoved) {
//                sf::Vector2f mp(sf::Mouse::getPosition(w));
//                light.setPosition(mp);
//                light.castLight(edges.begin(), edges.end());
//            }
//        }
//
//        w.clear();
//        w.draw(light);
//        w.display();
//    }
//    return 0;
//}
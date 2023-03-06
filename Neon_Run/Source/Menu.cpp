#include "Menu.h"

void Menu::init() {
	bg.loadFromFile("assets/menu/bg.png");
	exit.loadFromFile("assets/menu/Exit.png");
	exitClicked.loadFromFile("assets/menu/ExitClicked.png");
	exitHovered.loadFromFile("assets/menu/ExitHover.png");
	play.loadFromFile("assets/menu/Play.png");
	playClicked.loadFromFile("assets/menu/PlayClicked.png");
	playHovered.loadFromFile("assets/menu/PlayHover.png");

	sBg.setTexture(bg);
	sExit.setTexture(exit);
	sExitClicked.setTexture(exitClicked);
	sExitHovered.setTexture(exitHovered);
	sPlay.setTexture(play);
	sPlayClicked.setTexture(playClicked);
	sPlayHovered.setTexture(playHovered);

	sPlay.setPosition(1030.0f, 320.0f);
	sPlayClicked.setPosition(1030.0f, 320.0f);
	sPlayHovered.setPosition(1030.0f, 320.0f);

	sExit.setPosition(1070.0f, 550.0f);
	sExitClicked.setPosition(1070.0f, 550.0f);
	sExitHovered.setPosition(1070.0f, 550.0f);
}

void Menu::update(sf::RenderWindow& window, GAME_STATE& gameState, Game& game, Audio& audio) {
	sf::Event event;
	while (window.pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
			window.close();
	}

	if (sPlay.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y))
	{
		isHoveringPlay = true;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			audio.m_menuMusic.stop();
			//isClickingPlay = true;
			game.init(window, audio);
			gameState = GAME_STATE::GAME;
		}
	}
	else
		isHoveringPlay = false;

	if (sExit.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y))
	{
		isHoveringExit = true;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//isClickingExit = true;
			window.close();
		}
	}
	else
		isHoveringExit = false;
}

void Menu::render(sf::RenderWindow& window) {
	window.draw(sBg);
	window.draw(sExit);
	if(isClickingExit)
		window.draw(sExitClicked);
	if(isHoveringExit)
		window.draw(sExitHovered);
	window.draw(sPlay);
	if(isClickingPlay)
		window.draw(sPlayClicked);
	if(isHoveringPlay)
		window.draw(sPlayHovered);
}
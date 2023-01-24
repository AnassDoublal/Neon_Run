#include <Defines.h>

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Player.h>
#include <Events.h>
#include <Debug.h>
#include <Tiles.h>
#include <Set1.h>
#include <Set2.h>
#include "circle.h"
#include "Rectangle.h"
#include "EndScreen.h"
#include "Audio.h"

using namespace std;

//bool circle_to_circle(Circle a, Circle b)
//{
//	float distance = 0.0f;
//	float radiusAdd = 0.0f;
//
//	distance = sqrt((b.getX() - a.getX()) * (b.getX() - a.getX()) + (b.getY() - a.getY()) * (b.getY() - a.getY()));
//	radiusAdd = a.getRadius() + b.getRadius();
//
//	return(distance * 2.0f < radiusAdd);
//}

bool valueInRange(int value, int min, int max)
{
	return (value >= min) && (value <= max);
}

bool rectangle_to_rectangle(Rectangle& a, Rectangle& b)
{
	bool xOverlap = valueInRange(a.getX(), b.getX(), b.getX() + b.getWidth()) || valueInRange(b.getX(), a.getX(), a.getX() + a.getWidth());
	bool yOverlap = valueInRange(a.getY(), b.getY(), b.getY() + b.getHeight()) || valueInRange(b.getY(), a.getY(), a.getY() + a.getHeight());
	return xOverlap && yOverlap;
}

int main()
{
	srand(time(NULL));

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Player Finite State Machine");

	window.setKeyRepeatEnabled(false);

#pragma region TextureLoading

	// Load a sprite to display
	sf::Texture player_texture;
	if (!player_texture.loadFromFile(PLAYER_SPRITES)) {
		DEBUG_MSG("Failed to load file");
		if (!player_texture.loadFromFile(ERROR_SPRITES)) {
			return EXIT_FAILURE;
		}
	}

	sf::Texture bg_texture;
	if (!bg_texture.loadFromFile("assets\\bg\\1.png")) {
		DEBUG_MSG("Failed to load file");
	}

	sf::Texture tile_texture;
	if (!tile_texture.loadFromFile("assets\\tiles\\tiles.png")) {
		DEBUG_MSG("Failed to load file");
	}

#pragma endregion

#pragma region AnimatedSprite

	// Setup Players Default Animated Sprite
	AnimatedSprite player_animated_sprite(player_texture);

	sf::Sprite bg_sprite;
	bg_sprite.setTexture(bg_texture);
	bg_sprite.setScale(sf::Vector2f(.6f, .6f));

	sf::Sprite bg_sprite_copy;
	bg_sprite_copy.setTexture(bg_texture);
	bg_sprite_copy.setOrigin(sf::Vector2f(bg_sprite_copy.getGlobalBounds().width / 2.0f, bg_sprite_copy.getGlobalBounds().height / 2.0f));
	bg_sprite_copy.setPosition(sf::Vector2f(bg_sprite.getGlobalBounds().width + bg_sprite.getGlobalBounds().width/2.0f - 1.0f, bg_sprite.getGlobalBounds().height / 2.0f));
	bg_sprite_copy.setScale(sf::Vector2f(-.6f, .6f));

	float bg_friction = .05f;

	bool allowPositionChangeBg1 = true;
	bool allowPositionChangeBg2 = true;

	std::vector<sf::Sprite> tiles_ground;
	float ground_PosX = .0f;

	std::vector<sf::Sprite> tiles_ground_1;
	float ground_1_PosX = .0f;

	for (int i = 0; i < 25; i++)
	{
		sf::Sprite ground;
		ground.setTexture(tile_texture);
		ground.setTextureRect(sf::IntRect(32, 32, 32, 32));
		ground.setScale(sf::Vector2f(1.5f, 1.5f));
		ground.setPosition(sf::Vector2f(ground_PosX, 536.0f));
		tiles_ground.push_back(ground);
		ground_PosX += 32.0f;

		sf::Sprite ground_1;
		ground_1.setTexture(tile_texture);
		ground_1.setTextureRect(sf::IntRect(32, 64, 32, 32));
		ground_1.setScale(sf::Vector2f(1.5f, 1.5f));
		ground_1.setPosition(sf::Vector2f(ground_1_PosX, 568.0f));
		tiles_ground_1.push_back(ground_1);
		ground_1_PosX += 32.0f;
	}

	std::vector<sf::Sprite> tiles_ground_copy = tiles_ground;
	std::vector<sf::Sprite> tiles_ground_1_copy = tiles_ground_1;

	for (int i = 0; i < 25; i++)
	{
		tiles_ground_copy[i].setPosition(tiles_ground_copy[i].getPosition().x + 32.0f * 25.0f, 536.0f);
		tiles_ground_1_copy[i].setPosition(tiles_ground_1_copy[i].getPosition().x + 32.0f * 25.0f, 568.0f);
	}

	bool allowPositionChangeGround1 = true;
	bool allowPositionChangeGround2 = true;

#pragma endregion

	Tiles* tilesPtr = nullptr;

	Set1 set1;
	Set2 set2;

	set1.init(tile_texture, window);
	set2.init(tile_texture, window);

	int randomSet = rand() % 2 + 1;

	switch (randomSet)
	{
		case 1:
			tilesPtr = &set1;
			break;
		case 2:
			tilesPtr = &set2;
			break;
	}

	for (int i = 0; i < tilesPtr->getTiles().size(); i++)
	{
		tilesPtr->getTiles()[i].setScale(1.0f, 1.0f);
	}

	//tilesPtr->init(tile_texture, window);

	//std::vector<sf::Sprite> tiles = tilesPtr->getTiles();

	//std::cout << *(tiles).size() << "\n";

	Player player(player_animated_sprite, tilesPtr);

	player.getAnimatedSprite().setPosition(sf::Vector2f(50.0f, 405.0f));

	sf::Texture daggerTexture;

	if (!daggerTexture.loadFromFile("assets/Kunai.png"))
	{
		DEBUG_MSG("Failed to load kunai");
	}

	for (int i = 0; i < 50; i++)
	{
		sf::Sprite dagger;
		dagger.setTexture(daggerTexture);
		dagger.setPosition(-100.0f, -100.0f);
		dagger.setScale(.5f, .5f);
		player.m_daggers.push_back(dagger);
	}

	bool daggerThrow = false;

	//std::vector<sf::RectangleShape> rDaggersReps;

	for (int i = 0; i < 50; i++)
	{
		Rectangle rDagger(player.m_daggers[i].getPosition().x,
						  player.m_daggers[i].getPosition().y,
						  player.m_daggers[i].getGlobalBounds().width,
						  player.m_daggers[i].getGlobalBounds().height);

		player.m_daggers_rectangles.push_back(rDagger);

		/*sf::RectangleShape rDaggerRep;
		rDaggerRep.setPosition(-100.0f, -100.0f);
		rDaggerRep.setSize(sf::Vector2f(player.m_daggers[i].getGlobalBounds().width, player.m_daggers[i].getGlobalBounds().height));
		rDaggerRep.setFillColor(sf::Color::Green);

		rDaggersReps.push_back(rDaggerRep);*/
	}

	/*Circle cPlayer(player.getAnimatedSprite().getPosition().x,
				   player.getAnimatedSprite().getPosition().y,
				   player.getAnimatedSprite().getGlobalBounds().height / 2.0f);

	sf::CircleShape cPlayerRep;

	cPlayerRep.setRadius(player.getAnimatedSprite().getGlobalBounds().height / 2.0f);
	cPlayerRep.setFillColor(sf::Color::Yellow);*/

	Rectangle rPlayer(player.getAnimatedSprite().getPosition().x, 
					  player.getAnimatedSprite().getPosition().y, 
					  player.getAnimatedSprite().getGlobalBounds().width,
					  player.getAnimatedSprite().getGlobalBounds().height);

	sf::RectangleShape rPlayerRep;
	rPlayerRep.setSize(sf::Vector2f(player.getAnimatedSprite().getGlobalBounds().width, player.getAnimatedSprite().getGlobalBounds().height));
	rPlayerRep.setFillColor(sf::Color::Yellow);

	sf::Font font;
	if (!font.loadFromFile("assets/fonts/ninja.otf"))
	{
		std::cout << "Couldn't load ninja font";
	}

	sf::Text livesText;
	livesText.setFont(font);
	livesText.setCharacterSize(30.0f);
	livesText.setString("Lives :");
	livesText.setPosition(20.0f, 20.0f);
	livesText.setFillColor(sf::Color::Black);

	sf::Texture lives_texture;

	if(!lives_texture.loadFromFile("assets/Idle.png"))
	{
		DEBUG_MSG("Failed to load lives texture");
	}

	std::vector<sf::Sprite> lives;

	for (int i = 0; i < 3; i++)
	{
		sf::Sprite life;
		life.setTexture(lives_texture);
		life.setTextureRect(sf::IntRect(0, 0, 211, 200));
		life.setScale(.2f, .2f);
		lives.push_back(life);
	}

	lives[0].setPosition(115.0f, 20.0f);
	lives[1].setPosition(165.0f, 20.0f);
	lives[2].setPosition(215.0f, 20.0f);

	bool minusOneLife = false;

	int enemiesHit = 0;

	sf::Text enemiesHitText;
	enemiesHitText.setFont(font);
	enemiesHitText.setCharacterSize(30.0f);
	enemiesHitText.setString(std::to_string(enemiesHit));
	enemiesHitText.setPosition(window.getSize().x - enemiesHitText.getGlobalBounds().width - 20.0f, 20.0f);
	enemiesHitText.setFillColor(sf::Color::Black);

	sf::Texture enemyHUD_texture;

	if (!enemyHUD_texture.loadFromFile("assets/EnemySpriteSheet.png"))
	{
		DEBUG_MSG("Failed to load lives texture");
	}

	sf::Sprite enemyHUD;
	enemyHUD.setTexture(enemyHUD_texture);
	enemyHUD.setTextureRect(sf::IntRect(3900, 0, 211, 200));
	enemyHUD.setScale(.2f, .2f);
	enemyHUD.setPosition(enemiesHitText.getPosition().x - enemyHUD.getGlobalBounds().width - 10.0f, 20.0f);

	int numDaggers = 50;
	bool minusOneDagger = true;

	sf::Text daggersHUDText;
	daggersHUDText.setFont(font);
	daggersHUDText.setCharacterSize(30.0f);
	daggersHUDText.setString("0");
	daggersHUDText.setPosition(window.getSize().x - daggersHUDText.getGlobalBounds().width - 20.0f, 80.0f);
	daggersHUDText.setFillColor(sf::Color::Black);

	sf::Texture daggersHUD_texture;

	if (!daggersHUD_texture.loadFromFile("assets/Kunai.png"))
	{
		DEBUG_MSG("Failed to load lives texture");
	}

	sf::Sprite daggersHUD;
	daggersHUD.setTexture(daggersHUD_texture);
	daggersHUD.setScale(.4f, .4f);
	daggersHUD.setRotation(-20);
	daggersHUD.setPosition(daggersHUDText.getPosition().x - daggersHUD.getGlobalBounds().width - 10.0f, 105.0f);

	EndScreen endScreen(window, player);

	Audio audio;
	audio.playBgMusic();

	sf::Texture bloodTexture;

	if (!bloodTexture.loadFromFile("assets/images/blood.png"))
	{
		// Error
	}

	sf::Sprite playerBlood;
	playerBlood.setTexture(bloodTexture);
	playerBlood.setTextureRect(sf::IntRect(0, 0, 512, 512));
	playerBlood.setScale(.4f, .4f);
	playerBlood.setPosition(-2000.0f, -2000.0f);

	sf::Sprite enemyBlood;
	enemyBlood.setTexture(bloodTexture);
	enemyBlood.setTextureRect(sf::IntRect(0, 0, 512, 512));
	enemyBlood.setScale(.4f, .4f);
	enemyBlood.setPosition(-2000.0f, -2000.0f);

	int playerBloodFrame = 0;
	int enemyBloodFrame = 0;

	bool isPlayerHit = false;
	bool isEnemyHit = false;

	int numExtraKunais = 0;

	std::cout << sf::Joystick::ButtonCount << "\n";

	gpp::Events input;

	// Start the game loop
	while (window.isOpen())
	{
		/*cPlayer.updateX(player.getAnimatedSprite().getPosition().x, .0f);
		cPlayer.updateY(player.getAnimatedSprite().getPosition().y);

		cPlayerRep.setPosition(player.getAnimatedSprite().getPosition().x, 
							   player.getAnimatedSprite().getPosition().y);*/

		/*if (circle_to_circle(cPlayer, tilesPtr->getEnemyCircle()))
		{
			std::cout << "COLLISION BETWEEN THE BOIS\n";
		}*/

		rPlayer.updateX(player.getAnimatedSprite().getPosition().x, .0f);
		rPlayer.updateY(player.getAnimatedSprite().getPosition().y);

		rPlayerRep.setPosition(player.getAnimatedSprite().getPosition().x, player.getAnimatedSprite().getPosition().y);

		if (rectangle_to_rectangle(rPlayer, tilesPtr->getEnemy().m_rectangle))
		{
			if (player.m_isAttacking)
			{
				std::cout << "RIP ENEMY NINJA\n";
				//tilesPtr->getEnemy().getAnimatedSprite().setScale(.0f, .0f);
				tilesPtr->getEnemy().m_rectangle.setWidth(.0f);
				tilesPtr->getEnemy().m_rectangle.setHeight(.0f);
				tilesPtr->getEnemy().m_isDead = true;

				enemiesHit++;

				audio.playHurtSound();
				
				isEnemyHit = true;
			}
		}

		if (player.getAnimatedSprite().getGlobalBounds().intersects(tilesPtr->getMedkit().getSprite().getGlobalBounds()))
		{
			if (lives.size() < 3)
			{
				sf::Sprite life;
				life.setTexture(lives_texture);
				life.setTextureRect(sf::IntRect(0, 0, 211, 200));
				life.setScale(.2f, .2f);
				life.setPosition(lives[lives.size() - 1].getPosition().x + 50.0f, 20.0f);
				lives.push_back(life);

				tilesPtr->getMedkit().getSprite().setScale(.0f, .0f);
				player.m_health++;
			}
		}

		if (player.getAnimatedSprite().getGlobalBounds().intersects(tilesPtr->getExtraKunais().getSprite().getGlobalBounds()))
		{
			if (player.m_daggers.size() < 50)
			{
				if (player.m_daggers.size() > 47)
				{
					numExtraKunais = 50 - player.m_daggers.size();
				}
				else
					numExtraKunais = 3;

				numDaggers += numExtraKunais;

				for (int i = 0; i < numExtraKunais; i++)
				{
					sf::Sprite dagger;
					dagger.setTexture(daggerTexture);
					dagger.setPosition(-100.0f, -100.0f);
					dagger.setScale(.5f, .5f);
					player.m_daggers.push_back(dagger);

					Rectangle rDagger(player.m_daggers[i].getPosition().x,
									  player.m_daggers[i].getPosition().y,
									  player.m_daggers[i].getGlobalBounds().width,
									  player.m_daggers[i].getGlobalBounds().height);

					player.m_daggers_rectangles.push_back(rDagger);
				}

				tilesPtr->getExtraKunais().getSprite().setScale(.0f, .0f);
			}
		}

		if (isEnemyHit)
		{
			enemyBlood.setPosition(tilesPtr->getEnemy().getAnimatedSprite().getPosition().x - tilesPtr->getEnemy().getAnimatedSprite().getGlobalBounds().width, tilesPtr->getEnemy().getAnimatedSprite().getPosition().y);

			enemyBloodFrame++;

			if (enemyBlood.getTextureRect().left < 3072)
			{
				if (enemyBloodFrame > 60)
				{
					enemyBlood.setTextureRect(sf::IntRect(enemyBlood.getTextureRect().left + 512, 0, 512, 512));
					enemyBloodFrame = 0;
				}
			}
			else
			{
				enemyBlood.setTextureRect(sf::IntRect(0, 0, 512, 512));
				enemyBlood.setPosition(-2000.0f, -2000.0f);
				isEnemyHit = false;
			}
		}

		if (isPlayerHit)
		{
			playerBlood.setPosition(player.getAnimatedSprite().getPosition().x - player.getAnimatedSprite().getGlobalBounds().width / 2.0f, player.getAnimatedSprite().getPosition().y);

			playerBloodFrame++;

			if (playerBlood.getTextureRect().left < 3072)
			{
				if (playerBloodFrame > 60)
				{
					playerBlood.setTextureRect(sf::IntRect(playerBlood.getTextureRect().left + 512, 0, 512, 512));
					playerBloodFrame = 0;
				}
			}
			else
			{
				playerBlood.setTextureRect(sf::IntRect(0, 0, 512, 512));
				playerBlood.setPosition(-2000.0f, -2000.0f);
				isPlayerHit = false;
			}
		}

		if (player.m_daggers_rectangles.size() > 0)
		{
			if (rectangle_to_rectangle(player.m_daggers_rectangles[0], tilesPtr->getEnemy().m_rectangle))
			{
				std::cout << "RIP ENEMY NINJA\n";
				//tilesPtr->getEnemy().getAnimatedSprite().setScale(.0f, .0f);
				tilesPtr->getEnemy().m_rectangle.setWidth(.0f);
				tilesPtr->getEnemy().m_rectangle.setHeight(.0f);
				tilesPtr->getEnemy().m_isDead = true;

				enemiesHit++;
				player.m_shotsHit++;

				audio.playHurtSound();

				isEnemyHit = true;
			}
		}

		enemiesHitText.setString(std::to_string(enemiesHit));
		enemiesHitText.setPosition(window.getSize().x - enemiesHitText.getGlobalBounds().width - 20.0f, 20.0f);

		enemyHUD.setPosition(enemiesHitText.getPosition().x - enemyHUD.getGlobalBounds().width - 10.0f, 20.0f);
		
		daggersHUDText.setString(std::to_string(numDaggers));
		daggersHUDText.setPosition(window.getSize().x - daggersHUDText.getGlobalBounds().width - 20.0f, 80.0f);

		daggersHUD.setPosition(daggersHUDText.getPosition().x - daggersHUD.getGlobalBounds().width - 10.0f, 105.0f);

		if (tilesPtr->getEnemy().m_daggers_rectangles.size() > 0)
		{
			if (rectangle_to_rectangle(tilesPtr->getEnemy().m_daggers_rectangles[0], rPlayer))
			{
				if (!minusOneLife && lives.size() > 0)
				{
					std::cout << "OUCH THAT HURTS\n";
					lives.pop_back();
					player.m_health--;
					minusOneLife = true;

					audio.playHurtSound();

					isPlayerHit = true;
				}
			}
			else
			{
				minusOneLife = false;
			}
		}

		if (bg_sprite_copy.getPosition().x <= bg_sprite_copy.getGlobalBounds().width / 2.0f && allowPositionChangeBg1)
		{
			bg_sprite.setPosition(sf::Vector2f(bg_sprite.getGlobalBounds().width - 1.0f, 0.0f));
			allowPositionChangeBg1 = false;
			allowPositionChangeBg2 = true;
		}

		if (bg_sprite.getPosition().x <= 0.0f && allowPositionChangeBg2)
		{
			bg_sprite_copy.setPosition(sf::Vector2f(bg_sprite.getGlobalBounds().width + bg_sprite.getGlobalBounds().width / 2.0f - 1.0f, bg_sprite.getGlobalBounds().height / 2.0f));
			allowPositionChangeBg1 = true;
			allowPositionChangeBg2 = false;
		}

		if (tiles_ground_copy[0].getPosition().x <= 0.0f && allowPositionChangeGround1)
		{
			for (int i = 0; i < 25; i++)
			{
				tiles_ground[i].setPosition(tiles_ground_copy[i].getPosition().x + 32.0f * 25.0f, 536.0f);
				tiles_ground_1[i].setPosition(tiles_ground_1_copy[i].getPosition().x + 32.0f * 25.0f, 568.0f);
				allowPositionChangeGround1 = false;
				allowPositionChangeGround2 = true;
			}
		}

		if (tiles_ground[0].getPosition().x <= 0.0f && allowPositionChangeGround2)
		{
			for (int i = 0; i < 25; i++)
			{
				tiles_ground_copy[i].setPosition(tiles_ground[i].getPosition().x + 32.0f * 25.0f, 536.0f);
				tiles_ground_1_copy[i].setPosition(tiles_ground_1[i].getPosition().x + 32.0f * 25.0f, 568.0f);
				allowPositionChangeGround1 = true;
				allowPositionChangeGround2 = false;
			}
		}

		if (!player.m_isDead)
		{
			bg_sprite.move(sf::Vector2f(-.05f, .0f));
			bg_sprite_copy.move(sf::Vector2f(-.05f, .0f));

			for (int i = 0; i < 25; i++)
			{
				tiles_ground[i].move(sf::Vector2f(-.2f, .0f));
				tiles_ground_1[i].move(sf::Vector2f(-.2f, .0f));
				tiles_ground_copy[i].move(sf::Vector2f(-.2f, .0f));
				tiles_ground_1_copy[i].move(sf::Vector2f(-.2f, .0f));
			}
		}
		else
		{
			bg_friction *= .999f;
			bg_sprite.move(sf::Vector2f(-bg_friction, .0f));
			bg_sprite_copy.move(sf::Vector2f(-bg_friction, .0f));

			for (int i = 0; i < 25; i++)
			{
				tiles_ground[i].move(sf::Vector2f(-bg_friction, .0f));
				tiles_ground_1[i].move(sf::Vector2f(-bg_friction, .0f));
				tiles_ground_copy[i].move(sf::Vector2f(-bg_friction, .0f));
				tiles_ground_1_copy[i].move(sf::Vector2f(-bg_friction, .0f));
			}

			endScreen.update(window, enemiesHit);
		}

		//std::cout << "ISGROUNDED : " << player.m_isGrounded << "\n";
		if (player.m_isGrounded)
		{
			player.m_friction = 1.0f;
		}

		tilesPtr->update(window, &player);

		if (tilesPtr->getTiles()[tilesPtr->getTiles().size() - 1].getPosition().x < -31)
		{
			std::cout << "WE'RE IN !!! POGCHAMP\n";

			for (int i = 0; i < tilesPtr->getTiles().size(); i++)
			{
				tilesPtr->getTiles()[i].setScale(.0f, .0f);
			}

			randomSet = rand() % 2 + 1;

			switch (randomSet)
			{
			case 1:
				tilesPtr = &set1;
				break;
			case 2:
				tilesPtr = &set2;
				break;
			}

			for (int i = 0; i < tilesPtr->getTiles().size(); i++)
			{
				tilesPtr->getTiles()[i].setScale(1.0f, 1.0f);
			}
		}

		if (player.m_daggers.size() > 0)
		{
			if (daggerThrow && !player.m_isDead)
			{
				player.m_daggers[0].move(1.5f, .0f);
				//rDaggersReps[0].setPosition(player.m_daggers[0].getPosition().x, player.m_daggers[0].getPosition().y);
				player.m_daggers_rectangles[0].updateX(player.m_daggers[0].getPosition().x, .0f);
				player.m_daggers_rectangles[0].updateY(player.m_daggers[0].getPosition().y);

				if (minusOneDagger)
				{
					numDaggers--;
					player.m_totalShots++;

					audio.playSwooshSound();
				}

				minusOneDagger = false;
			}

			if (player.m_daggers[0].getPosition().x > window.getSize().x)
			{
				player.m_daggers.erase(player.m_daggers.begin());
				//rDaggersReps.erase(rDaggersReps.begin());
				player.m_daggers_rectangles.erase(player.m_daggers_rectangles.begin());
				daggerThrow = false;

				minusOneDagger = true;
			}
		}

		if (Joystick::isButtonPressed(0, 0))
		{
			DEBUG_MSG("gpp::Events::Event::JUMP_UP_EVENT");
			input.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
		}

		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				// Close window : exit
				window.close();
				break;
				// Controller
			case sf::Event::JoystickButtonPressed:
				if (player.m_isGrounded && Joystick::isButtonPressed(0, 0))
				{
					DEBUG_MSG("gpp::Events::Event::JUMP_UP_EVENT");
					input.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
				}
				else if (!player.m_isGrounded && Joystick::isButtonPressed(0, 0))
				{
					DEBUG_MSG("gpp::Events::Event::GLIDE_EVENT");
					input.setCurrent(gpp::Events::Event::GLIDE_EVENT);
				}
				else if (sf::Joystick::isButtonPressed(0, 2))
				{
					DEBUG_MSG("gpp::Events::Event::ATTACK_START_EVENT");
					input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);

					audio.playSwooshSound();
				}
				else if (sf::Joystick::isButtonPressed(0, 5) && player.m_daggers.size() > 0 && !daggerThrow && player.m_canThrowDagger)
				{
					DEBUG_MSG("gpp::Events::Event::THROW_START_EVENT");
					input.setCurrent(gpp::Events::Event::THROW_START_EVENT);

					daggerThrow = true;
				}
				break;
			case sf::Event::JoystickMoved:
				if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 90.0f)
				{
					DEBUG_MSG("gpp::Events::Event::SLIDE_EVENT");
					input.setCurrent(gpp::Events::Event::SLIDE_EVENT);
				}
				else if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y) <= 90.0f && !player.m_isAttacking)
				{
					DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
				}
				break;
			case sf::Event::JoystickButtonReleased:
				if (!player.m_isGrounded && event.joystickButton.button == (0, 0))
				{
					DEBUG_MSG("gpp::Events::Event::GLIDE_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::GLIDE_STOP_EVENT);
				}
				// Stop Attack
				else if (event.joystickButton.button == (0, 2)
					&&
					player.m_isGrounded)
				{
					DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
				}
				else if (event.joystickButton.button == (0, 2)
					&&
					!player.m_isGrounded)
				{
					DEBUG_MSG("gpp::Events::Event::ATTACK_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::ATTACK_STOP_EVENT);
				}
				break;
				// Deal with KeyPressed
			case sf::Event::KeyPressed:
				// Died Event
				/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					DEBUG_MSG("gpp::Events::Event::DIED_EVENT");
					input.setCurrent(gpp::Events::Event::DIED_EVENT);
				}*/
				// Revieved Event
				/*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
					DEBUG_MSG("gpp::Events::Event::REVIVED_EVENT");
					input.setCurrent(gpp::Events::Event::REVIVED_EVENT);
				}*/
				// Running attack
				/*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)
					&& 
					sf::Keyboard::isKeyPressed(sf::Keyboard::Right) 
					||
					sf::Keyboard::isKeyPressed(sf::Keyboard::Right) 
					&& 
					sf::Keyboard::isKeyPressed(sf::Keyboard::Z)
					)
				{
					DEBUG_MSG("gpp::Events::Event::ATTACK_START");
					input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
				}*/
				// Attack
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
				{
					DEBUG_MSG("gpp::Events::Event::ATTACK_START_EVENT");
					input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);

					audio.playSwooshSound();
				}
				// Throw attack
				//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) 
					//&& 
					//sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
					//||
					//sf::Keyboard::isKeyPressed(sf::Keyboard::Right) 
					//&& 
					//sf::Keyboard::isKeyPressed(sf::Keyboard::X)
				/*	)
				{
					DEBUG_MSG("gpp::Events::Event::THROW_START_EVENT");
					input.setCurrent(gpp::Events::Event::THROW_START_EVENT);
				}*/
				// Throw Attack
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && player.m_daggers.size() > 0 && !daggerThrow && player.m_canThrowDagger)
				{
					DEBUG_MSG("gpp::Events::Event::THROW_START_EVENT");
					input.setCurrent(gpp::Events::Event::THROW_START_EVENT);

					daggerThrow = true;
				}
				// Run Right
				/*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
				}*/
				// Climb Up
				/*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					DEBUG_MSG("gpp::Events::Event::MOVE_UP_START_EVENT");
					input.setCurrent(gpp::Events::Event::MOVE_UP_START_EVENT);
				}*/
				// Climb Down
				/*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					DEBUG_MSG("gpp::Events::Event::MOVE_DOWN_START_EVENT");
					input.setCurrent(gpp::Events::Event::MOVE_DOWN_START_EVENT);
				}*/
				// Hit Bottom of Ladder Event
				/*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
				{
					DEBUG_MSG("gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT");
					input.setCurrent(gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT);
				}*/
				// Hit Top of Ladder Event
				/*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
				{
					DEBUG_MSG("gpp::Events::Event::HIT_LADDER_TOP_EVENT");
					input.setCurrent(gpp::Events::Event::HIT_LADDER_TOP_EVENT);
				}*/
				// Jump Run
				/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) 
					&& 
					sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
					||
					sf::Keyboard::isKeyPressed(sf::Keyboard::Right) 
					&& 
					sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
					)
				{
					DEBUG_MSG("gpp::Events::Event::JUMP_UP_EVENT");
					input.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
				}*/
				// Jump Event
				else if (player.m_isGrounded && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					DEBUG_MSG("gpp::Events::Event::JUMP_UP_EVENT");
					input.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
				}
				// Running Slide
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					DEBUG_MSG("gpp::Events::Event::SLIDE_EVENT");
					input.setCurrent(gpp::Events::Event::SLIDE_EVENT);
				}
				// Hit Ground Event
				/*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
				{
					DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
					input.setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);
				}*/

				// Jump Attack Event
				/*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
				{
					DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
					input.setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);
				}*/

				// Jump Throw Attack Event
				/*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
				{
					DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
					input.setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);
				}*/

				// Glide
				else if (player.m_isGrounded == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					DEBUG_MSG("gpp::Events::Event::GLIDE_EVENT");
					input.setCurrent(gpp::Events::Event::GLIDE_EVENT);
				}
				break;

				// Deal with KeyReleased
			case sf::Event::KeyReleased:
				// Stop Attack
				if (event.key.code == sf::Keyboard::Z 
					&& 
					player.m_isGrounded)
				{
					DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
				}
				else if(event.key.code == sf::Keyboard::Z
					&&
					player.m_isGrounded == false)
				{
					DEBUG_MSG("gpp::Events::Event::ATTACK_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::ATTACK_STOP_EVENT);
				}
				// Run and Stop Throw Attack
				/*else if (event.key.code == sf::Keyboard::X && player.m_daggers.size() > 0 && !daggerThrow
					&&
					sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
				}*/
				// Stop Throw Attack
				/*else if (event.key.code == sf::Keyboard::X && player.m_daggers.size() > 0 && !daggerThrow)
				{
					DEBUG_MSG("gpp::Events::Event::THROW_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::THROW_STOP_EVENT);
				}*/
				// Stop Running Right
				/*else if (event.key.code == sf::Keyboard::Right)
				{
					DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_RIGHT_STOP_EVENT);
				}*/
				// Stop Slide
				else if (event.key.code == sf::Keyboard::Down 
					/*&&
					sf::Keyboard::isKeyPressed(sf::Keyboard::Right)*/)
				{
					DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
				}
				// Stop Moving Up
				/*else if (event.key.code == sf::Keyboard::Up)
				{
					DEBUG_MSG("gpp::Events::Event::MOVE_UP_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::MOVE_UP_STOP_EVENT);
				}*/
				// Stop Moving Down
				/*else if (event.key.code == sf::Keyboard::Down)
				{
					DEBUG_MSG("gpp::Events::Event::MOVE_DOWN_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::MOVE_DOWN_STOP_EVENT);
				}*/
				// Stop gliding
				else if (player.m_isGrounded == false && event.key.code == sf::Keyboard::Space)
				{
					DEBUG_MSG("gpp::Events::Event::GLIDE_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::GLIDE_STOP_EVENT);
				}
				break;

			default:
				DEBUG_MSG("gpp::Events::Event::NONE");
				input.setCurrent(gpp::Events::Event::NONE);
				break;
			}
			// Handle input to Player
			player.handleInput(input);
		}

		sf::RectangleShape rect(sf::Vector2f(player.getAnimatedSprite().getGlobalBounds().width - 15.0f, 15.0f));
		rect.setPosition(player.getAnimatedSprite().getPosition().x + 2.0f, player.getAnimatedSprite().getPosition().y + player.getAnimatedSprite().getGlobalBounds().height - 20.0f);
		rect.setFillColor(sf::Color::Yellow);

		// Update the Player
		player.update();

		// Clear screen
		window.clear();

		window.draw(bg_sprite);
		window.draw(bg_sprite_copy);

		window.draw(livesText);

		for (auto& life : lives)
		{
			window.draw(life);
		}

		window.draw(enemiesHitText);
		window.draw(enemyHUD);

		window.draw(daggersHUDText);
		window.draw(daggersHUD);

		for (int i = 0; i < 25; i++)
		{
			window.draw(tiles_ground[i]);
			window.draw(tiles_ground_1[i]);
			window.draw(tiles_ground_copy[i]);
			window.draw(tiles_ground_1_copy[i]);
		}

		tilesPtr->render(window);

		//window.draw(rect);

		//window.draw(cPlayerRep);

		//window.draw(rPlayerRep);

		// Draw the Players Current Animated Sprite
		window.draw(player.getAnimatedSpriteFrame());

		for (int i = 0; i < player.m_daggers.size(); i++)
		{
			//window.draw(rDaggersReps[i]);
			window.draw(player.m_daggers[i]);
		}

		window.draw(playerBlood);
		window.draw(enemyBlood);

		if (player.m_isDead)
		{
			endScreen.render(window);
		}

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};
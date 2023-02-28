//#ifdef _DEBUG
//#pragma comment(lib, "libCandle-s.a") 
//#endif

#include "Game.h"
#include "Defines.h"

#include "iostream"
#include "SFML/Graphics.hpp"
//#include <Player.h>
//#include "AnimatedSprite.h"
#include "Events.h"
#include "Debug.h"
#include "Tiles.h"
#include "Set1.h"
#include "Set2.h"
#include "Set3.h"
#include "Set4.h"
#include "Set5.h"
#include "circle.h"
#include "Rectangle.h"
#include "EndScreen.h"
#include "Audio.h"
#include "Score.h"
#include "EnemyScore.h"
#include "DoubleKill.h"
//#include "Candle/RadialLight.hpp"

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

sf::Texture player_texture;

sf::Texture bg1_texture;
sf::Texture bg2_texture;
sf::Texture bg3_texture;

sf::Texture tile_texture;

// Setup Players Default Animated Sprite
AnimatedSprite player_animated_sprite(player_texture);

sf::Sprite bg1_sprite;
sf::Sprite bg2_sprite;
sf::Sprite bg3_sprite;

float bg_friction = .05f;

bool allowPositionChangeBg1 = true;
bool allowPositionChangeBg2 = true;
bool allowPositionChangeBg3 = true;

std::vector<sf::Sprite> tiles_ground;
float ground_PosX = .0f;

std::vector<sf::Sprite> tiles_ground_1;
float ground_1_PosX = .0f;

std::vector<sf::Sprite> tiles_ground_copy = tiles_ground;
std::vector<sf::Sprite> tiles_ground_1_copy = tiles_ground_1;

bool allowPositionChangeGround1 = true;
bool allowPositionChangeGround2 = true;

Set1 set1;
Set2 set2;
Set3 set3;
Set4 set4;
Set5 set5;

std::vector<Tiles*> tileArray;
std::vector<bool> tileMove;

int randomSet = 0;
int currentSet = 0;
int previousSet = 0;

bool gotNewTileset = false;

float baseTilePos = .0f;

Player player(player_animated_sprite);

sf::Texture daggerTexture;

bool daggerThrow = false;

Rectangle rPlayer(player.getAnimatedSprite().getPosition().x,
	player.getAnimatedSprite().getPosition().y,
	player.getAnimatedSprite().getGlobalBounds().width,
	player.getAnimatedSprite().getGlobalBounds().height);

sf::RectangleShape rPlayerRep;

sf::Font font;

sf::Text livesText;

sf::Texture lives_texture;

std::vector<sf::Sprite> lives;

bool minusOneLife = false;

int enemiesHit = 0;

sf::Text enemiesHitText;

sf::Texture enemyHUD_texture;

sf::Sprite enemyHUD;

int numDaggers = 3;

bool minusOneDagger = true;

sf::Text daggersHUDText;

sf::Texture daggersHUD_texture;

sf::Sprite daggersHUD;

EndScreen endScreen;

Audio audio;

sf::Texture bloodTexture;

sf::Sprite playerBlood;

sf::Sprite enemyBlood;

int playerBloodFrame = 0;

int enemyBloodFrame = 0;

bool isEnemyHit = false;

bool isPlayerHit = false;

int hitEnemy = 0;

int numExtraKunais = 0;

std::vector<sf::Sprite> emptyVector;

bool isTileOccupied = false;

int occupyingTile = 0;

Score score;

float scoreBonus = 1000.0f;

int speedIncreaseFactor = 4000;

int collectedMedkit = 0;

int collectedKunais = 0;

std::vector<std::shared_ptr<EnemyScore>> enemyScores;

std::vector<int> hitEnemies;

float accuracyCooldown = .5f;

sf::Clock accuracyClock;

bool setAccuracy = true;

bool startAccuracyClock = false;

bool hasResetAccuracyClock = false;

DoubleKill doubleKill;

bool showDoubleKill = false;

sf::Clock doubleKillClock;

bool hasResetDoubleKillClock = false;

gpp::Events input;

void Game::init(sf::RenderWindow& window)
{
	srand(time(NULL));

	// Create the main window

	window.setKeyRepeatEnabled(false);

#pragma region TextureLoading

	// Load a sprite to display
	if (!player_texture.loadFromFile(PLAYER_SPRITES)) {
		DEBUG_MSG("Failed to load file");
		if (!player_texture.loadFromFile(ERROR_SPRITES)) {
			DEBUG_MSG("Error sprites");
		}
	}

	/*sf::Texture bg_texture;
	if (!bg_texture.loadFromFile("assets\\bg\\1.png")) {
		DEBUG_MSG("Failed to load file");
	}*/

	if (!bg1_texture.loadFromFile("assets\\bg\\bg1.jpg")) {
		DEBUG_MSG("Failed to load file");
	}

	if (!bg2_texture.loadFromFile("assets\\bg\\bg2.jpg")) {
		DEBUG_MSG("Failed to load file");
	}

	if (!bg3_texture.loadFromFile("assets\\bg\\bg3.jpg")) {
		DEBUG_MSG("Failed to load file");
	}

	if (!tile_texture.loadFromFile("assets\\tiles\\tiles.png")) {
		DEBUG_MSG("Failed to load file");
	}

#pragma endregion

#pragma region AnimatedSprite


	bg1_sprite.setTexture(bg1_texture);
	bg2_sprite.setTexture(bg2_texture);
	bg3_sprite.setTexture(bg3_texture);
	//bg_sprite.setScale(sf::Vector2f(.6f, .6f));

	bg1_sprite.setPosition(.0f, .0f);
	bg2_sprite.setPosition(bg1_sprite.getGlobalBounds().width - 2.0f, .0f);
	bg3_sprite.setPosition(bg2_sprite.getPosition().x + bg2_sprite.getGlobalBounds().width - 1.0f, .0f);
	/*sf::Sprite bg_sprite_copy;
	bg_sprite_copy.setTexture(bg_texture);
	bg_sprite_copy.setOrigin(sf::Vector2f(bg_sprite_copy.getGlobalBounds().width / 2.0f, bg_sprite_copy.getGlobalBounds().height / 2.0f));
	bg_sprite_copy.setPosition(sf::Vector2f(bg_sprite.getGlobalBounds().width + bg_sprite.getGlobalBounds().width/2.0f - 1.0f, bg_sprite.getGlobalBounds().height / 2.0f));
	bg_sprite_copy.setScale(sf::Vector2f(-1.0f, 1.0f));*/

	/*for (int i = 0; i < 40; i++)
	{
		sf::Sprite ground;
		ground.setTexture(tile_texture);
		ground.setTextureRect(sf::IntRect(32, 32, 32, 32));
		ground.setScale(sf::Vector2f(1.5f, 1.5f));
		ground.setPosition(sf::Vector2f(ground_PosX, window.getSize().y - 128.0f - 16.0f));
		tiles_ground.push_back(ground);
		ground_PosX += 32.0f * 1.5f;

		sf::Sprite ground_1;
		ground_1.setTexture(tile_texture);
		ground_1.setTextureRect(sf::IntRect(32, 64, 32, 32));
		ground_1.setScale(sf::Vector2f(1.5f, 1.5f));
		ground_1.setPosition(sf::Vector2f(ground_1_PosX, window.getSize().y - 96.0f - 16.0f));
		tiles_ground_1.push_back(ground_1);
		ground_1_PosX += 32.0f * 1.5f;
	}*/



	/*for (int i = 0; i < 40; i++)
	{
		tiles_ground_copy[i].setPosition(tiles_ground_copy[i].getPosition().x + 32.0f * 25.0f, window.getSize().y - 128.0f - 16.0f);
		tiles_ground_1_copy[i].setPosition(tiles_ground_1_copy[i].getPosition().x + 32.0f * 25.0f, window.getSize().y - 96.0f - 16.0f);
	}*/

#pragma endregion

	player.m_isDead = false;

	for (size_t i = 0; i < tileArray.size(); i++)
	{
		tileArray[i]->getEnemy().m_isPlayerDead = false;
	}

	allowPositionChangeBg1 = true;
	allowPositionChangeBg2 = true;
	allowPositionChangeBg3 = true;

	gotNewTileset = false;

	daggerThrow = false;

	minusOneLife = false;

	minusOneDagger = true;

	isEnemyHit = false;

	isPlayerHit = false;

	isTileOccupied = false;

	setAccuracy = true;

	startAccuracyClock = false;

	hasResetAccuracyClock = false;

	showDoubleKill = false;

	hasResetDoubleKillClock = false;

	playerBloodFrame = 0;

	enemyBloodFrame = 0;

	hitEnemy = 0;

	numExtraKunais = 0;

	occupyingTile = 0;

	scoreBonus = 1000.0f;

	speedIncreaseFactor = 4000;

	collectedMedkit = 0;

	collectedKunais = 0;

	//Tiles* tilesPtr = nullptr;

	set1.init(tile_texture, window);
	set2.init(tile_texture, window);
	set3.init(tile_texture, window);
	set4.init(tile_texture, window);
	set5.init(tile_texture, window);

	tileArray.clear();

	tileArray.push_back(&set1);
	tileArray.push_back(&set2);
	tileArray.push_back(&set3);
	tileArray.push_back(&set4);
	tileArray.push_back(&set5);

	baseTilePos = .0f;

	enemiesHit = 0;

	numDaggers = 3;

	player = Player(player_animated_sprite);

	tileMove.clear();

	for (size_t i = 0; i < tileArray.size(); i++)
	{
		tileMove.push_back(false);

		for (size_t j = 0; j < tileArray[i]->getTiles().size(); j++)
		{
			tileArray[i]->getTiles()[j].setScale(1.0f, 1.0f);
		}

		tileArray[i]->getEnemy().getAnimatedSprite().setScale(-.3f, .3f);
		tileArray[i]->getMedkit().getSprite().setScale(.1f, .1f);
		tileArray[i]->getExtraKunais().getSprite().setScale(.5f, .5f);
	}

	randomSet = rand() % tileArray.size() + 1;

	currentSet = randomSet;

	tileMove[currentSet - 1] = true;

	player.getAnimatedSprite().setPosition(sf::Vector2f(50.0f, 805.0f));

	if (!daggerTexture.loadFromFile("assets/Kunai.png"))
	{
		DEBUG_MSG("Failed to load kunai");
	}

	player.m_daggers.clear();

	for (int i = 0; i < 3; i++)
	{
		sf::Sprite dagger;
		dagger.setTexture(daggerTexture);
		dagger.setPosition(-100.0f, -100.0f);
		dagger.setScale(.5f, .5f);
		player.m_daggers.push_back(dagger);
	}

	//std::vector<sf::RectangleShape> rDaggersReps;

	player.m_daggers_rectangles.clear();

	for (int i = 0; i < 3; i++)
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

	rPlayerRep.setSize(sf::Vector2f(player.getAnimatedSprite().getGlobalBounds().width, player.getAnimatedSprite().getGlobalBounds().height));
	rPlayerRep.setFillColor(sf::Color::Yellow);

	if (!font.loadFromFile("assets/fonts/ninja.otf"))
	{
		std::cout << "Couldn't load ninja font";
	}

	livesText.setFont(font);
	livesText.setCharacterSize(30.0f);
	livesText.setString("Lives :");
	livesText.setPosition(20.0f, 20.0f);
	livesText.setFillColor(sf::Color::Black);


	if (!lives_texture.loadFromFile("assets/Idle.png"))
	{
		DEBUG_MSG("Failed to load lives texture");
	}

	lives.clear();

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



	enemiesHitText.setFont(font);
	enemiesHitText.setCharacterSize(30.0f);
	enemiesHitText.setString(std::to_string(enemiesHit));
	enemiesHitText.setPosition(window.getSize().x - enemiesHitText.getGlobalBounds().width - 20.0f, 20.0f);
	enemiesHitText.setFillColor(sf::Color::Black);


	if (!enemyHUD_texture.loadFromFile("assets/EnemySpriteSheet.png"))
	{
		DEBUG_MSG("Failed to load lives texture");
	}

	enemyHUD.setTexture(enemyHUD_texture);
	enemyHUD.setTextureRect(sf::IntRect(3900, 0, 211, 200));
	enemyHUD.setScale(.2f, .2f);
	enemyHUD.setPosition(enemiesHitText.getPosition().x - enemyHUD.getGlobalBounds().width - 10.0f, 20.0f);


	daggersHUDText.setFont(font);
	daggersHUDText.setCharacterSize(30.0f);
	daggersHUDText.setString("0");
	daggersHUDText.setPosition(window.getSize().x - daggersHUDText.getGlobalBounds().width - 20.0f, 80.0f);
	daggersHUDText.setFillColor(sf::Color::Black);


	if (!daggersHUD_texture.loadFromFile("assets/Kunai.png"))
	{
		DEBUG_MSG("Failed to load lives texture");
	}

	daggersHUD.setTexture(daggersHUD_texture);
	daggersHUD.setScale(.4f, .4f);
	daggersHUD.setRotation(-20);
	daggersHUD.setPosition(daggersHUDText.getPosition().x - daggersHUD.getGlobalBounds().width - 10.0f, 105.0f);


	audio.playBgMusic();


	if (!bloodTexture.loadFromFile("assets/images/blood.png"))
	{
		// Error
	}

	playerBlood.setTexture(bloodTexture);
	playerBlood.setTextureRect(sf::IntRect(0, 0, 512, 512));
	playerBlood.setScale(.4f, .4f);
	playerBlood.setPosition(-2000.0f, -2000.0f);

	enemyBlood.setTexture(bloodTexture);
	enemyBlood.setTextureRect(sf::IntRect(0, 0, 512, 512));
	enemyBlood.setScale(.4f, .4f);
	enemyBlood.setPosition(-2000.0f, -2000.0f);

	endScreen.init(window, player);

	//std::cout << sf::Joystick::ButtonCount << "\n";

	//std::vector<sf::Sprite> playerTiles;

	/*std::vector<reference_wrapper<sf::Sprite const>> playerTiles;

	for (Tiles* i : tileArray)
	{
		for (size_t j = 0; j < i->getTiles().size(); j++)
		{
			playerTiles.push_back(i->getTiles()[j]);
		}

		playerTiles.insert(playerTiles.end(), i->getTiles().begin(), i->getTiles().end());
	}*/


	score.init(window);
	doubleKill.init(window);

	enemyScores.clear();
	hitEnemies.clear();
}

void Game::update(sf::RenderWindow& window)
{
	/*cPlayer.updateX(player.getAnimatedSprite().getPosition().x, .0f);
		cPlayer.updateY(player.getAnimatedSprite().getPosition().y);

		cPlayerRep.setPosition(player.getAnimatedSprite().getPosition().x,
							   player.getAnimatedSprite().getPosition().y);*/

	if (!player.m_isDead)
		score.update(window, player.m_speed);

	if (player.m_speed < player.m_maxSpeed)
	{
		if (score.getScore() > 0 && score.getScore() > speedIncreaseFactor)
		{
			player.m_speed += .1f;
			speedIncreaseFactor += 4000;
		}
	}

	rPlayer.updateX(player.getAnimatedSprite().getPosition().x, .0f);
	rPlayer.updateY(player.getAnimatedSprite().getPosition().y);

	rPlayerRep.setPosition(player.getAnimatedSprite().getPosition().x, player.getAnimatedSprite().getPosition().y);

	//std::cout << "x : " << tileArray[currentSet - 1]->getTiles()[tileArray[currentSet - 1]->getTiles().size() - 1].getPosition().x << "\n";
	//std::cout << playerTiles.size() << "\n";

	//std::cout << enemyScores.size() << "\n";

	for (size_t i = 0; i < tileArray.size(); i++)
	{
		if (rectangle_to_rectangle(rPlayer, tileArray[i]->getEnemy().m_rectangle))
		{
			if (player.m_isAttacking && !player.m_isDead)
			{
				std::shared_ptr<EnemyScore> enemyScore = std::make_unique<EnemyScore>(scoreBonus);
				enemyScores.push_back(enemyScore);

				tileArray[i]->getEnemy().m_rectangle.setWidth(.0f);
				tileArray[i]->getEnemy().m_rectangle.setHeight(.0f);
				tileArray[i]->getEnemy().m_isDead = true;

				enemiesHit++;
				score.bonus(scoreBonus);

				audio.playHurtSound();

				isEnemyHit = true;
				hitEnemy = i;
				hitEnemies.push_back(i);
			}
		}

		for (size_t i = 0; i < enemyScores.size(); i++)
		{
			if (hitEnemies.size() > 0)
				enemyScores[i]->update(&(tileArray[hitEnemies[i]]->getEnemy()), enemyScores, hitEnemies);
		}

		if (player.getAnimatedSprite().getGlobalBounds().intersects(tileArray[i]->getMedkit().getSprite().getGlobalBounds()))
		{
			if (lives.size() < 3 && lives.size() > 0)
			{
				player.m_hasCollectedMedkit = true;
				collectedMedkit = i;

				sf::Sprite life;
				life.setTexture(lives_texture);
				life.setTextureRect(sf::IntRect(0, 0, 211, 200));
				life.setScale(.2f, .2f);
				life.setPosition(lives[lives.size() - 1].getPosition().x + 50.0f, 20.0f);
				lives.push_back(life);

				tileArray[i]->getMedkit().getSprite().setScale(.0f, .0f);
				player.m_health++;
			}
		}

		if (player.getAnimatedSprite().getGlobalBounds().intersects(tileArray[i]->getExtraKunais().getSprite().getGlobalBounds()))
		{
			if (player.m_daggers.size() < 5)
			{
				player.m_hasCollectedKunais = true;
				collectedKunais = i;

				if (player.m_daggers.size() > 2)
				{
					numExtraKunais = 5 - player.m_daggers.size();
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

				tileArray[i]->getExtraKunais().getSprite().setScale(.0f, .0f);
			}
		}

		if (isEnemyHit)
		{
			enemyBlood.setPosition(tileArray[hitEnemy]->getEnemy().getAnimatedSprite().getPosition().x - tileArray[hitEnemy]->getEnemy().getAnimatedSprite().getGlobalBounds().width, tileArray[hitEnemy]->getEnemy().getAnimatedSprite().getPosition().y);

			enemyBloodFrame++;

			if (enemyBlood.getTextureRect().left < 3072)
			{
				if (enemyBloodFrame > 100)
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

		if (player.m_daggers_rectangles.size() > 0)
		{
			if (rectangle_to_rectangle(player.m_daggers_rectangles[0], tileArray[i]->getEnemy().m_rectangle))
			{
				//std::cout << "RIP ENEMY NINJA\n";

				std::shared_ptr<EnemyScore> enemyScore = std::make_unique<EnemyScore>(scoreBonus);
				enemyScores.push_back(enemyScore);

				tileArray[i]->getEnemy().m_rectangle.setWidth(.0f);
				tileArray[i]->getEnemy().m_rectangle.setHeight(.0f);
				tileArray[i]->getEnemy().m_isDead = true;

				enemiesHit++;
				score.bonus(scoreBonus);

				if (setAccuracy)
				{
					player.m_shotsHit++;
					std::cout << "SHOTS HIT : " << player.m_shotsHit << "\n";
				}
				else
				{
					std::cout << "DOUBLE KILL\n";
					showDoubleKill = true;
					score.bonus(2000.0f);
				}

				if (!startAccuracyClock)
					startAccuracyClock = true;

				audio.playHurtSound();

				isEnemyHit = true;
				hitEnemy = i;
				hitEnemies.push_back(i);
			}
		}

		if (startAccuracyClock)
		{
			setAccuracy = false;

			if (!hasResetAccuracyClock)
			{
				accuracyClock.restart();
				hasResetAccuracyClock = true;
			}

			if (accuracyClock.getElapsedTime().asSeconds() > accuracyCooldown)
			{
				setAccuracy = true;
				startAccuracyClock = false;
				hasResetAccuracyClock = false;
			}
		}

		if (showDoubleKill)
		{
			doubleKill.update(window);

			if (!hasResetDoubleKillClock)
			{
				doubleKillClock.restart();
				hasResetDoubleKillClock = true;
			}

			if (doubleKillClock.getElapsedTime().asSeconds() > 3.0)
			{
				showDoubleKill = false;
				hasResetDoubleKillClock = false;
				doubleKill.getText().setScale(.0f, .0f);
			}
		}

		if (tileArray[i]->getEnemy().m_daggers_rectangles.size() > 0)
		{
			if (rectangle_to_rectangle(tileArray[i]->getEnemy().m_daggers_rectangles[0], rPlayer))
			{
				if (!minusOneLife && lives.size() > 0)
				{
					//std::cout << "OUCH THAT HURTS\n";
					lives.pop_back();
					player.m_health--;
					minusOneLife = true;

					audio.playHurtSound();

					isPlayerHit = true;
				}
			}
			//else
			//{
			//	minusOneLife = false;
			//}
		}

		if (minusOneLife)
		{
			if (!player.m_isInvincibilityClockRestarted)
			{
				player.m_invincibilityTime.restart();
				player.m_isInvincibilityClockRestarted = true;
			}

			if (player.m_invincibilityTime.getElapsedTime().asSeconds() > 2.0f)
			{
				minusOneLife = false;
				player.m_isInvincibilityClockRestarted = false;
			}

			//std::cout << player.m_invincibilityTime.getElapsedTime().asSeconds() << "\n";
		}

		if (tileMove[i])
		{
			tileArray[i]->update(window, &player);
		}

		if (player.getAnimatedSprite().getPosition().x >= tileArray[i]->getTiles()[0].getPosition().x - player.getAnimatedSprite().getGlobalBounds().width
			&& player.getAnimatedSprite().getPosition().x <= tileArray[i]->getTiles()[tileArray[i]->getTiles().size() - 1].getPosition().x)
		{
			occupyingTile = i;
			player.setTiles(tileArray[i]->getTiles());
			isTileOccupied = true;
		}

		if (isTileOccupied)
		{
			if (player.getAnimatedSprite().getPosition().x > tileArray[occupyingTile]->getTiles()[tileArray[occupyingTile]->getTiles().size() - 1].getPosition().x)
			{
				player.setTiles(emptyVector);
				isTileOccupied = false;
			}
		}

		if (tileArray[i]->getTiles()[tileArray[i]->getTiles().size() - 1].getPosition().x < -tileArray[i]->getTiles()[tileArray[i]->getTiles().size() - 1].getGlobalBounds().width + 1600.0f && !gotNewTileset)
		{
			gotNewTileset = true;

			//std::cout << "WE'RE IN !!! POGCHAMP\n";

			while (randomSet == currentSet)
				randomSet = rand() % tileArray.size() + 1;

			currentSet = randomSet;

			tileMove[currentSet - 1] = true;

			/*for (int j = 0; j < tileArray[i]->getTiles().size(); j++)
			{
				tileArray[i]->getTiles()[j].setScale(1.0f, 1.0f);
			}

			tileArray[i]->getEnemy().getAnimatedSprite().setScale(-.3f, .3f);
			tileArray[i]->getMedkit().getSprite().setScale(.1f, .1f);
			tileArray[i]->getExtraKunais().getSprite().setScale(.5f, .5f);*/
		}

		if (tileArray[i]->getTiles()[tileArray[i]->getTiles().size() - 1].getPosition().x < -tileArray[i]->getTiles()[tileArray[i]->getTiles().size() - 1].getGlobalBounds().width)
		{
			tileMove[i] = false;

			baseTilePos = std::abs(tileArray[i]->getTiles()[0].getPosition().x);
			tileArray[i]->getTiles()[0].setPosition(window.getSize().x, tileArray[i]->getTiles()[0].getPosition().y);

			for (size_t j = 1; j < tileArray[i]->getTiles().size(); j++)
			{
				tileArray[i]->getTiles()[j].setPosition(window.getSize().x + baseTilePos - std::abs(tileArray[i]->getTiles()[j].getPosition().x), tileArray[i]->getTiles()[j].getPosition().y);
			}

			/*switch (i + 1)
			{
				case 1:
					tileArray[i]->getEnemy().getAnimatedSprite().setPosition(window.getSize().x + 400.0f, tileArray[i]->getEnemy().getAnimatedSprite().getPosition().y);
					tileArray[i]->getMedkit().getSprite().setPosition(window.getSize().x + 850.0f, tileArray[i]->getMedkit().getSprite().getPosition().y);
					tileArray[i]->getExtraKunais().getSprite().setPosition(window.getSize().x + 620.0f, tileArray[i]->getExtraKunais().getSprite().getPosition().y);
					break;
				case 2:
					tileArray[i]->getEnemy().getAnimatedSprite().setPosition(window.getSize().x + 750.0f, tileArray[i]->getEnemy().getAnimatedSprite().getPosition().y);
					break;
				case 3:
					tileArray[i]->getEnemy().getAnimatedSprite().setPosition(window.getSize().x + 1400.0f, tileArray[i]->getEnemy().getAnimatedSprite().getPosition().y);
					break;
			}*/

			//tileArray[i]->getEnemy().getAnimatedSprite().setPosition(window.getSize().x + tileArray[i]->getEnemyX(), tileArray[i]->getEnemy().getAnimatedSprite().getPosition().y);
			sf::Vector2f newEnemyPos = tileArray[i]->getNewEnemyPos();
			tileArray[i]->getEnemy().getAnimatedSprite().setPosition(window.getSize().x + newEnemyPos.x, newEnemyPos.y - 131.7f);
			tileArray[i]->getMedkit().getSprite().setPosition(window.getSize().x + 850.0f, tileArray[i]->getMedkit().getSprite().getPosition().y);
			tileArray[i]->getExtraKunais().getSprite().setPosition(window.getSize().x + 620.0f, tileArray[i]->getExtraKunais().getSprite().getPosition().y);

			tileArray[i]->getMedkit().getSprite().setScale(.1f, .1f);
			tileArray[i]->getExtraKunais().getSprite().setScale(.5f, .5f);

			gotNewTileset = false;

			//std::cout << "YEEEEEEEEEEEEAAAAAAAAAAAAAAAAAAAAAAAAH " << i + 1 << currentSet << "\n";
		}

	}

	if (isPlayerHit)
	{
		playerBlood.setPosition(player.getAnimatedSprite().getPosition().x - player.getAnimatedSprite().getGlobalBounds().width / 2.0f, player.getAnimatedSprite().getPosition().y);

		playerBloodFrame++;

		if (playerBlood.getTextureRect().left < 3072)
		{
			if (playerBloodFrame > 20)
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

	enemiesHitText.setString(std::to_string(enemiesHit));
	enemiesHitText.setPosition(window.getSize().x - enemiesHitText.getGlobalBounds().width - 20.0f, 20.0f);

	enemyHUD.setPosition(enemiesHitText.getPosition().x - enemyHUD.getGlobalBounds().width - 10.0f, 20.0f);

	daggersHUDText.setString(std::to_string(numDaggers));
	daggersHUDText.setPosition(window.getSize().x - daggersHUDText.getGlobalBounds().width - 20.0f, 80.0f);

	daggersHUD.setPosition(daggersHUDText.getPosition().x - daggersHUD.getGlobalBounds().width - 10.0f, 105.0f);

	if (bg1_sprite.getPosition().x <= -bg1_sprite.getGlobalBounds().width && allowPositionChangeBg1)
	{
		bg1_sprite.setPosition(sf::Vector2f(bg3_sprite.getPosition().x + bg3_sprite.getGlobalBounds().width - 1.0f, .0f));
		allowPositionChangeBg2 = true;
		allowPositionChangeBg1 = false;
		allowPositionChangeBg3 = true;
	}

	if (bg2_sprite.getPosition().x <= -bg2_sprite.getGlobalBounds().width && allowPositionChangeBg2)
	{
		bg2_sprite.setPosition(sf::Vector2f(bg1_sprite.getPosition().x + bg1_sprite.getGlobalBounds().width - 2.0f, 0.0f));
		allowPositionChangeBg2 = false;
		allowPositionChangeBg1 = true;
		allowPositionChangeBg3 = true;
	}

	if (bg3_sprite.getPosition().x <= -bg3_sprite.getGlobalBounds().width && allowPositionChangeBg3)
	{
		bg3_sprite.setPosition(sf::Vector2f(bg2_sprite.getPosition().x + bg2_sprite.getGlobalBounds().width - 1.0f, 0.0f));
		allowPositionChangeBg2 = true;
		allowPositionChangeBg1 = true;
		allowPositionChangeBg3 = false;
	}

	/*if (tiles_ground_copy[0].getPosition().x <= 0.0f && allowPositionChangeGround1)
	{
		for (int i = 0; i < 40; i++)
		{
			tiles_ground[i].setPosition(tiles_ground_copy[i].getPosition().x + 32.0f * 1.5f * 40.0f, window.getSize().y - 128.0f - 16.0f);
			tiles_ground_1[i].setPosition(tiles_ground_1_copy[i].getPosition().x + 32.0f * 1.5f * 40.0f, window.getSize().y - 96.0f - 16.0f);
			allowPositionChangeGround1 = false;
			allowPositionChangeGround2 = true;
		}
	}

	if (tiles_ground[0].getPosition().x <= 0.0f && allowPositionChangeGround2)
	{
		for (int i = 0; i < 40; i++)
		{
			tiles_ground_copy[i].setPosition(tiles_ground[i].getPosition().x + 32.0f * 1.5f * 40.0f, window.getSize().y - 128.0f - 16.0f);
			tiles_ground_1_copy[i].setPosition(tiles_ground_1[i].getPosition().x + 32.0f * 1.5f * 40.0f, window.getSize().y - 96.0f - 16.0f);
			allowPositionChangeGround1 = true;
			allowPositionChangeGround2 = false;
		}
	}*/

	if (!player.m_isDead)
	{
		bg1_sprite.move(sf::Vector2f(-.2f, .0f));
		bg2_sprite.move(sf::Vector2f(-.2f, .0f));
		bg3_sprite.move(sf::Vector2f(-.2f, .0f));

		/*for (int i = 0; i < 40; i++)
		{
			tiles_ground[i].move(sf::Vector2f(-player.m_speed, .0f));
			tiles_ground_1[i].move(sf::Vector2f(-player.m_speed, .0f));
			tiles_ground_copy[i].move(sf::Vector2f(-player.m_speed, .0f));
			tiles_ground_1_copy[i].move(sf::Vector2f(-player.m_speed, .0f));
		}*/
	}
	else
	{
		bg_friction *= .999f;
		bg1_sprite.move(sf::Vector2f(-bg_friction, .0f));
		bg2_sprite.move(sf::Vector2f(-bg_friction, .0f));
		bg3_sprite.move(sf::Vector2f(-bg_friction, .0f));

		/*for (int i = 0; i < 40; i++)
		{
			tiles_ground[i].move(sf::Vector2f(-bg_friction, .0f));
			tiles_ground_1[i].move(sf::Vector2f(-bg_friction, .0f));
			tiles_ground_copy[i].move(sf::Vector2f(-bg_friction, .0f));
			tiles_ground_1_copy[i].move(sf::Vector2f(-bg_friction, .0f));
		}*/

		endScreen.update(window, score.getScore(), player, *this);
	}

	//std::cout << "ISGROUNDED : " << player.m_isGrounded << "\n";
	if (player.m_isGrounded)
	{
		player.m_friction = 1.0f;
	}


	if (player.m_daggers.size() > 0)
	{
		if (daggerThrow)
		{
			player.m_daggers[0].move(10.0f, .0f);
			//rDaggersReps[0].setPosition(player.m_daggers[0].getPosition().x, player.m_daggers[0].getPosition().y);

			if (!player.m_isDead)
			{
				player.m_daggers_rectangles[0].updateX(player.m_daggers[0].getPosition().x, .0f);
				player.m_daggers_rectangles[0].updateY(player.m_daggers[0].getPosition().y);

				if (minusOneDagger)
				{
					numDaggers--;
					player.m_totalShots++;
					std::cout << "TOTAL SHOTS : " << player.m_totalShots << "\n";

					audio.playSwooshSound();
				}

				minusOneDagger = false;
			}
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
		//DEBUG_MSG("gpp::Events::Event::JUMP_UP_EVENT");
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
				//DEBUG_MSG("gpp::Events::Event::JUMP_UP_EVENT");
				input.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
			}
			else if (!player.m_isGrounded && Joystick::isButtonPressed(0, 0))
			{
				//DEBUG_MSG("gpp::Events::Event::GLIDE_EVENT");
				input.setCurrent(gpp::Events::Event::GLIDE_EVENT);
			}
			else if (sf::Joystick::isButtonPressed(0, 2))
			{
				//DEBUG_MSG("gpp::Events::Event::ATTACK_START_EVENT");
				input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);

				if (!player.m_isDead)
					audio.playSwooshSound();
			}
			else if (sf::Joystick::isButtonPressed(0, 5) && player.m_daggers.size() > 0 && !daggerThrow && player.m_canThrowDagger)
			{
				//DEBUG_MSG("gpp::Events::Event::THROW_START_EVENT");
				input.setCurrent(gpp::Events::Event::THROW_START_EVENT);

				daggerThrow = true;
			}
			break;
		case sf::Event::JoystickMoved:
			if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 90.0f)
			{
				//DEBUG_MSG("gpp::Events::Event::SLIDE_EVENT");
				input.setCurrent(gpp::Events::Event::SLIDE_EVENT);
			}
			else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) <= 90.0f && !player.m_isAttacking)
			{
				//DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
				input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
			}
			break;
		case sf::Event::JoystickButtonReleased:
			if (!player.m_isGrounded && event.joystickButton.button == (0, 0))
			{
				//DEBUG_MSG("gpp::Events::Event::GLIDE_STOP_EVENT");
				input.setCurrent(gpp::Events::Event::GLIDE_STOP_EVENT);
			}
			// Stop Attack
			else if (event.joystickButton.button == (0, 2)
				&&
				player.m_isGrounded)
			{
				//DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
				input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
			}
			else if (event.joystickButton.button == (0, 2)
				&&
				!player.m_isGrounded)
			{
				//DEBUG_MSG("gpp::Events::Event::ATTACK_STOP_EVENT");
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
				//DEBUG_MSG("gpp::Events::Event::ATTACK_START_EVENT");
				input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);

				if (!player.m_isDead)
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
				//DEBUG_MSG("gpp::Events::Event::THROW_START_EVENT");
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
				//DEBUG_MSG("gpp::Events::Event::JUMP_UP_EVENT");
				input.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
			}
			// Running Slide
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				//DEBUG_MSG("gpp::Events::Event::SLIDE_EVENT");
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
				//DEBUG_MSG("gpp::Events::Event::GLIDE_EVENT");
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
				//DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
				input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
			}
			else if (event.key.code == sf::Keyboard::Z
				&&
				player.m_isGrounded == false)
			{
				//DEBUG_MSG("gpp::Events::Event::ATTACK_STOP_EVENT");
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
				//DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
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
				//DEBUG_MSG("gpp::Events::Event::GLIDE_STOP_EVENT");
				input.setCurrent(gpp::Events::Event::GLIDE_STOP_EVENT);
			}
			break;

		default:
			//DEBUG_MSG("gpp::Events::Event::NONE");
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
}

void Game::render(sf::RenderWindow& window)
{
	// Clear screen
	window.clear();

	window.draw(bg1_sprite);
	window.draw(bg2_sprite);
	window.draw(bg3_sprite);

	window.draw(livesText);

	for (auto& life : lives)
	{
		window.draw(life);
	}

	/*window.draw(enemiesHitText);
	window.draw(enemyHUD);*/

	score.render(window);

	window.draw(daggersHUDText);
	window.draw(daggersHUD);

	/*for (int i = 0; i < 40; i++)
	{
		window.draw(tiles_ground[i]);
		window.draw(tiles_ground_1[i]);
		window.draw(tiles_ground_copy[i]);
		window.draw(tiles_ground_1_copy[i]);
	}*/


	for (size_t i = 0; i < tileArray.size(); i++)
	{
		tileArray[i]->render(window);
	}

	//window.draw(rect);

	//window.draw(cPlayerRep);

	//window.draw(rPlayerRep);

	// Draw the Players Current Animated Sprite
	if (minusOneLife && !player.m_isDead)
	{
		if (player.m_invincibilityTime.getElapsedTime().asMilliseconds() % 200 < 100)
		{
			window.draw(player.getAnimatedSpriteFrame());
		}
	}
	else
		window.draw(player.getAnimatedSpriteFrame());

	for (int i = 0; i < player.m_daggers.size(); i++)
	{
		//window.draw(rDaggersReps[i]);
		window.draw(player.m_daggers[i]);
	}

	window.draw(playerBlood);
	window.draw(enemyBlood);

	if (player.m_hasCollectedMedkit)
	{
		tileArray[collectedMedkit]->getMedkit().displayExtraLife(window, &player);
	}

	if (player.m_hasCollectedKunais)
	{
		tileArray[collectedKunais]->getExtraKunais().displayExtraKunais(window, &player);
	}

	for (auto& enemyScore : enemyScores)
	{
		enemyScore->render(window);
	}

	if (showDoubleKill)
		doubleKill.render(window);

	if (player.m_isDead)
	{
		endScreen.render(window);
	}

	// Update the window
	window.display();
}
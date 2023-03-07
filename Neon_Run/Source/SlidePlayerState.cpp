#include "Events.h"

#include "SlidePlayerState.h"

#include "RunRightPlayerState.h"
#include "DiedPlayerState.h"
#include "IdlePlayerState.h"
#include "JumpPlayerState.h"


PlayerState* SlidePlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::RUN_RIGHT_START_EVENT)
	{
		//DEBUG_MSG("SlidePlayerState -> RunRightPlayerState");
		return new RunRightPlayerState();
	}
	/*else if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("SlidePlayerState -> DiedPlayerState");
		return new DiedPlayerState(m_tiles);
	}*/
	else if (input.getCurrent() == gpp::Events::Event::JUMP_UP_EVENT) {
		//DEBUG_MSG("SlidePlayerState -> JumpPlayerState");
		return new JumpPlayerState();
	}
	return nullptr;
}
void SlidePlayerState::update(Player& player) {
	// Switch from SlidePlayerState to IdlePlayerState
	// There is a fixed time at which the slide switched
	// back to IdlePlayerState....as the gameplay programmer
	// you may wish to stop the slide and have an appropriate
	// state and animation at the end of the slide
	// this was added so sliding does not go one indefinitely

	for (int i = 0; i < player.getTiles().size(); i++)
	{
		if (player.m_feet_collision.intersects(player.getTiles()[i].getGlobalBounds()))
		{
			player.m_collision_helper++;
		}

		if (i >= player.getTiles().size() - 1)
		{
			//std::cout << "NUMBER : " << player.m_collision_helper << "\n";

			if (player.m_collision_helper > 0)
			{
				player.m_canFall = false;
				player.m_collision_helper = 0;
			}
			else
				player.m_canFall = true;
		}
	}

	if (m_clock.getElapsedTime().asSeconds() > 2.0f || player.getAnimatedSprite().getPosition().y < GROUND_POS && player.m_canFall) {
		//DEBUG_MSG("SlidePlayerState -> RunRightPlayerState");
		PlayerState* temp = player.getPlayerState();
		PlayerState* state = new RunRightPlayerState();
		player.getPlayerState()->exit(player);
		player.setPlayerState(state);
		player.getPlayerState()->enter(player);
		delete temp; // Delete previous
	}
}
void SlidePlayerState::enter(Player& player)
{
	//DEBUG_MSG("Entering SlidePlayerState");
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().setPosition(sf::Vector2f(player.getAnimatedSprite().getPosition().x, player.getAnimatedSprite().getPosition().y + 90.0f));
	player.m_canThrowDagger = false;

	player.getAnimatedSprite().addFrame(sf::IntRect(0, 550 * 11, 550, 500));

	/*player.getAnimatedSprite().addFrame(sf::IntRect(0, 5388, 373, 351));
	player.getAnimatedSprite().addFrame(sf::IntRect(373, 5388, 373, 351));
	player.getAnimatedSprite().addFrame(sf::IntRect(746, 5388, 373, 351));
	player.getAnimatedSprite().addFrame(sf::IntRect(0, 5739, 373, 351));
	player.getAnimatedSprite().addFrame(sf::IntRect(373, 5739, 373, 351));
	player.getAnimatedSprite().addFrame(sf::IntRect(746, 5739, 373, 351));
	player.getAnimatedSprite().addFrame(sf::IntRect(0, 6090, 373, 351));
	player.getAnimatedSprite().addFrame(sf::IntRect(373, 6090, 373, 351));
	player.getAnimatedSprite().addFrame(sf::IntRect(746, 6090, 373, 351));
	player.getAnimatedSprite().addFrame(sf::IntRect(0, 6441, 373, 351));*/

	player.getAnimatedSpriteFrame().setTime(seconds(0.03f));
}
void SlidePlayerState::exit(Player& player)
{
	player.getAnimatedSprite().setPosition(sf::Vector2f(player.getAnimatedSprite().getPosition().x, player.getAnimatedSprite().getPosition().y - 90.0f));
	player.m_canThrowDagger = true;

	//DEBUG_MSG("Exiting SlidePlayerState");
}

//void SlidePlayerState::setTiles(std::vector<sf::Sprite>& t_tiles)
//{
//	m_tiles = t_tiles;
//}
#include "Events.h"

#include "ThrowAttackPlayerState.h"

#include "RunRightPlayerState.h"
#include "IdlePlayerState.h"
#include "DiedPlayerState.h"

PlayerState* ThrowAttackPlayerState::handleInput(gpp::Events& input)
{
	/*if (input.getCurrent() == gpp::Events::Event::RUN_RIGHT_START_EVENT)
	{
		DEBUG_MSG("AttackPlayerState -> RunRightPlayerState");
		return new RunRightPlayerState(m_tiles);
	}
	else if (input.getCurrent() == gpp::Events::Event::THROW_STOP_EVENT)
	{
		DEBUG_MSG("AttackPlayerState -> RunRightPlayerState");
		return new RunRightPlayerState(m_tiles);
	}*/
	/*if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("ThrowAttackPlayerState -> DiedPlayerState");
		return new DiedPlayerState(m_tiles);
	}*/
	return nullptr;
}
void ThrowAttackPlayerState::update(Player& player) {
	if (m_clock.getElapsedTime().asSeconds() > .3f) {
		//DEBUG_MSG("ThrowAttackPlayerState -> RunRightPlayerState");
		PlayerState* temp = player.getPlayerState();
		PlayerState* state = new RunRightPlayerState();
		player.getPlayerState()->exit(player);
		player.setPlayerState(state);
		player.getPlayerState()->enter(player);
		delete temp; // Delete previous
	}
}
void ThrowAttackPlayerState::enter(Player& player)
{
	//DEBUG_MSG("Entering AttackPlayerState");
	player.getAnimatedSprite().clearFrames();

	for (int i = 0; i < player.m_daggers.size(); i++)
	{
		player.m_daggers[0].setPosition(player.getAnimatedSprite().getPosition().x + 90.0f, player.getAnimatedSprite().getPosition().y + 120.0f);
	}

	player.getAnimatedSprite().addFrame(sf::IntRect(0, 600 * 7, 600, 760));
	player.getAnimatedSprite().addFrame(sf::IntRect(600, 600 * 7, 600, 760));
	player.getAnimatedSprite().addFrame(sf::IntRect(600 * 2, 600 * 7, 600, 760));
	player.getAnimatedSprite().addFrame(sf::IntRect(600 * 3, 600 * 7, 600, 760));
	player.getAnimatedSprite().addFrame(sf::IntRect(600 * 4, 600 * 7, 600, 760));
	player.getAnimatedSprite().addFrame(sf::IntRect(600 * 5, 600 * 7, 600, 760));
	player.getAnimatedSprite().addFrame(sf::IntRect(600 * 6, 600 * 7, 600, 760));
	player.getAnimatedSprite().addFrame(sf::IntRect(600 * 7, 600 * 7, 600, 760));
	player.getAnimatedSprite().addFrame(sf::IntRect(600 * 8, 600 * 7, 600, 760));

	/*player.getAnimatedSprite().addFrame(sf::IntRect(6075, 0, 377, 451));
	player.getAnimatedSprite().addFrame(sf::IntRect(6452, 0, 377, 451));
	player.getAnimatedSprite().addFrame(sf::IntRect(6829, 0, 377, 451));
	player.getAnimatedSprite().addFrame(sf::IntRect(6075, 451, 377, 451));
	player.getAnimatedSprite().addFrame(sf::IntRect(6452, 451, 377, 451));
	player.getAnimatedSprite().addFrame(sf::IntRect(6829, 451, 377, 451));
	player.getAnimatedSprite().addFrame(sf::IntRect(6075, 902, 377, 451));
	player.getAnimatedSprite().addFrame(sf::IntRect(6452, 902, 377, 451));
	player.getAnimatedSprite().addFrame(sf::IntRect(6829, 902,377, 451));
	player.getAnimatedSprite().addFrame(sf::IntRect(6075, 1353, 377, 451));*/

	player.getAnimatedSprite().setTime(seconds(0.03f));
}
void ThrowAttackPlayerState::exit(Player& player)
{
	//DEBUG_MSG("Exiting AttackPlayerState");
}

//void ThrowAttackPlayerState::setTiles(std::vector<sf::Sprite>& t_tiles)
//{
//	m_tiles = t_tiles;
//}

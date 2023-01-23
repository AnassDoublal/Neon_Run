#include <Events.h>

#include <AttackPlayerState.h>

#include <RunRightPlayerState.h>
#include <IdlePlayerState.h>
#include <JumpPlayerState.h>
#include <DiedPlayerState.h>

PlayerState* AttackPlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::RUN_RIGHT_START_EVENT)
	{
		DEBUG_MSG("AttackPlayerState -> RunRightPlayerState");
		return new RunRightPlayerState(m_tiles);
	}
	else if (input.getCurrent() == gpp::Events::Event::ATTACK_STOP_EVENT)
	{
		DEBUG_MSG("AttackPlayerState -> RunRightPlayerState");
		return new RunRightPlayerState(m_tiles);
	}
	/*else if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("AttackPlayerState -> DiedPlayerState");
		return new DiedPlayerState(m_tiles);
	}*/
	return nullptr;
}
void AttackPlayerState::update(Player& player) {
	for (int i = 0; i < m_tiles.size(); i++)
	{
		if (player.m_feet_collision.intersects(m_tiles[i].getGlobalBounds()))
		{
			player.m_collision_helper++;
		}

		if (i >= m_tiles.size() - 1)
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

	if (m_clock.getElapsedTime().asSeconds() > .33f || player.getAnimatedSprite().getPosition().y < 405.0f && player.m_canFall) {
		DEBUG_MSG("AttackPlayerState -> RunRightPlayerState");
		PlayerState* temp = player.getPlayerState();
		PlayerState* state = new RunRightPlayerState(m_tiles);
		player.getPlayerState()->exit(player);
		player.setPlayerState(state);
		player.getPlayerState()->enter(player);
		delete temp; // Delete previous
	}
}
void AttackPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering AttackPlayerState");
	player.getAnimatedSprite().clearFrames();

	player.m_isAttacking = true;

	player.getAnimatedSprite().addFrame(sf::IntRect(0, 0, 536, 495));
	player.getAnimatedSprite().addFrame(sf::IntRect(536, 0, 536, 495));
	player.getAnimatedSprite().addFrame(sf::IntRect(1072, 0, 536, 495));
	player.getAnimatedSprite().addFrame(sf::IntRect(0, 495, 536, 495));
	player.getAnimatedSprite().addFrame(sf::IntRect(536, 495, 536, 495));
	player.getAnimatedSprite().addFrame(sf::IntRect(1072, 495, 536, 495));
	player.getAnimatedSprite().addFrame(sf::IntRect(0, 990, 536, 495));
	player.getAnimatedSprite().addFrame(sf::IntRect(536, 990, 536, 495));
	player.getAnimatedSprite().addFrame(sf::IntRect(1072, 990, 536, 495));
	player.getAnimatedSprite().addFrame(sf::IntRect(0, 1485, 536, 495));

	player.getAnimatedSprite().setTime(seconds(0.03f));
}
void AttackPlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting AttackPlayerState");

	player.m_isAttacking = false;
}
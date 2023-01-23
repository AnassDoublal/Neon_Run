#include <Events.h>

#include <RunRightPlayerState.h>

#include <AttackPlayerState.h>
#include <ThrowAttackPlayerState.h>
#include <IdlePlayerState.h>
#include <AccendLadderPlayerState.h>
#include <DecendLadderPlayerState.h>
#include <JumpPlayerState.h>
#include <DiedPlayerState.h>
#include <SlidePlayerState.h>

PlayerState* RunRightPlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::ATTACK_START_EVENT)
	{
		DEBUG_MSG("RunRightPlayerState -> AttackPlayerState");
		return new AttackPlayerState(m_tiles);
	}
	if (input.getCurrent() == gpp::Events::Event::THROW_START_EVENT)
	{
		DEBUG_MSG("RunRightPlayerState -> ThrowAttackPlayerState");
		return new ThrowAttackPlayerState(m_tiles);
	}
	//else if (input.getCurrent() == gpp::Events::Event::HIT_WALL_EVENT || input.getCurrent() == gpp::Events::Event::RUN_RIGHT_STOP_EVENT)
	//{
	//	DEBUG_MSG("RunRightPlayerState -> RunRightPlayerState");
	//	return new RunRightPlayerState();
	//}
	//else if (input.getCurrent() == gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT)
	//{
	//	DEBUG_MSG("RunRightPlayerState -> AccendLadderPlayerState");
	//	return new AccendLadderPlayerState();
	//}
	//else if (input.getCurrent() == gpp::Events::Event::HIT_LADDER_TOP_EVENT)
	//{
	//	DEBUG_MSG("RunRightPlayerState -> DecendLadderPlayerState");
	//	return new DecendLadderPlayerState();
	//}
	else if (input.getCurrent() == gpp::Events::Event::JUMP_UP_EVENT) {
		DEBUG_MSG("IdlePlayerState -> JumpPlayerState");
		return new JumpPlayerState(m_tiles);
	}
	else if (input.getCurrent() == gpp::Events::Event::SLIDE_EVENT) {
		DEBUG_MSG("RunRightPlayerState -> SlidePlayerState");
		return new SlidePlayerState(m_tiles);
	}
	/*else if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("RunRightPlayerState -> DiedPlayerState");
		return new DiedPlayerState(m_tiles);
	}*/
	return nullptr;
}
void RunRightPlayerState::update(Player& player) {

	for (int i=0; i<m_tiles.size(); i++)
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

	if (player.getAnimatedSprite().getPosition().y < 405.0f && player.m_canFall)
	{
		player.m_friction = .0f;
		PlayerState* temp = player.getPlayerState();
		PlayerState* state = new JumpPlayerState(m_tiles);
		player.getPlayerState()->exit(player);
		player.setPlayerState(state);
		player.getPlayerState()->enter(player);
		delete temp;
	}
}
void RunRightPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering RunRightPlayerState");
	player.getAnimatedSprite().clearFrames();

	player.m_isGrounded = true;

	player.getAnimatedSprite().addFrame(sf::IntRect(4986, 3556, 363, 458));
	player.getAnimatedSprite().addFrame(sf::IntRect(5349, 3556, 363, 458));
	player.getAnimatedSprite().addFrame(sf::IntRect(5712, 3556, 363, 458));
	player.getAnimatedSprite().addFrame(sf::IntRect(4986, 4014, 363, 458));
	player.getAnimatedSprite().addFrame(sf::IntRect(5349, 4014, 363, 458));
	player.getAnimatedSprite().addFrame(sf::IntRect(5712, 4014, 363, 458));
	player.getAnimatedSprite().addFrame(sf::IntRect(4986, 4472, 363, 458));
	player.getAnimatedSprite().addFrame(sf::IntRect(5349, 4472, 363, 458));
	player.getAnimatedSprite().addFrame(sf::IntRect(5712, 4472, 363, 458));
	player.getAnimatedSprite().addFrame(sf::IntRect(4986, 4930, 363, 458));

	player.getAnimatedSpriteFrame().setTime(seconds(0.05f));
}
void RunRightPlayerState::exit(Player& player) 
{
	DEBUG_MSG("Exiting RunRightPlayerState");
}
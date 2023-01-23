#include <Events.h>

#include <JumpPlayerState.h>

#include <DiedPlayerState.h>
#include <JumpAttackPlayerState.h>
#include <JumpThrowAttackPlayerState.h>
#include <GlidePlayerState.h>
#include <RunRightPlayerState.h>

PlayerState* JumpPlayerState::handleInput(gpp::Events& input)
{
	//if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
	//	DEBUG_MSG("JumpPlayerState -> DiedPlayerState");
	//	return new DiedPlayerState(m_tiles);
	//}
	if (input.getCurrent() == gpp::Events::Event::ATTACK_START_EVENT)
	{
		DEBUG_MSG("JumpPlayerState -> JumpAttackPlayerState");
		return new JumpAttackPlayerState(m_tiles);
	}
	else if (input.getCurrent() == gpp::Events::Event::THROW_START_EVENT)
	{
		DEBUG_MSG("JumpPlayerState -> JumpThrowAttackPlayerState");
		return new JumpThrowAttackPlayerState(m_tiles);
	}
	else if (input.getCurrent() == gpp::Events::Event::GLIDE_EVENT)
	{
		DEBUG_MSG("JumpPlayerState -> GlidePlayerState");
		return new GlidePlayerState(m_tiles);
	}
	return nullptr;
}
void JumpPlayerState::update(Player& player) {
	player.m_friction -= .002f;
	
	if (player.getAnimatedSprite().getPosition().y <= 405.0f && !player.m_tileIntersection)
	{
		for (auto& tile : m_tiles)
		{
			if (player.m_friction < 0.0f)
			{
				if (player.m_feet_collision.intersects(tile.getGlobalBounds()))
				{
					std::cout << "INTERSECTED" << "\n";
					//std::cout << tile.getPosition().x << "\n";
					player.m_tileIntersection = true;
				}

			}
		}
		player.getAnimatedSprite().move(sf::Vector2f(.0f, -1.0f * player.m_friction));

	}
	else
	{
		player.m_isGrounded = true;
	}

	//std::cout << player.getAnimatedSprite().getPosition().y << "\n";

	if (player.m_isGrounded) {
		DEBUG_MSG("JumpPlayerState -> RunRightPlayerState");
		if(!player.m_tileIntersection)
			player.getAnimatedSprite().setPosition(sf::Vector2f(50.0f, 405.0f));
		else
			player.getAnimatedSprite().setPosition(sf::Vector2f(50.0f, std::floor(player.getAnimatedSprite().getPosition().y + 10.0f)));
		PlayerState* temp = player.getPlayerState();
		PlayerState* state = new RunRightPlayerState(m_tiles);
		player.getPlayerState()->exit(player);
		player.setPlayerState(state);
		player.getPlayerState()->enter(player);
		delete temp;
	}
}
void JumpPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering JumpPlayerState");
	player.getAnimatedSprite().clearFrames();

	player.m_isGrounded = false;

	player.getAnimatedSprite().setPlayed(false);
	player.getAnimatedSprite().setLooped(false);

	player.getAnimatedSprite().addFrame(sf::IntRect(3900, 1756, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(4262, 1756, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(4624, 1756, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(3900, 2239, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(4262, 2239, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(4624, 2239, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(3900, 2722, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(4262, 2722, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(4624, 2722, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(3900, 3205, 362, 483));

	player.getAnimatedSpriteFrame().setTime(seconds(0.03f));
}
void JumpPlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting JumpPlayerState");
	player.getAnimatedSprite().setPlayed(false);
	player.getAnimatedSprite().setLooped(true);

	player.m_tileIntersection = false;
}
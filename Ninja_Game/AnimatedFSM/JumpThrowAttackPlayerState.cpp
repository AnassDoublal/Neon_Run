#include <Events.h>

#include <JumpThrowAttackPlayerState.h>

#include <RunRightPlayerState.h>
#include <GlidePlayerState.h>
#include <DiedPlayerState.h>

PlayerState* JumpThrowAttackPlayerState::handleInput(gpp::Events& input)
{
	/*if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("JumpThrowAttackPlayerState -> DiedPlayerState");
		return new DiedPlayerState(m_tiles);
	}*/
	if (input.getCurrent() == gpp::Events::Event::THROW_STOP_EVENT)
	{
		DEBUG_MSG("JumpThrowAttackPlayerState -> GlidePlayerState");
		return new GlidePlayerState(m_tiles);
	}
	return nullptr;
}
void JumpThrowAttackPlayerState::update(Player& player) {
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

	if (player.m_isGrounded) {
		DEBUG_MSG("JumpThrowAttackPlayerState -> RunRightPlayerState");
		if (!player.m_tileIntersection)
			player.getAnimatedSprite().setPosition(sf::Vector2f(50.0f, 405.0f));
		else
			player.getAnimatedSprite().setPosition(sf::Vector2f(50.0f, std::floor(player.getAnimatedSprite().getPosition().y - 25.0f)));
		PlayerState* temp = player.getPlayerState();
		PlayerState* state = new RunRightPlayerState(m_tiles);
		player.getPlayerState()->exit(player);
		player.setPlayerState(state);
		player.getPlayerState()->enter(player);
		delete temp;
	}

	if (player.m_health == 0)
	{
		PlayerState* temp = player.getPlayerState();
		PlayerState* state = new DiedPlayerState(m_tiles);
		player.getPlayerState()->exit(player);
		player.setPlayerState(state);
		player.getPlayerState()->enter(player);
		delete temp;
	}
}
void JumpThrowAttackPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering JumpThrowAttackPlayerState");
	player.getAnimatedSprite().clearFrames();

	//player.m_friction = .0f;

	for (int i = 0; i < player.m_daggers.size(); i++)
	{
		player.m_daggers[0].setPosition(player.getAnimatedSprite().getPosition().x + 90.0f, player.getAnimatedSprite().getPosition().y + 70.0f);
	}

	player.getAnimatedSprite().addFrame(sf::IntRect(4596, 0, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(4956, 0, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(5316, 0, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(4596, 431, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(4956, 431, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(5316, 431, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(4596, 862, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(4956, 862, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(5316, 862, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(4596, 1293, 360, 431));

	player.getAnimatedSprite().setTime(seconds(0.05f));
}
void JumpThrowAttackPlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting JumpThrowAttackPlayerState");
}
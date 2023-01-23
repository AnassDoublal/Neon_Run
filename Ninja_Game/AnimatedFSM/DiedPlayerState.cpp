#include <Events.h>

#include <DiedPlayerState.h>

#include <RevivedPlayerState.h>

PlayerState* DiedPlayerState::handleInput(gpp::Events& input)
{
	/*if (input.getCurrent() == gpp::Events::Event::REVIVED_EVENT)
	{
		DEBUG_MSG("DiedPlayerState -> RevivedPlayerState");
		return new RevivedPlayerState(m_tiles);
	}*/
	return nullptr;
}
void DiedPlayerState::update(Player& player) {
	player.m_friction -= .002f;

	if (player.getAnimatedSprite().getPosition().y < 405.0f && !player.m_tileIntersection && !player.m_isGrounded)
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
		/*if(!player.m_isGrounded && player.getAnimatedSprite().getPosition().y < 405.0f)
			player.getAnimatedSprite().setPosition(player.getAnimatedSprite().getPosition().x, player.getAnimatedSprite().getPosition().y + 5.0f);*/

		player.m_isGrounded = true;
	}

	if (player.m_isGrounded) {
		if (player.getAnimatedSprite().getPosition().y >= 405.0f)
		{
			player.getAnimatedSprite().setPosition(sf::Vector2f(50.0f, 405.0f));
		}
		else
		{
			player.getAnimatedSprite().setPosition(sf::Vector2f(50.0f, std::floor(player.getAnimatedSprite().getPosition().y)));
		}
	}

	/*if(player.m_tileIntersection)
		player.m_friction = .0f;*/

	//std::cout << player.getAnimatedSprite().getPosition().y << "\n";
}
void DiedPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering DiedPlayerState");
	player.getAnimatedSprite().clearFrames();

	player.m_isDead = true;

	player.getAnimatedSprite().setPlayed(false);
	player.getAnimatedSprite().setLooped(false);

	player.getAnimatedSprite().addFrame(sf::IntRect(2454, 0, 482, 498));
	player.getAnimatedSprite().addFrame(sf::IntRect(2936, 0, 482, 498));
	player.getAnimatedSprite().addFrame(sf::IntRect(3418, 0, 482, 498));
	player.getAnimatedSprite().addFrame(sf::IntRect(2454, 498, 482, 498));
	player.getAnimatedSprite().addFrame(sf::IntRect(2936, 498, 482, 498));
	player.getAnimatedSprite().addFrame(sf::IntRect(3418, 498, 482, 498));
	player.getAnimatedSprite().addFrame(sf::IntRect(2454, 996, 482, 498));
	player.getAnimatedSprite().addFrame(sf::IntRect(2936, 996, 482, 498));
	player.getAnimatedSprite().addFrame(sf::IntRect(3418, 996, 482, 498));
	player.getAnimatedSprite().addFrame(sf::IntRect(2454, 1494, 482, 498));

	player.getAnimatedSprite().setTime(seconds(0.03f));
}
void DiedPlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting DiedPlayerState");
	player.getAnimatedSprite().setPlayed(false);
	player.getAnimatedSprite().setLooped(true);
}
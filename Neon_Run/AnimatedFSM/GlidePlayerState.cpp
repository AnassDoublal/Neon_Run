#include "Events.h"

#include "GlidePlayerState.h"

#include "DiedPlayerState.h"
#include "IdlePlayerState.h"
#include "RunRightPlayerState.h"
#include "JumpPlayerState.h"


PlayerState* GlidePlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::HIT_GROUND_EVENT)
	{
		//DEBUG_MSG("GlidePlayerState -> RunRightPlayerState");
		return new RunRightPlayerState();
	}
	/*else if (input.getCurrent() == gpp::Events::Event::DIED_EVENT)
	{
		DEBUG_MSG("GlidePlayerState -> DiedPlayerState");
		return new DiedPlayerState(m_tiles);
	}*/
	else if (input.getCurrent() == gpp::Events::Event::GLIDE_STOP_EVENT)
	{
		//DEBUG_MSG("GlidePlayerState -> JumpPlayerState");
		return new JumpPlayerState();
	}
	return nullptr;
}
void GlidePlayerState::update(Player& player) {
	//DEBUG_MSG("GlidePlayerState -> RunRightPlayerState");

	player.getAnimatedSprite().move(sf::Vector2f(.0f, .25f));

	if (player.getAnimatedSprite().getPosition().y >= GROUND_POS)
	{
		player.getAnimatedSprite().setPosition(sf::Vector2f(50.0f, GROUND_POS));
		player.m_isGrounded = true;
	}

	for (auto& tile : player.getTiles())
	{
		if (player.m_feet_collision.intersects(tile.getGlobalBounds()))
		{
			player.getAnimatedSprite().setPosition(sf::Vector2f(50.0f, std::floor(player.getAnimatedSprite().getPosition().y + 1.0f)));
			player.m_isGrounded = true;
		}
	}

	if (player.m_isGrounded) {
		PlayerState* temp = player.getPlayerState();
		PlayerState* state = new RunRightPlayerState();
		player.getPlayerState()->exit(player);
		player.setPlayerState(state);
		player.getPlayerState()->enter(player);
		delete temp;
	}
}
void GlidePlayerState::enter(Player& player)
{
	//DEBUG_MSG("Entering GlidePlayerState");

	player.getAnimatedSprite().clearFrames();

	player.m_canThrowDagger = false;

	player.getAnimatedSprite().addFrame(sf::IntRect(0, 575 * 3, 575, 760));
	player.getAnimatedSprite().addFrame(sf::IntRect(575, 575 * 3, 575, 760));
	player.getAnimatedSprite().addFrame(sf::IntRect(575 * 2, 575 * 3, 575, 760));
	player.getAnimatedSprite().addFrame(sf::IntRect(575 * 3, 575 * 3, 575, 760));
	player.getAnimatedSprite().addFrame(sf::IntRect(575 * 4, 575 * 3, 575, 760));
	player.getAnimatedSprite().addFrame(sf::IntRect(575 * 5, 575 * 3, 575, 760));
	player.getAnimatedSprite().addFrame(sf::IntRect(575 * 6, 575 * 3, 575, 760));
	player.getAnimatedSprite().addFrame(sf::IntRect(575 * 7, 575 * 3, 575, 760));
	player.getAnimatedSprite().addFrame(sf::IntRect(575 * 8, 575 * 3, 575, 760));
	player.getAnimatedSprite().addFrame(sf::IntRect(575 * 9, 575 * 3, 575, 760));
	player.getAnimatedSprite().addFrame(sf::IntRect(575 * 10, 575 * 3, 575, 760));

	/*player.getAnimatedSprite().addFrame(sf::IntRect(0, 1992, 443, 454));
	player.getAnimatedSprite().addFrame(sf::IntRect(443, 1992, 443, 454));
	player.getAnimatedSprite().addFrame(sf::IntRect(886, 1992, 443, 454));
	player.getAnimatedSprite().addFrame(sf::IntRect(0, 2446, 443, 454));
	player.getAnimatedSprite().addFrame(sf::IntRect(443, 2446, 443, 454));
	player.getAnimatedSprite().addFrame(sf::IntRect(886, 2446, 443, 454));
	player.getAnimatedSprite().addFrame(sf::IntRect(0, 2900, 443, 454));
	player.getAnimatedSprite().addFrame(sf::IntRect(443, 2900, 443, 454));
	player.getAnimatedSprite().addFrame(sf::IntRect(886, 2900, 443, 454));
	player.getAnimatedSprite().addFrame(sf::IntRect(0, 3354, 443, 454));*/

	player.getAnimatedSprite().setTime(seconds(0.04f));
}
void GlidePlayerState::exit(Player& player)
{
	player.m_friction = .0f;

	player.m_canThrowDagger = true;

	//DEBUG_MSG("Exiting GlidePlayerState");
}

//void GlidePlayerState::setTiles(std::vector<sf::Sprite>& t_tiles)
//{
//	m_tiles = t_tiles;
//}

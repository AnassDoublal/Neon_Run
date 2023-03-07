#include "Events.h"

#include "JumpAttackPlayerState.h"

#include "RunRightPlayerState.h"
#include "GlidePlayerState.h"
#include "DiedPlayerState.h"
#include "JumpPlayerState.h"


PlayerState* JumpAttackPlayerState::handleInput(gpp::Events& input)
{
	/*if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("JumpAttackPlayerState -> DiedPlayerState");
		return new DiedPlayerState(m_tiles);
	}*/
	if (input.getCurrent() == gpp::Events::Event::ATTACK_STOP_EVENT)
	{
		//DEBUG_MSG("JumpAttackPlayerState -> JumpPlayerState");
		return new JumpPlayerState();
	}
	return nullptr;
}
void JumpAttackPlayerState::update(Player& player) {
	player.m_friction -= .0075f;

	if (player.getAnimatedSprite().getPosition().y <= GROUND_POS && !player.m_tileIntersection)
	{
		for (auto& tile : player.getTiles())
		{
			if (player.m_friction < 0.0f)
			{
				if (player.m_feet_collision.intersects(tile.getGlobalBounds()))
				{
					//std::cout << "INTERSECTED" << "\n";
					//std::cout << tile.getPosition().x << "\n";
					player.m_tileIntersection = true;
				}

			}
		}
		//std::cout << "FRICTION IS : " << player.m_friction << "\n";
		player.getAnimatedSprite().move(sf::Vector2f(.0f, -4.0f * player.m_friction));
	}
	else
	{
		player.m_isGrounded = true;
	}

	if (player.m_isGrounded) {
		//DEBUG_MSG("JumpAttackPlayerState -> RunRightPlayerState");
		if (!player.m_tileIntersection)
			player.getAnimatedSprite().setPosition(sf::Vector2f(50.0f, GROUND_POS));
		else
			player.getAnimatedSprite().setPosition(sf::Vector2f(50.0f, std::floor(player.getAnimatedSprite().getPosition().y + 10.0f)));
		PlayerState* temp = player.getPlayerState();
		PlayerState* state = new RunRightPlayerState();
		player.getPlayerState()->exit(player);
		player.setPlayerState(state);
		player.getPlayerState()->enter(player);
		delete temp;
	}
}
void JumpAttackPlayerState::enter(Player& player)
{
	//DEBUG_MSG("Entering JumpAttackPlayerState");
	player.getAnimatedSprite().clearFrames();

	//player.m_friction = .0f;

	player.m_isAttacking = true;

	player.getAnimatedSprite().addFrame(sf::IntRect(0, 700 * 4, 700, 820));
	player.getAnimatedSprite().addFrame(sf::IntRect(700, 700 * 4, 700, 820));
	player.getAnimatedSprite().addFrame(sf::IntRect(700 * 2, 700 * 4, 700, 820));
	player.getAnimatedSprite().addFrame(sf::IntRect(700 * 3, 700 * 4, 700, 820));
	player.getAnimatedSprite().addFrame(sf::IntRect(700 * 4, 700 * 4, 700, 820));
	player.getAnimatedSprite().addFrame(sf::IntRect(700 * 5, 700 * 4, 700, 820));
	player.getAnimatedSprite().addFrame(sf::IntRect(700 * 6, 700 * 4, 700, 820));
	player.getAnimatedSprite().addFrame(sf::IntRect(700 * 7, 700 * 4, 700, 820));

	/*player.getAnimatedSprite().addFrame(sf::IntRect(1329, 1992, 504, 522));
	player.getAnimatedSprite().addFrame(sf::IntRect(1851, 1992, 504, 522));
	player.getAnimatedSprite().addFrame(sf::IntRect(2373, 1992, 504, 522));
	player.getAnimatedSprite().addFrame(sf::IntRect(1329, 2514, 504, 522));
	player.getAnimatedSprite().addFrame(sf::IntRect(1851, 2514, 504, 522));
	player.getAnimatedSprite().addFrame(sf::IntRect(2373, 2514, 504, 522));
	player.getAnimatedSprite().addFrame(sf::IntRect(1329, 3036, 504, 522));
	player.getAnimatedSprite().addFrame(sf::IntRect(1851, 3036, 504, 522));*/
	/*player.getAnimatedSprite().addFrame(sf::IntRect(2373, 3036, 504, 522));
	player.getAnimatedSprite().addFrame(sf::IntRect(1329, 3558, 504, 522));*/

	player.getAnimatedSprite().setTime(seconds(0.04f));
}
void JumpAttackPlayerState::exit(Player& player)
{
	//DEBUG_MSG("Exiting JumpAttackPlayerState");

	player.m_friction = .0f;

	player.m_isAttacking = false;
}

//void JumpAttackPlayerState::setTiles(std::vector<sf::Sprite>& t_tiles)
//{
//	m_tiles = t_tiles;
//}
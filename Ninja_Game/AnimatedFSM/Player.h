#ifndef PLAYER_H
#define PLAYER_H
#include <Events.h>
#include <PlayerState.h>
#include <AnimatedSprite.h>
#include <map>
#include "Tiles.h"

class Player
{
public:
	Player(const AnimatedSprite&);
	virtual void handleInput(gpp::Events);
	virtual void update();
	AnimatedSprite& getAnimatedSprite();
	AnimatedSprite& getAnimatedSpriteFrame();
	void setAnimatedSprite(AnimatedSprite&);
	PlayerState* getPlayerState();
	void setPlayerState(PlayerState*);
	void setTiles(std::vector<sf::Sprite>& t_tiles);
	std::vector<sf::Sprite>& getTiles();
	float m_friction = 1.0f;
	bool m_isGrounded = true;
	bool m_tileIntersection = false;
	sf::FloatRect m_feet_collision;
	int m_collision_helper = 0;
	bool m_canFall = false;
	bool m_isAttacking = false;

	std::vector<sf::Sprite> m_daggers;
	std::vector<Rectangle> m_daggers_rectangles;

	int m_health = 3;
	bool m_isDead = false;

	bool m_canThrowDagger = true;

	int m_totalShots = 0;
	int m_shotsHit = 0;

	sf::Clock m_invincibilityTime;
	bool m_isInvincibilityClockRestarted = false;

	float m_speed = .8f;
	float m_maxSpeed = 2.0f;
private:
	PlayerState* m_state;
	AnimatedSprite m_animated_sprite;
	std::vector<sf::Sprite> m_tiles;
};
#endif


#include <stdio.h>
#include <Player.h>
#include <Events.h>
#include <IdlePlayerState.h>
#include <RunRightPlayerState.h>
#include <DiedPlayerState.h>

Player::Player(const AnimatedSprite& sprite, Tiles* t_tilesPtr) : m_animated_sprite(sprite), m_tilesPtr(t_tilesPtr), m_tiles(m_tilesPtr->getTiles())
{
	// Set the Player to Default to IdlePlayer State 
	// and Enter that State
	m_state = new RunRightPlayerState(m_tiles);
	m_state->enter(*this);
}

void Player::handleInput(gpp::Events input) {
	PlayerState * state = m_state->handleInput(input);

	if (state != NULL) {
		m_state->exit(*this);
		delete m_state;
		m_state = state;
		m_state->enter(*this);
	}
}

void Player::update() {
	m_tiles = m_tilesPtr->getTiles();
	std::cout << m_tilesPtr << "\n";
	m_feet_collision = sf::FloatRect(getAnimatedSprite().getPosition().x + 2.0f,
									 getAnimatedSprite().getPosition().y + getAnimatedSprite().getGlobalBounds().height - 20.0f,
									 getAnimatedSprite().getGlobalBounds().width - 15.0f,
									 15.0f);
	m_animated_sprite.update();

	if (m_health > 0)
	{
		m_state->update(*this);
	}
	else
	{
		if (!m_isDead)
		{	
			PlayerState* temp;
			PlayerState* state;
			temp = getPlayerState();
			state = new DiedPlayerState(m_tiles);
			getPlayerState()->exit(*this);
			setPlayerState(state);
			getPlayerState()->enter(*this);
			delete temp;
		}

		getPlayerState()->update(*this);
	}

	//std::cout << "TILE INTERSECTION : " << m_tileIntersection << "\n";
}

AnimatedSprite& Player::getAnimatedSprite() {
	return m_animated_sprite;
}

AnimatedSprite& Player::getAnimatedSpriteFrame() {
	int frame = m_animated_sprite.getCurrentFrame();
	m_animated_sprite.setTextureRect(m_animated_sprite.getFrame(frame));
	m_animated_sprite.setScale(sf::Vector2f(.3f, .3f));
	return m_animated_sprite;
}

void Player::setAnimatedSprite(AnimatedSprite& animated_sprite) {
	this->m_animated_sprite = animated_sprite;
}

PlayerState* Player::getPlayerState() { return this->m_state; }

void Player::setPlayerState(PlayerState* state) { this->m_state = state; }

Tiles* Player::getTiles()
{
	return m_tilesPtr;
}

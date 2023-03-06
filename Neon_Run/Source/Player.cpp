#include "stdio.h"
#include "Player.h"
#include "Events.h"
#include "IdlePlayerState.h"
#include "RunRightPlayerState.h"
#include "DiedPlayerState.h"

Player::Player(const AnimatedSprite& sprite) : m_animated_sprite(sprite)
{
	// Set the Player to Default to RunRightPlayer State 
	// and Enter that State
	m_state = new RunRightPlayerState();
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
	//std::cout << m_tilesPtr << "\n";
	//m_tiles = m_tilesPtr->getTiles();

	//std::cout << "PLAYER POINTER : " << m_tilesPtr << "\n\n";

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
			state = new DiedPlayerState();
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

void Player::setTiles(std::vector<sf::Sprite>& t_tiles)
{
	m_tiles = t_tiles;
}

std::vector<sf::Sprite>& Player::getTiles()
{
	return m_tiles;
}

void Player::addReward(sf::RenderWindow& window, std::string string, std::vector<std::shared_ptr<Reward>>& rewards)
{
	std::shared_ptr<Reward> reward = std::make_shared<Reward>();
	reward->init(window, rewards.size() + 1);
	reward->getText().setString(string);
	rewards.push_back(reward);
}

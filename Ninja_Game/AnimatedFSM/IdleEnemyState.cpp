#include <Events.h>

#include <IdleEnemyState.h>
#include <ThrowAttackEnemyState.h>
#include <DiedEnemyState.h>

EnemyState* IdleEnemyState::setAction() {

	/*if (input.getCurrent() == gpp::Events::Event::ATTACK_START_EVENT)
	{
		DEBUG_MSG("IdlePlayerState -> AttackPlayerState");
		return new AttackPlayerState(m_tiles);
	}
	else if (input.getCurrent() == gpp::Events::Event::THROW_START_EVENT)
	{
		DEBUG_MSG("IdlePlayerState -> ThrowAttackPlayerState");
		return new ThrowAttackPlayerState(m_tiles);
	}*/
	/*else if (input.getCurrent() == gpp::Events::Event::RUN_RIGHT_START_EVENT) {
		DEBUG_MSG("IdlePlayerState -> RunRightPlayerState");
		return new RunRightPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT) {
		DEBUG_MSG("IdlePlayerState -> AccendLadderPlayerState");
		return new AccendLadderPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::HIT_LADDER_TOP_EVENT) {
		DEBUG_MSG("IdlePlayerState -> DecendLadderPlayerState");
		return new DecendLadderPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::JUMP_UP_EVENT) {
		DEBUG_MSG("IdlePlayerState -> JumpPlayerState");
		return new JumpPlayerState();
	}*/
	/*else if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("IdlePlayerState -> DiedPlayerState");
		return new DiedPlayerState(m_tiles);
	}*/
	return nullptr;
}

void IdleEnemyState::update(Enemy& enemy) {
	if (!enemy.m_isDead)
	{
		if (enemy.m_animated_sprite.getPosition().x < 800.0f && !enemy.m_isPlayerDead)
		{
			if (m_clock.getElapsedTime().asSeconds() > 1.0f) {
				DEBUG_MSG("IdleEnemyState -> ThrowAttackEnemyState");
				EnemyState* temp = enemy.getEnemyState();
				EnemyState* state = new ThrowAttackEnemyState();
				enemy.getEnemyState()->exit(enemy);
				enemy.setEnemyState(state);
				enemy.getEnemyState()->enter(enemy);
				delete temp; // Delete previous
			}
		}
	}
	else
	{
		DEBUG_MSG("IdleEnemyState -> DiedEnemyState");
		EnemyState* temp = enemy.getEnemyState();
		EnemyState* state = new DiedEnemyState();
		enemy.getEnemyState()->exit(enemy);
		enemy.setEnemyState(state);
		enemy.getEnemyState()->enter(enemy);
		delete temp; // Delete previous
	}
}

void IdleEnemyState::enter(Enemy& enemy)
{
	DEBUG_MSG("ENTERED THE IDLE ENEMY STATE BABY WE GOT IT OMG");
	enemy.getAnimatedSprite().clearFrames();

	enemy.getAnimatedSprite().addFrame(sf::IntRect(3900, 0, 232, 439));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(4132, 0, 232, 439));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(4364, 0, 232, 439));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(3900, 439, 232, 439));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(4132, 439, 232, 439));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(4364, 439, 232, 439));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(3900, 878, 232, 439));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(4132, 878, 232, 439));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(4364, 878, 232, 439));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(3900, 1317, 232, 439));

	enemy.getAnimatedSprite().setTime(seconds(0.05f));
}

void IdleEnemyState::exit(Enemy& enemy)
{
	DEBUG_MSG("Exiting IdlePlayerState");
}
#include "Events.h"

#include "AttackEnemyState.h"
#include "ThrowAttackEnemyState.h"
#include "DiedEnemyState.h"
#include "IdleEnemyState.h"

EnemyState* AttackEnemyState::setAction() {

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

void AttackEnemyState::update(Enemy& enemy) {
	if (!enemy.m_isDead)
	{
		if (enemy.m_animated_sprite.getPosition().x < 1920.0f)
		{
			if (m_clock.getElapsedTime().asSeconds() > .3f) {
				//DEBUG_MSG("ThrowAttackEnemyState -> IdleEnemyState");
				EnemyState* temp = enemy.getEnemyState();
				EnemyState* state = new IdleEnemyState();
				enemy.getEnemyState()->exit(enemy);
				enemy.setEnemyState(state);
				enemy.getEnemyState()->enter(enemy);
				delete temp; // Delete previous
			}
		}
	}
	else
	{
		//DEBUG_MSG("IdleEnemyState -> DiedEnemyState");
		EnemyState* temp = enemy.getEnemyState();
		EnemyState* state = new DiedEnemyState();
		enemy.getEnemyState()->exit(enemy);
		enemy.setEnemyState(state);
		enemy.getEnemyState()->enter(enemy);
		delete temp; // Delete previous
	}
}

void AttackEnemyState::enter(Enemy& enemy)
{
	enemy.m_isAttacking = true;

	enemy.m_action = Enemy::Action::SWORD;

	enemy.getAnimatedSprite().setPosition(enemy.getAnimatedSprite().getPosition().x - 100.0f, enemy.getAnimatedSprite().getPosition().y - 20.0f);

	//DEBUG_MSG("ENTERED THE IDLE ENEMY STATE BABY WE GOT IT OMG");
	enemy.getAnimatedSprite().clearFrames();

	/*enemy.getAnimatedSprite().addFrame(sf::IntRect(3900, 0, 232, 439));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(4132, 0, 232, 439));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(4364, 0, 232, 439));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(3900, 439, 232, 439));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(4132, 439, 232, 439));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(4364, 439, 232, 439));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(3900, 878, 232, 439));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(4132, 878, 232, 439));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(4364, 878, 232, 439));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(3900, 1317, 232, 439));*/

	enemy.getAnimatedSprite().addFrame(sf::IntRect(0, 600 * 7, 1200, 1300));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(1200, 600 * 7, 1200, 1300));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(1200 * 2, 600 * 7, 1200, 1300));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(1200 * 3, 600 * 7, 1200, 1300));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(0, 600 * 9, 1200, 1300));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(1200, 600 * 9, 1200, 1300));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(1200 * 2, 600 * 9, 1200, 1300));

	enemy.getAnimatedSprite().setTime(seconds(0.04f));
}

void AttackEnemyState::exit(Enemy& enemy)
{
	enemy.m_isAttacking = false;

	enemy.getAnimatedSprite().setPosition(enemy.getAnimatedSprite().getPosition().x + 100.0f, enemy.getAnimatedSprite().getPosition().y + 20.0f);
	//DEBUG_MSG("Exiting IdlePlayerState");
}
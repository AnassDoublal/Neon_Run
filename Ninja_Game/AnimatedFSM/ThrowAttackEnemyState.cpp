#include <Events.h>

#include <ThrowAttackEnemyState.h>
#include <IdleEnemyState.h>
#include <DiedEnemyState.h>

EnemyState* ThrowAttackEnemyState::setAction() {
	return nullptr;
}

void ThrowAttackEnemyState::update(Enemy& enemy) {
	if (!enemy.m_isDead)
	{
		if (enemy.m_animated_sprite.getPosition().x < 800.0f)
		{
			if (m_clock.getElapsedTime().asSeconds() > .3f) {
				DEBUG_MSG("ThrowAttackEnemyState -> IdleEnemyState");
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
		DEBUG_MSG("IdleEnemyState -> DiedEnemyState");
		EnemyState* temp = enemy.getEnemyState();
		EnemyState* state = new DiedEnemyState();
		enemy.getEnemyState()->exit(enemy);
		enemy.setEnemyState(state);
		enemy.getEnemyState()->enter(enemy);
		delete temp; // Delete previous
	}
}

void ThrowAttackEnemyState::enter(Enemy& enemy)
{
	DEBUG_MSG("ENTERED THE THROWING ENEMY STATE");
	enemy.getAnimatedSprite().clearFrames();

	if (enemy.m_animated_sprite.getPosition().x < 800.0f)
	{
		for (int i = 0; i < enemy.m_daggers.size(); i++)
		{
			enemy.m_daggers[0].setPosition(enemy.getAnimatedSprite().getPosition().x - 90.0f, enemy.getAnimatedSprite().getPosition().y + 70.0f);
		}

		enemy.m_daggerThrow = true;
	}

	enemy.getAnimatedSprite().addFrame(sf::IntRect(6075, 0, 377, 451));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(6452, 0, 377, 451));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(6829, 0, 377, 451));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(6075, 451, 377, 451));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(6452, 451, 377, 451));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(6829, 451, 377, 451));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(6075, 902, 377, 451));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(6452, 902, 377, 451));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(6829, 902, 377, 451));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(6075, 1353, 377, 451));

	enemy.getAnimatedSprite().setTime(seconds(0.03f));
}

void ThrowAttackEnemyState::exit(Enemy& enemy)
{
	DEBUG_MSG("Exiting ThrowAttackPlayerState");
}
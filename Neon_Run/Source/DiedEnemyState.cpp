#include "Events.h"

#include "DiedEnemyState.h"
#include "IdleEnemyState.h"

EnemyState* DiedEnemyState::setAction() {
	return nullptr;
}

void DiedEnemyState::update(Enemy& enemy) {
	if (enemy.m_animated_sprite.getPosition().x > 1920.0f)
	{
		enemy.m_isDead = false;
		enemy.m_rectangle.setWidth(enemy.getAnimatedSprite().getGlobalBounds().width);
		enemy.m_rectangle.setHeight(enemy.getAnimatedSprite().getGlobalBounds().height);

		for (int i = 0; i < 50 - enemy.m_daggers.size(); i++)
		{
			sf::Sprite dagger;
			dagger.setTexture(enemy.m_daggerTexture);
			dagger.setPosition(10000.0f, 10000.0f);
			dagger.setScale(-.5f, .5f);
			enemy.m_daggers.push_back(dagger);
		}

		//DEBUG_MSG("DiedEnemyState -> IdleEnemyState");
		EnemyState* temp = enemy.getEnemyState();
		EnemyState* state = new IdleEnemyState();
		enemy.getEnemyState()->exit(enemy);
		enemy.setEnemyState(state);
		enemy.getEnemyState()->enter(enemy);
		delete temp; // Delete previous
	}
}

void DiedEnemyState::enter(Enemy& enemy)
{
	//DEBUG_MSG("ENTERED DIED ENEMY STATE");
	enemy.getAnimatedSprite().clearFrames();

	enemy.getAnimatedSprite().setPlayed(false);
	enemy.getAnimatedSprite().setLooped(false);

	enemy.getAnimatedSprite().setPosition(enemy.getAnimatedSprite().getPosition().x - 50.0f, enemy.getAnimatedSprite().getPosition().y);

	/*enemy.getAnimatedSprite().addFrame(sf::IntRect(2454, 0, 482, 498));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(2936, 0, 482, 498));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(3418, 0, 482, 498));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(2454, 498, 482, 498));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(2936, 498, 482, 498));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(3418, 498, 482, 498));*/

	/*enemy.getAnimatedSprite().addFrame(sf::IntRect(2454, 996, 482, 498));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(2936, 996, 482, 498));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(3418, 996, 482, 498));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(2454, 1494, 482, 498));*/

	enemy.getAnimatedSprite().addFrame(sf::IntRect(0, 1000 * 3, 1000, 970));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(1000, 1000 * 3, 1000, 970));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(1000 * 2, 1000 * 3, 1000, 970));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(1000 * 3, 1000 * 3, 1000, 970));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(1000 * 4, 1000 * 3, 1000, 970));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(1000 * 5, 1000 * 3, 1000, 970));
	enemy.getAnimatedSprite().addFrame(sf::IntRect(1000 * 6, 1000 * 3, 1000, 970));

	enemy.getAnimatedSprite().setTime(seconds(0.07f));
}

void DiedEnemyState::exit(Enemy& enemy)
{
	//DEBUG_MSG("Exiting DiedEnemyState");
	enemy.getAnimatedSprite().setPlayed(false);
	enemy.getAnimatedSprite().setLooped(true);
}
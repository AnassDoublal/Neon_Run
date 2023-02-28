#pragma once

#include "Enemy.h"
#include "EnemyState.h"

class ThrowAttackEnemyState : public EnemyState {
public:
	virtual EnemyState* setAction();
	virtual void update(Enemy&);
	virtual void enter(Enemy&);
	virtual void exit(Enemy&);
private:
	sf::Clock m_clock;
};
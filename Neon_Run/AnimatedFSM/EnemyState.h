#pragma once

#include "Debug.h"
#include "Events.h"
#include "vector"
#include "SFML/Graphics.hpp"

class Enemy;
class Player;

class EnemyState {
	public:
		virtual ~EnemyState() {};
		virtual EnemyState* setAction() = 0;
		virtual void update(Enemy&) = 0;
		virtual void enter(Enemy&) = 0;
		virtual void exit(Enemy&) = 0;
};
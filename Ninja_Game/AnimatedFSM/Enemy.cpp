#include "Enemy.h"
#include "IdleEnemyState.h"

#include "Player.h"

//Enemy::Enemy(const AnimatedSprite& sprite) : m_animated_sprite(sprite)
//{
//
//}

void Enemy::init(sf::RenderWindow& window, float posX, float PosY)
{
	if (!m_texture.loadFromFile("assets/EnemySpriteSheet.png")) {
		std::cout << "error loading enemy spritesheet";
	}

	m_animated_sprite.setTexture(m_texture);
	m_animated_sprite.setTextureRect(sf::IntRect(3900, 0, 232, 439));
	m_animated_sprite.setScale(-.3f, .3f);
	m_animated_sprite.setPosition(window.getSize().x + posX, PosY);

	m_state = new IdleEnemyState();
	m_state->enter(*this);

	//m_circle.setRadius(m_animated_sprite.getGlobalBounds().height / 2.0f);

	//m_circle_rep.setRadius(m_animated_sprite.getGlobalBounds().height / 2.0f);
	//m_circle_rep.setFillColor(sf::Color::Cyan);

	m_rectangle.setWidth(m_animated_sprite.getGlobalBounds().width);
	m_rectangle.setHeight(m_animated_sprite.getGlobalBounds().height);

	m_rectangle_rep.setSize(sf::Vector2f(m_animated_sprite.getGlobalBounds().width, m_animated_sprite.getGlobalBounds().height));
	m_rectangle_rep.setFillColor(sf::Color::Cyan);
	//m_rectangle_rep.setScale(-1.0f, 1.0f);

	if (!m_daggerTexture.loadFromFile("assets/Kunai.png"))
	{
		DEBUG_MSG("Failed to load kunai");
	}

	for (int i = 0; i < 50; i++)
	{
		sf::Sprite dagger;
		dagger.setTexture(m_daggerTexture);
		dagger.setPosition(10000.0f, 10000.0f);
		dagger.setScale(-.5f, .5f);
		m_daggers.push_back(dagger);
	}

	for (int i = 0; i < 50; i++)
	{
		Rectangle rDagger(m_daggers[i].getPosition().x,
						  m_daggers[i].getPosition().y,
						  m_daggers[i].getGlobalBounds().width,
						  m_daggers[i].getGlobalBounds().height);

		m_daggers_rectangles.push_back(rDagger);
	}

	m_animated_sprite.setScale(.0f, .0f);
}

void Enemy::update(sf::RenderWindow& window, Player* player)
{
	/*m_circle.updateX(m_animated_sprite.getPosition().x, m_animated_sprite.getGlobalBounds().width * 1.5);
	m_circle.updateY(m_animated_sprite.getPosition().y);

	m_circle_rep.setPosition(m_animated_sprite.getPosition().x - m_animated_sprite.getGlobalBounds().width * 1.5,
						     m_animated_sprite.getPosition().y);*/

	m_rectangle_rep.setPosition(m_animated_sprite.getPosition().x - m_animated_sprite.getGlobalBounds().width, m_animated_sprite.getPosition().y);

	if (!player->m_isDead)
	{
		m_animated_sprite.move(-.5f, .0f);
	}
	else
	{
		m_friction *= .999f;
		m_animated_sprite.move(-m_friction, .0f);

		m_isPlayerDead = true;
	}

	m_animated_sprite.update();

	if (m_daggers.size() > 0)
	{
		if (m_rectangle.getWidth() != .0f)
		{
			m_rectangle.updateX(m_animated_sprite.getPosition().x, m_animated_sprite.getGlobalBounds().width);
			m_rectangle.updateY(m_animated_sprite.getPosition().y);
		}
		else
		{
			m_rectangle.updateY(-10000.0f);
		}
	}

	m_state->update(*this);
	
	if (m_daggers.size() > 0 && m_daggers_rectangles.size() > 0)
	{
		if (m_daggerThrow)
		{
			m_daggers[0].move(-10.0f, .0f);
			m_daggers_rectangles[0].updateX(m_daggers[0].getPosition().x, .0f);
			m_daggers_rectangles[0].updateY(m_daggers[0].getPosition().y);
		}

		if (m_daggers[0].getPosition().x < .0f)
		{
			m_daggers.erase(m_daggers.begin());
			m_daggers_rectangles.erase(m_daggers_rectangles.begin());
			m_daggerThrow = false;
		}
	}
}

void Enemy::render(sf::RenderWindow& window)
{
	//window.draw(m_circle_rep);
	//window.draw(m_rectangle_rep);
	window.draw(getAnimatedSpriteFrame());

	for (auto& dagger : m_daggers)
	{
		window.draw(dagger);
	}
}

AnimatedSpriteEnemy& Enemy::getAnimatedSprite() {
	return m_animated_sprite;
}

AnimatedSpriteEnemy& Enemy::getAnimatedSpriteFrame() {
	int frame = m_animated_sprite.getCurrentFrame();
	m_animated_sprite.setTextureRect(m_animated_sprite.getFrame(frame));
	return m_animated_sprite;
}

EnemyState* Enemy::getEnemyState() { return this->m_state; }

void Enemy::setEnemyState(EnemyState* state) { this->m_state = state; }
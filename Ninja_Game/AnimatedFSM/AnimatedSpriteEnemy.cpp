#include <AnimatedSpriteEnemy.h>

AnimatedSpriteEnemy::AnimatedSpriteEnemy() :
	m_current_frame(0),
	m_time(seconds(0.5f)),
	m_loop(true),
	m_play_count(0),
	m_max_plays(0),
	m_played(false)
{
	//DEBUG_MSG("AnimatedSprite()");
}

AnimatedSpriteEnemy::AnimatedSpriteEnemy(const sf::Texture& t) : AnimatedSpriteEnemy() {
	//DEBUG_MSG("AnimatedSprite(const Texture&)");
	this->setTexture(t);
}

AnimatedSpriteEnemy::AnimatedSpriteEnemy(const sf::Texture& t, const sf::IntRect& rect) :
	AnimatedSpriteEnemy(t)
{
	//DEBUG_MSG("AnimatedSprite(const Texture&, const IntRect&)");
	m_frames.push_back(rect);
}

AnimatedSpriteEnemy::~AnimatedSpriteEnemy() {
	//DEBUG_MSG("~AnimatedSprite()");
}

const sf::Clock& AnimatedSpriteEnemy::getClock() {
	return m_clock;
}

const sf::Time& AnimatedSpriteEnemy::getTime() {
	return m_time;
}

void AnimatedSpriteEnemy::setTime(Time t)
{
	this->m_time = t;
}

const vector<IntRect>& AnimatedSpriteEnemy::getFrames() {
	return m_frames;
}

void AnimatedSpriteEnemy::clearFrames() {
	m_current_frame = 0;
	m_played = false;
	if (!m_frames.empty())
	{
		m_frames.clear();
	}
}

const IntRect& AnimatedSpriteEnemy::getFrame(int n) {
	return m_frames[n];
}

void AnimatedSpriteEnemy::addFrame(const IntRect& frame) {
	m_frames.push_back(frame);
}

const int AnimatedSpriteEnemy::getCurrentFrame() {
	return m_current_frame;
}

void AnimatedSpriteEnemy::setLooped(bool loop) {
	this->m_loop = loop;
}

const bool AnimatedSpriteEnemy::getLooped() {
	return this->m_loop;
}

void AnimatedSpriteEnemy::setPlayed(bool played) {
	this->m_played = played;
}

const bool AnimatedSpriteEnemy::getPlayed() {
	return this->m_played;
}

void AnimatedSpriteEnemy::update() {
	// If not looped only play once
	if (m_played == true && !m_loop)
	{
		m_current_frame = m_frames.size() - 1;
	}
	else {
		if (m_clock.getElapsedTime() > m_time) {
			if (m_frames.size() > m_current_frame + 1)
			{
				m_current_frame++;
			}
			else {
				m_current_frame = 0;
				m_played = true;
			}
			m_clock.restart();
		}
	}

}


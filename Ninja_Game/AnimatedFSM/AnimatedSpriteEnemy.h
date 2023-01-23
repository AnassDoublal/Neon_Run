#pragma once

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\System\Clock.hpp>
#include <vector>
#include <Debug.h>

using namespace std;
using namespace sf;

class AnimatedSpriteEnemy : public Sprite {
public:
	AnimatedSpriteEnemy();
	AnimatedSpriteEnemy(const Texture&);
	AnimatedSpriteEnemy(const Texture&, const IntRect&);
	~AnimatedSpriteEnemy();

	const Clock& getClock();
	const Time& getTime();
	const vector<IntRect>& getFrames();
	void clearFrames();
	const IntRect& getFrame(int);
	void addFrame(const IntRect&);
	const int getCurrentFrame();
	void setLooped(bool);
	const bool getLooped();
	void setPlayed(bool);
	const bool getPlayed();
	void setTime(Time);
	void update();

private:
	Clock m_clock;
	Time m_time;
	vector<IntRect> m_frames;
	unsigned int m_current_frame;
	bool m_loop;
	unsigned int m_play_count;
	unsigned int m_max_plays;
	bool m_played;
};

#ifndef GLIDE_PLAYER_STATE_H
#define GLIDE_PLAYER_STATE_H

#include <Player.h>
#include <PlayerState.h>

class GlidePlayerState : public PlayerState {
public:
	GlidePlayerState(std::vector<sf::Sprite>& t_tiles) : m_tiles(t_tiles) {};
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player&);
	virtual void enter(Player&);
	virtual void exit(Player&);
private:
	sf::Clock m_clock;
	std::vector<sf::Sprite>& m_tiles;
};

#endif
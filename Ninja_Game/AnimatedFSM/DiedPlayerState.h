#ifndef DIED_PLAYER_STATE_H
#define DIED_PLAYER_STATE_H

#include <Player.h>
#include <PlayerState.h>

class DiedPlayerState : public PlayerState {
public:
	DiedPlayerState(std::vector<sf::Sprite>& t_tiles) : m_tiles(t_tiles) {};
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player&);
	virtual void enter(Player&);
	virtual void exit(Player&);
private:
	std::vector<sf::Sprite>& m_tiles;
};

#endif
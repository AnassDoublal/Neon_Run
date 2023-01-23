#ifndef REVIVED_PLAYER_STATE_H
#define REVIVED_PLAYER_STATE_H

#include <Player.h>
#include <PlayerState.h>

class RevivedPlayerState : public PlayerState {
public:
	RevivedPlayerState(std::vector<sf::Sprite>& t_tiles) : m_tiles(t_tiles) {};
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player&);
	virtual void enter(Player&);
	virtual void exit(Player&);
private:
	sf::Clock m_clock;
	std::vector<sf::Sprite>& m_tiles;
};

#endif
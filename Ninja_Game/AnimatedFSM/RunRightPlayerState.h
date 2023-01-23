#ifndef RUN_RIGHT_PLAYER_STATE_H
#define RUN_RIGHT_PLAYER_STATE_H

#include <Player.h>
#include <PlayerState.h>

class RunRightPlayerState : public PlayerState {
public:
	RunRightPlayerState(std::vector<sf::Sprite>& t_tiles) : m_tiles(t_tiles) {};
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player&);
	virtual void enter(Player&);
	virtual void exit(Player&);
private:
	std::vector<sf::Sprite>& m_tiles;
};

#endif

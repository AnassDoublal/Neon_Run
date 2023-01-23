#ifndef JUMP_PLAYER_STATE_H
#define JUMP_PLAYER_STATE_H

#include <Player.h>
#include <PlayerState.h>

class JumpPlayerState : public PlayerState {
public:
	JumpPlayerState(std::vector<sf::Sprite>& t_tiles) : m_tiles(t_tiles) {};
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player&);
	virtual void enter(Player&);
	virtual void exit(Player&);
private:
	sf::Clock m_clock;
	std::vector<sf::Sprite>& m_tiles;
};

#endif
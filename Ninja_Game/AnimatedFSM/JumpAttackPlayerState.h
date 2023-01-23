#ifndef JUMP_ATTACK_PLAYER_STATE_H
#define JUMP_ATTACK_PLAYER_STATE_H

#include <Player.h>
#include <PlayerState.h>

class JumpAttackPlayerState : public PlayerState {
public:
	JumpAttackPlayerState(std::vector<sf::Sprite>& t_tiles) : m_tiles(t_tiles) {};
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player&);
	virtual void enter(Player&);
	virtual void exit(Player&);
private:
	std::vector<sf::Sprite>& m_tiles;
};

#endif
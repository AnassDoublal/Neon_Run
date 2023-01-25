#ifndef DIED_PLAYER_STATE_H
#define DIED_PLAYER_STATE_H

#include <Player.h>
#include <PlayerState.h>

class DiedPlayerState : public PlayerState {
public:
	DiedPlayerState(){};
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player&);
	virtual void enter(Player&);
	virtual void exit(Player&);
};

#endif
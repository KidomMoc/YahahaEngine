#ifndef KFTG_PLAYER_SYSTEM
#define KFTG_PLAYER_SYSTEM

#include "System.hpp"
#include "../Component/State.hpp"

namespace KFTG
{

class PlayerSystem : public System
{
public:
	PlayerSystem ();

	virtual void init (World *w) override;
	virtual void update (u16 deltaTime) override;

private:
	inline void setPlayerState (State *p, StateSet s);
};

}

#endif // KFTG_PLAYER_SYSTEM
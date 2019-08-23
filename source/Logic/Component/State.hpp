#ifndef KFTG_COMPONENT_STATE
#define KFTG_COMPONENT_STATE

#include "Component.hpp"
#include "../../Core/types.hpp"

namespace KFTG
{

enum class StateSet : u8
{
	NONE,
	PLAYER_STAND,
	PLAYER_WALK,
	PLAYER_JUMP_UP,
	PLAYER_JUMP_DOWN
};

static const u16 statePeriod[] = {
	1, 800, 500, 1000, 1
};

struct State : public Component
{
	StateSet state;
	u16 stateTime;

	State ();
	State (Entity e, StateSet s);

	State& operator = (const State &other);
};

State::State ()
	: State (Entity (0), StateSet::NONE)
{}


State::State (Entity e, StateSet s)
	: Component (ComponentType::STATE, e),
	state (s)
{}

State& State::operator = (const State &other)
{
	owner = other.owner;
	state = other.state;
	stateTime = other.stateTime;
	return *this;
}

}

#endif // KFTG_COMPONENT_STATE
#include "MovementSystem.hpp"
#include "../Component/Transform.hpp"
#include "../Component/Motion.hpp"
#include "../Component/State.hpp"

namespace KFTG
{

MovementSystem::MovementSystem ()
	: System (SystemType::MOVEMENT)
{
	mask.add ((u8) ComponentType::TRANSFORM);
	mask.add ((u8) ComponentType::MOTION);
}

void MovementSystem::update (u16 deltaTime)
{
	for (auto entity : _entities)
	{
		Transform *t;
		Motion *m;
		_world->getComponents (entity, &t, &m);
		t->lastCoordinate = t->coordinate;
		t->coordinate += m->velocity     * (deltaTime / 1000);
		if (t->coordinate.y < 0)
		{
			t->coordinate.y = 0;
			State *s;
			_world->getComponents<State> (entity, &s);
			if (s)
			{
				s->state = StateSet::PLAYER_STAND;
				s->stateTime = 0;
			}
		}
		m->velocity   += m->acceleration * (deltaTime / 1000);
	}
}

}
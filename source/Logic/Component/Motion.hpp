#ifndef KFTG_COMPONENT_MOTION
#define KFTG_COMPONENT_MOTION

#include "Component.hpp"
#include "../../Core/types.hpp"
#include "../../Core/Math.hpp"

namespace KFTG
{

struct Motion : public Component
{
	Vec2 velocity;
	Vec2 acceleration;

	Motion ();
	Motion (Entity e, Vec2 v, Vec2 a);

	Motion& operator = (const Motion &other);
};

Motion::Motion ()
	: Motion ({0}, {0.0f, 0.0f}, {0.0f, 0.0f})
{}

Motion::Motion (Entity e, Vec2 v, Vec2 a)
	: Component (ComponentType::MOTION, e),
	velocity (v), acceleration (a)
{}

Motion& Motion::operator = (const Motion &other)
{
	owner = other.owner;
	velocity = other.velocity;
	acceleration = other.acceleration;
	return *this;
}

}

#endif // KFTG_COMPONENT_MOTION
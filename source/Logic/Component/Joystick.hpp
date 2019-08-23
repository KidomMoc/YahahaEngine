#ifndef KFTG_COMPONENT_JOYSTICK
#define KFTG_COMPONENT_JOYSTICK

#include "Component.hpp"

namespace KFTG
{

struct Joystick : public Component
{
	Joystick ();
	Joystick (Entity e);

	Joystick& operator = (const Joystick &other);
};

Joystick::Joystick ()
	: Joystick (Entity (0))
{}

Joystick::Joystick (Entity e)
	: Component (ComponentType::JOYSTICK, e)
{}

Joystick& Joystick::operator = (const Joystick &other)
{
	owner = other.owner;
}

}

#endif // KFTG_COMPONENT_JOYSTICK
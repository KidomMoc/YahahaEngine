#ifndef KFTG_COMPONENT_ANIMATOR
#define KFTG_COMPONENT_ANIMATOR

#include "Component.hpp"
#include "State.hpp"
#include "../../Core/Asset/AssetTypes.hpp"

namespace KFTG
{

struct Animator : public Component
{
	Animation *ani;
	u16 playTime;
	StateSet state;

	Animator ();
	Animator (Entity e, Animation *a, StateSet s);

	Animator& operator = (const Animator &other);
};

Animator::Animator ()
	: Animator ({0}, nullptr, StateSet::NONE)
{}

Animator::Animator (Entity e, Animation *a, StateSet s)
	: Component (ComponentType::ANIMATOR, e),
	ani (a), state (s)
{}

Animator& Animator::operator = (const Animator &other)
{
	owner = other.owner;
	ani = other.ani;
	playTime = other.playTime;
	return *this;
}

}

#endif // KFTG_COMPONENT_ANIMATOR
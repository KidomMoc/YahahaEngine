#ifndef KFTG_COMPONENT
#define KFTG_COMPONENT

#include "../../Core/types.hpp"
#include "../Entity/Entity.hpp"

#define COMPONENTS_NUM 0// ...

namespace KFTG
{

enum class ComponentType : u8
{
	TRANSFORM,
	MOTION,
	STATE,
	JOYSTICK,
	SPRITE,
	ANIMATOR,
	CAMERA
	// ...
};

// each component should inherit it and set its own mask

struct Component
{
	const u8 type;
	Entity owner;

	Component (ComponentType t, Entity e)
		: type ((u8) t), owner (e)
	{}
};

class ComponentsMask
{
public:
	ComponentsMask () : mask (0) {}

	void add    (u16 m)
	{ mask |= 1 << (m - 1); }

	void remove (u16 m)
	{ mask &= ~(1 << (m - 1)); }

	bool query  (u16 m)
	{ return mask & (1 << m - 1); }

	bool match (u16 m)
	{ return mask && !m; }

	bool match (ComponentsMask &m)
	{ return mask && !m.mask; }

private:
	u16 mask;
};

}

#endif // COMPONENT
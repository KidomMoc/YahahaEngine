#ifndef KFTG_SYSTEM
#define KFTG_SYSTEM

#include "../../Core/array.hpp"
#include "../Entity/Entity.hpp"
#include "../Component/Component.hpp"
#include "../World/World.hpp"

namespace KFTG
{

class World;

enum class SystemType : u8
{
	PLAYER,
	MOVEMENT,
	ANIMATION,
	RENDER
	// ...
};

class System
{
public:
	// set mask
	System (SystemType t) : type (t) {}

	virtual void init (World *w) { _world = w; }
	virtual void update (u16 deltaTime) = 0;
	virtual void exit () {}
	
	void registerEntity   (Entity e);
	void unregisterEntity (Entity e);
	SystemType getType () { return type; }
	ComponentsMask getMask () { return mask; }

protected:
	const SystemType type;
	World *_world;
	ComponentsMask mask;
	array<Entity> _entities;
};

}

#endif // SYSTEM
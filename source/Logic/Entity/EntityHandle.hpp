#ifndef KFTG_ENTITY_HANDLE
#define KFTG_ENTITY_HANDLE

#include "../../Core/types.hpp"
#include "Entity.hpp"
#include "../World/World.hpp"

namespace KFTG
{

class World;

struct EntityHandle
{
	Entity entity;

	EntityHandle (Entity e, World *w)
		: entity (e), _world (w)
	{}

	EntityHandle (const EntityHandle &other)
		: entity (other.entity), _world (other._world)
	{}

	void destroy ();

	template <typename ComponentType>
	void addComponent (ComponentType &c);

	template <typename ComponentType>
	void removeComponent ();

	template <typename ComponentType>
	void getComponents (ComponentType **c);

	template <typename ComponentType, typename... Args>
	void getComponents (ComponentType **c, Args ** ... args);

private:
	World *_world;
};

}

#endif // ENTITY_HANDLE
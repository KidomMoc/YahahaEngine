#include "EntityHandle.hpp"

namespace KFTG
{

void EntityHandle::destroy ()
{
	_world->destroyEntity (entity);
}

template <typename ComponentType>
void EntityHandle::addComponent (ComponentType &c)
{
	_world->addComponent<ComponentType> (entity, c);
}

template <typename ComponentType>
void EntityHandle::removeComponent ()
{
	_world->removeComponent<ComponentType> (entity);
}


template <typename ComponentType>
void EntityHandle::getComponents (ComponentType **c)
{
	_world->getComponents (entity, c);
}

template <typename ComponentType, typename... Args>
void EntityHandle::getComponents (ComponentType **c, Args ** ... args)
{
	_world->getComponents (entity, c, args ...);
}

}
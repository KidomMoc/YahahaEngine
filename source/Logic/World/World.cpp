#include "World.hpp"
#include <new>
#include "../../Core/Memory/MemoryManager.hpp"
#include "../../Core/Asset/AssetManager.hpp"
#include "../System/PlayerSystem.hpp"
#include "../System/MovementSystem.hpp"
#include "../System/AnimationSystem.hpp"
#include "../System/RenderSystem.hpp"
#include "../Component/Animator.hpp"
#include "../Component/Camera.hpp"
#include "../Component/Joystick.hpp"
#include "../Component/Motion.hpp"
#include "../Component/Sprite.hpp"
#include "../Component/State.hpp"
#include "../Component/Transform.hpp"

namespace KFTG
{

void World::init (GUID *sceneName)
{
	MemoryManager *memMgr = MemoryManager::instance ();
	AssetManager *assetMgr = AssetManager::instance ();
	_entityManager = new (memMgr->allocScene (sizeof (EntityManager)))
		EntityManager ();

	initComponentMgrs ();
	typedef XML::Node::Attribute::Type AttrType;
	XML *scene = (XML*) assetMgr->queryAsset (*sceneName);
	initSystems ();
	initEntities (scene->root);

	EventManager::instance ()->registerEvent (Event::QuitScene, this);
	memMgr->freeAsset (sceneName);
}

void World::update (u16 deltaTime)
{
	for (auto sys : _systems)
		sys->update (deltaTime);
}

GUID* World::exit ()
{
	for (auto sys : _systems)
		sys->exit ();
	EventManager::instance ()->unregisterEvent (Event::QuitScene, this);
	MemoryManager::instance ()->freeScene ();
	return _nextScene;
}

EntityHandle World::createEntity ()
{
	Entity e = _entityManager->createEntity ();
	_entityMasks.add (e.id, ComponentsMask ());
	EntityHandle handle (e, this);
	return handle;
}

void World::destroyEntity (Entity e)
{
	for (auto sys : _systems)
		sys->unregisterEntity (e);
	for (auto mgr : _componentManagers)
		mgr->remove (e);
	_entityMasks.remove (e.id);
	_entityManager->destroyEntity (e);
}

template <typename ComponentType>
void World::addComponent (Entity e, ComponentType &c)
{
	u16 type = ComponentType ().type;
	dynamic_cast<ComponentManager<ComponentType>*> (_componentManagers[type])
		->add (e, c);
	ComponentsMask old = *_entityMasks.query (e.id);
	_entityMasks.query (e.id)->add (type);
	updateSystemCare (e, old);
}

template <typename ComponentType>
void World::removeComponent (Entity e)
{
	u16 type = ComponentType ().type;
	dynamic_cast<ComponentManager<ComponentType>*> (_componentManagers[type])
		->remove (e);
	ComponentsMask old = *_entityMasks.query (e.id);
	_entityMasks.query (e.id)->remove (type);
	updateSystemCare (e, old);
}

template <typename ComponentType>
void World::getComponents (Entity e, ComponentType **c)
{
	u16 type = ComponentType ().type;
	*c = dynamic_cast<ComponentManager<ComponentType>*> (_componentManagers[type])
		->query (e);
}

template <typename ComponentType, typename... Args>
void World::getComponents (Entity e, ComponentType **c, Args **... args)
{
	u16 type = ComponentType ().type;
	*c = dynamic_cast<ComponentManager<ComponentType>*> (_componentManagers[type])
		->query (e);

	getComponents (e, args ...);
}

template <typename ComponentType>
ComponentManager<ComponentType>* World::getComponentManager ()
{
	return dynamic_cast<ComponentManager<ComponentType>>
		(_componentManagers[ComponentType ().type]);
}

void World::initComponentMgrs ()
{
	MemoryManager *memMgr = MemoryManager::instance ();
	// init component managers
	_componentManagers[(u8) ComponentType::ANIMATOR] =
		new (MemoryManager::instance ()->allocScene (sizeof (ComponentManager<Animator>)))
		ComponentManager<Animator> (true);
	_componentManagers[(u8) ComponentType::CAMERA] =
		new (MemoryManager::instance ()->allocScene (sizeof (ComponentManager<Camera>)))
		ComponentManager<Camera> (true);
	_componentManagers[(u8) ComponentType::JOYSTICK] =
		new (MemoryManager::instance ()->allocScene (sizeof (ComponentManager<Joystick>)))
		ComponentManager<Joystick> (true);
	_componentManagers[(u8) ComponentType::MOTION] =
		new (MemoryManager::instance ()->allocScene (sizeof (ComponentManager<Motion>)))
		ComponentManager<Motion> (true);
	_componentManagers[(u8) ComponentType::SPRITE] =
		new (MemoryManager::instance ()->allocScene (sizeof (ComponentManager<Sprite>)))
		ComponentManager<Sprite> (true);
	_componentManagers[(u8) ComponentType::STATE] =
		new (MemoryManager::instance ()->allocScene (sizeof (ComponentManager<State>)))
		ComponentManager<State> (true);
	_componentManagers[(u8) ComponentType::TRANSFORM] =
		new (MemoryManager::instance ()->allocScene (sizeof (ComponentManager<Transform>)))
		ComponentManager<Transform> (true);
}

void World::initSystems ()
{
	// instantiate systems
	System *sys = new
		(MemoryManager::instance ()->allocScene (sizeof (PlayerSystem)))
		PlayerSystem ();
	_systems.append (sys);
	System *sys = new
		(MemoryManager::instance ()->allocScene (sizeof (MovementSystem)))
		MovementSystem ();
	_systems.append (sys);
	System *sys = new
		(MemoryManager::instance ()->allocScene (sizeof (AnimationSystem)))
		AnimationSystem ();
	_systems.append (sys); System *sys = new
		(MemoryManager::instance ()->allocScene (sizeof (RenderSystem)))
		RenderSystem ();
	_systems.append (sys);
	for (auto sys : _systems)
		sys->init (this);
}

void World::initEntities (XML::Node *root)
{
	typedef XML::Node::Attribute::Type AttrType;
	AssetManager *assetMgr = AssetManager::instance ();
	for (XML::Node *e = root->firstChild; e; e = e->nextSibling)
	{
		EntityHandle entity = createEntity ();
		for (XML::Node *c = e->firstChild; c; c = c->nextSibling)
		{
			XML::Node::Attribute *compType = e->findAttr ("ComponentType");
			if (compType->type != AttrType::NUMBER)
				continue; // TODO: error handling
			XML::Node::Attribute *attr;
			switch (compType->value.n)
			{
				case (u8) ComponentType::ANIMATOR:
				{
					Animator c;
					c.owner = entity.entity;
					attr = e->findAttr ("ani");
					c.ani = (Animation*) assetMgr->queryAsset (attr->value.s);
					attr = e->findAttr ("state");
					c.state = (StateSet) attr->value.n;
					entity.addComponent<Animator> (c);
					break;	
				}
				case (u8) ComponentType::CAMERA:
				{
					Camera c;
					c.owner = entity.entity;
					attr = e->findAttr ("width");
					c.width = attr->value.n;
					attr = e->findAttr ("range");
					c.range = attr->value.f;
					entity.addComponent<Camera> (c);
					break;	
				}
				case (u8) ComponentType::JOYSTICK:
				{
					Joystick c (entity.entity);
					entity.addComponent<Joystick> (c);
					break;	
				}
				case (u8) ComponentType::MOTION:
				{
					Motion c;
					c.owner = entity.entity;
					attr = e->findAttr ("velocity_x");
					c.velocity.x = attr->value.f;
					attr = e->findAttr ("velocity_y");
					c.velocity.y = attr->value.f;
					attr = e->findAttr ("acceleration_x");
					c.acceleration.x = attr->value.f;
					attr = e->findAttr ("acceleration_y");
					c.acceleration.y = attr->value.f;
					entity.addComponent<Motion> (c);
					break;	
				}
				case (u8) ComponentType::SPRITE:
				{
					Sprite c;
					c.owner = entity.entity;
					attr = e->findAttr ("img");
					c.img = (Image*) assetMgr->queryAsset (attr->value.s);
					entity.addComponent<Sprite> (c);
					break;	
				}
				case (u8) ComponentType::STATE:
				{
					State c;
					c.owner = entity.entity;
					attr = e->findAttr ("state");
					c.state = (StateSet) attr->value.n;
					entity.addComponent<State> (c);
					break;	
				}
				case (u8) ComponentType::TRANSFORM:
				{
					Transform c;
					c.owner = entity.entity;
					attr = e->findAttr ("coordinate_x");
					c.coordinate.x = attr->value.f;
					c.lastCoordinate.x = attr->value.f;
					attr = e->findAttr ("coordinate_y");
					c.coordinate.y = attr->value.f;
					c.lastCoordinate.y = attr->value.f;
					attr = e->findAttr ("scale_x");
					c.scale.x = attr->value.f;
					attr = e->findAttr ("scale_y");
					c.scale.y = attr->value.f;
					c.parent = nullptr;
					entity.addComponent<Transform> (c);
					break;	
				}
				default:
					// TODO: error handling
					break;
			}
		}
	}
}

void World::updateSystemCare (Entity e, ComponentsMask old)
{
	for (auto sys : _systems)
	{
		if (sys->getMask ().match (*_entityMasks.query (e.id)) &&
			!sys->getMask ().match (old))
			sys->registerEntity (e);
		if (sys->getMask ().match (old) &&
			!sys->getMask ().match (*_entityMasks.query (e.id)))
			sys->unregisterEntity (e);
	}
}

}
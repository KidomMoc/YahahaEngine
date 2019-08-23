#ifndef KFTG_WORLD
#define KFTG_WORLD

#include "../../Core/array.hpp"
#include "../../Core/Asset/AssetTypes.hpp"
#include "../Entity/Entity.hpp"
#include "../Entity/EntityHandle.hpp"
#include "../Entity/EntityManager.hpp"
#include "../Component/Component.hpp"
#include "../Component/ComponentHandle.hpp"
#include "../Component/ComponentManager.hpp"
#include "../System/System.hpp"

namespace KFTG
{

class EntityHandle;
class AbstractCM;
class System;

class World : public QuitSceneListener
{
public:
	World ()
		: _isQuit (false), _entityMasks (true), _systems ()
	{}
	~World () {}

	void init (GUID *sceneName);
	void update (u16 deltaTime);
	GUID* exit ();

	bool isQuit () { return _isQuit; }
	void setQuit () override { _isQuit = true; }

	EntityHandle createEntity ();
	void destroyEntity (Entity e);
	EntityManager* getEntityManager () { return _entityManager; }

	template <typename ComponentType>
	void addComponent (Entity e, ComponentType &c);

	template <typename ComponentType>
	void removeComponent (Entity e);

	template <typename ComponentType>
	void getComponents (Entity e, ComponentType **c);

	template <typename ComponentType, typename... Args>
	void getComponents (Entity e, ComponentType **c, Args ** ... args);

	template <typename ComponentType>
	ComponentManager<ComponentType>* getComponentManager ();

	void setNextScene (GUID *next) { _nextScene = next; }

protected:
	void initComponentMgrs ();
	void initSystems ();
	void initEntities (XML::Node *root);
	void updateSystemCare (Entity e, ComponentsMask old);

	bool _isQuit;
	GUID *_nextScene;
	EntityManager *_entityManager;
	map<ComponentsMask> _entityMasks;
	AbstractCM *_componentManagers[COMPONENTS_NUM];
	array<System*> _systems;
};

}

#endif // WORLD
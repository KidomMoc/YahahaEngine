#ifndef KFTG_COMPONENT_MANAGER
#define KFTG_COMPONENT_MANAGER

#include "../../Core/types.hpp"
#include "../../Core/map.hpp"
#include "../../Core/array.hpp"
#include "../../Core/Event/EventManager.hpp"
#include "../Entity/Entity.hpp"
#include "Component.hpp"

namespace KFTG
{

class AbstractCM
{
public:
	virtual void remove (Entity e) = 0;
};

template <typename ComponentType>
class ComponentManager : public AbstractCM
{
public:
	ComponentManager (bool s)
		: _componentsCount (0), _entityMap (true), _single (s)
	{}

	~ComponentManager ();

	void add (Entity e, ComponentType &c)
	{
		if (_single)
		{
			if (queryComponent (e)->owner == e)
				return;
			u16 index = _componentsCount++;
			_entityMap.add (e.id, index);
		}
		_components.append (c);
	}

	void remove (Entity e) override
	{
		if (_single)
		{
			--_componentsCount;
			u16 index = *_entityMap.query (e.id);
			_entityMap.remove (e.id);
			_components[index] = _components[_componentsCount];
			_components.shrink ();
		}
		else
			for (u16 i = 0; i < _componentsCount; ++i)
				if (_components[i].owner == e)
				{
					--_componentsCount;
					if (i < _componentsCount)
					{
						_components[i] = _components[_componentsCount];
						--i;
					}
					_components.shrink ();
				}
	}

	ComponentType* queryComponent (Entity e)
	{
		if (_single)
			return _components[*_entityMap.query (e.id)];
		return nullptr;
	}

	array<ComponentType>* getComponents () { return &_components; }

private:
	bool _single;
	u16 _componentsCount;
	array<ComponentType> _components;
	map<u16> _entityMap;
};

}

#endif // COMPONENT_MANAGER
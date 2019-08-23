#include "Logic.hpp"
#include <new>
#include "../Core/Memory/MemoryManager.hpp"
#include "../Core/Asset/AssetTypes.hpp"
#include "../Core/Asset/AssetManager.hpp"
#include "../Core/Time/Time.hpp"

namespace KFTG
{

Logic* Logic::instance ()
{
	static Logic _instance;
	return &_instance;
}

void Logic::init ()
{
	MemoryManager *memMgr = MemoryManager::instance ();
	AssetManager *assetMgr = AssetManager::instance ();
	GUID *startScene = (GUID*) assetMgr->queryAsset ("StartSceneName");
	_scene = new (memMgr->allocScene (sizeof (World))) World ();
	_scene->init (startScene);
}

void Logic::loop ()
{
	MemoryManager *memMgr = MemoryManager::instance ();
	_scene->update (Time::instance ()->getDeltaTimeMilli ());
	memMgr->freeFrame ();
	if (_scene->isQuit ())
	{
		// end this scene and get uid of next scene,
		GUID *nextScene = _scene->exit ();
		memMgr->freeScene ();
		if (!nextScene)
		{
			EventManager::instance ()->fireEvent (Event::QuitGame, nullptr);
			return;
		}
		::new (_scene) World ();
		_scene->init (nextScene);
	}
}

void Logic::exit ()
{
}

}
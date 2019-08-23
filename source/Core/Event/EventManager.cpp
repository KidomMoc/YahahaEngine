#include "EventManager.hpp"

namespace KFTG
{

void QuitGameListener::callback (void *param)
{
	setQuit ();
}

QuitSceneListener::QuitSceneListener ()
{
}

void QuitSceneListener::callback (void *param)
{
	setQuit ();
}

void KeyPressListener::callback (void *param)
{
	whenKeyPress (*((u32*) param));
}

void KeyReleaseListener::callback (void *param)
{
	whenKeyRelease (*((u32*) param));
}

// EventManager

EventManager* EventManager::instance ()
{
	static EventManager _instance;
	return &_instance;
}

void EventManager::init ()
{
	for (u32 i = 0; i < EVENT_TYPE_NUM; ++i)
		_listenerCount[i] = 0;
}

void EventManager::exit ()
{
}

void EventManager::registerEvent (enum Event eventType, EventListener *listener)
{
	for (u32 i = 0; i < _listenerCount[(u8) eventType]; ++i)
		if (_listeners[(u8) eventType][i] == listener)
			return;
	if (_listenerCount[(u8) eventType] < EVENT_NUM)
	{
		_listeners[(u8) eventType][_listenerCount[(u8) eventType]] = listener;
		++_listenerCount[(u8) eventType];
	}
}

void EventManager::unregisterEvent (enum Event eventType, EventListener *listener)
{
	for (u32 i = 0; i < _listenerCount[(u8) eventType]; ++i)
		if (_listeners[(u8) eventType][i] == listener)
		{
			_listeners[(u8) eventType][i] =
				_listeners[(u8) eventType][_listenerCount[(u8) eventType - 1]];
			--_listenerCount[(u8) eventType];
			return;
		}
}

void EventManager::fireEvent (enum Event eventType, void *param)
{
	for (u32 i = 0; i < _listenerCount[(u8) eventType]; ++i)
		_listeners[(u8) eventType][i]->callback (param);
}

}
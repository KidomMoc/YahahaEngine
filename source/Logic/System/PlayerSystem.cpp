#include "PlayerSystem.hpp"
#include "../Component/Transform.hpp"
#include "../Component/Motion.hpp"
#include "../Component/Joystick.hpp"
#include "../Component/Collider.hpp"
#include "../Component/Animator.hpp"
#include "../../Core/Asset/AssetManager.hpp"
#include "../../Core/Asset/AssetTypes.hpp"
#include "../../Core/Event/InputManager.hpp"

namespace KFTG
{

PlayerSystem::PlayerSystem ()
	: System (SystemType::PLAYER)
{
	mask.add ((u8) ComponentType::TRANSFORM);
	mask.add ((u8) ComponentType::MOTION);
	mask.add ((u8) ComponentType::STATE);
	mask.add ((u8) ComponentType::JOYSTICK);
	mask.add ((u8) ComponentType::COLLIDER);
	mask.add ((u8) ComponentType::ANIMATOR);
}

void PlayerSystem::init (World *w)
{
	_world = w;
	EntityHandle ph = _world->createEntity ();
	State p (ph.entity, StateSet::PLAYER_STAND);
	ph.addComponent<State> (p);
	Transform t (ph.entity, {0.0f, 0.0f}, {1.0f, 1.0f}, nullptr);
	ph.addComponent<Transform> (t);
	Motion m (ph.entity, {0.0f, 0.0f}, {0.0f, 0.0f});
	ph.addComponent<Motion> (m);
	Joystick j (ph.entity);
	ph.addComponent<Joystick> (j);
	Collider c (ph.entity, ColliderType::PLAYER,
		{-0.5f, -0.75f}, {0.5f, -0.75f});
	ph.addComponent<Collider> (c);
	Animation *ani = (Animation*) AssetManager::instance()
		->queryAsset ("Ani" + (u8) p.state);
	if (!ani)
		; // TODO: error handling
	Animator a (ph.entity, ani, StateSet::PLAYER_STAND);
	ph.addComponent<Animator> (a);
}

void PlayerSystem::update (u16 deltaTime)
{
	State *s;
	Motion *m;
	Transform *t;
	_world->getComponents (_entities[0], &s, &m, &t);

	s->stateTime += deltaTime;

	// A: move left; D: move right; J: jump
	InputManager *inputMgr = InputManager::instance ();
	if (inputMgr->queryKeyRelease ('A')
		|| inputMgr->queryKeyRelease ('D'))
	{
		if (s->state == StateSet::PLAYER_WALK)
			setPlayerState (s, StateSet::PLAYER_STAND);
		m->velocity.x = 0.0f;
	}
	if (inputMgr->queryKeyPress ('A'))
	{
		if (s->state == StateSet::PLAYER_STAND)
			setPlayerState (s, StateSet::PLAYER_WALK);
		if (t->scale.x > 0)
			t->scale.x = -t->scale.x;
		m->velocity.x = -5.0f;
	}
	if (inputMgr->queryKeyPress ('D'))
	{
		if (s->state == StateSet::PLAYER_STAND)
			setPlayerState (s, StateSet::PLAYER_WALK);
		if (t->scale.x < 0)
			t->scale.x = -t->scale.x;
		m->velocity.x = 5.0f;
	}
	if (inputMgr->queryKeyPress ('J')
		&& (s->state == StateSet::PLAYER_STAND
		||  s->state == StateSet::PLAYER_WALK))
	{
		setPlayerState (s, StateSet::PLAYER_JUMP_UP);
		m->velocity.y = 3.0f;
	}
	if (s->state == StateSet::PLAYER_JUMP_UP
		&& s->stateTime >= statePeriod[(u8) s->state])
	{
		setPlayerState (s, StateSet::PLAYER_JUMP_DOWN);
		m->velocity.y = -3.0f;
	}
	s->stateTime %= statePeriod[(u8) s->state];
}

void PlayerSystem::setPlayerState (State *p, StateSet s)
{
	p->state = s;
	p->stateTime = 0;
}

}
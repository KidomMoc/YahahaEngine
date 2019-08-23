#include "AnimationSystem.hpp"
#include "../Component/Animator.hpp"
#include "../Component/State.hpp"
#include "../../Core/Asset/AssetManager.hpp"

namespace KFTG
{

void AnimationSystem::update (u16 deltaTime)
{
	for (auto entity : _entities)
	{
		Animator *ani;
		State *state;
		_world->getComponents (entity, &ani, &state);
		u16 totalTime = 0;
		for (int i = 0; i < ani->ani->len; ++i)
			totalTime += ani->ani->ani[i].time;
		ani->playTime = (ani->playTime + deltaTime) % totalTime;
		if (ani->state != StateSet::NONE
			&& state->state != ani->state)
		{
			ani->state = state->state;
			ani->playTime = 0;
			ani->ani = (Animation*) AssetManager::instance ()
				->queryAsset ("Animation" + (u8) ani->state);
		}
	}
}

}
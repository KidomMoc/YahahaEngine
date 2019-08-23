#include "RenderSystem.hpp"
#include "../Component/Camera.hpp"
#include "../Component/Transform.hpp"
#include "../Component/Sprite.hpp"
#include "../Component/Animator.hpp"
#include "../../Core/Asset/AssetTypes.hpp"
#include "../../Core/Display/DisplayManager.hpp"

namespace KFTG
{

RenderSystem::RenderSystem ()
	: System (SystemType::RENDER)
{
	mask.add ((u8) ComponentType::CAMERA);
	mask.add ((u8) ComponentType::TRANSFORM);
}

void RenderSystem::update (u16 deltaTime)
{
	DisplayManager *dispMgr = DisplayManager::instance ();
	for (auto entity : _entities)
	{
		Camera *c;
		Transform *t;
		_world->getComponents (entity, &c, &t);
		array<Entity> &arr = *_world->getEntityManager ()->getEntities ();
		for (auto e : arr)
		{
			Animator *ani;
			Sprite *sprite;
			Transform *trans;
			_world->getComponents (e, &ani, &sprite, &trans);
			if (!ani && !sprite)
				continue;
			if (!trans)
				continue;
			Image *img;
			if (ani)
			{
				u16 ind = ani->ani->len;
				u16 countTime = 0;
				for (u16 i = 0; i < ani->ani->len; countTime += ani->ani->ani[i].time, ++i)
					if (ani->playTime < countTime)
					{
						ind = i - 1;
						break;
					}
				if (ind == ani->ani->len)
					--ind;
				img = ani->ani->ani[ind].img;
			}
			else if (sprite)
				img = sprite->img;

			u32 winw = dispMgr->getWindowWidth ();
			i32 x = (trans->coordinate.x - t->coordinate.x) / c->range * winw;
			i32 y = (trans->coordinate.y - t->coordinate.y) / c->range * winw;
			dispMgr->drawImg (img, x, y, t->scale);
		}
	}
}

}
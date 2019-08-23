#ifndef KFTG_ANIMATION_SYSTEM
#define KFTG_ANIMATION_SYSTEM

#include "System.hpp"

namespace KFTG
{

class AnimationSystem : public System
{
public:
	AnimationSystem ();

	virtual void update (u16 deltaTime) override;
};

}

#endif KFTG_ANIMATION_SYSTEM
#ifndef KFTG_MOVEMENT_SYSTEM
#define KFTG_MOVEMENT_SYSTEM

#include "System.hpp"

namespace KFTG
{

class MovementSystem : public System
{
public:
	MovementSystem ();

	virtual void update (u16 deltaTime) override;
};

}

#endif // KFTG_MOVEMENT_SYSTEM
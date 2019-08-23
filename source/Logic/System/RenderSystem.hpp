#ifndef KFTG_RENDER_SYSTEM
#define KFTG_RENDER_SYSTEM

#include "System.hpp"

namespace KFTG
{

class RenderSystem : public System
{
public:
	RenderSystem ();

	virtual void update (u16 deltaTime) override;
};

}

#endif // KFTG_RENDER_SYSTEM
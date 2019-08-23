#ifndef KFTG_COMPONENT_SPRITE
#define KFTG_COMPONENT_SPRITE

#include "Component.hpp"
#include "../../Core/types.hpp"
#include "../../Core/Asset/AssetTypes.hpp"

namespace KFTG
{

struct Sprite : public Component
{
	Image *img;

	Sprite ();
	Sprite (Entity e, Image *i);
	Sprite& operator = (const Sprite &other);
};

Sprite::Sprite ()
	: Sprite ({0}, nullptr)
{}

Sprite::Sprite (Entity e, Image *i)
	: Component (ComponentType::SPRITE, e),
	img (i)
{}

Sprite& Sprite::operator = (const Sprite &other)
{
	owner = other.owner;
	img = other.img;
	return *this;
}

}

#endif // KFTG_COMPONENT_SPRITE
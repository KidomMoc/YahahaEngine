#ifndef KFTG_COMPONENT_TRANSFORM
#define KFTG_COMPONENT_TRANSFORM

#include "Component.hpp"
#include "../../Core/types.hpp"
#include "../../Core/Math.hpp"

namespace KFTG
{

struct Transform : public Component
{
	Vec2 coordinate;
	Vec2 lastCoordinate;
	Vec2 scale;
	Transform *parent;

	Transform ();
	Transform (Entity e, Vec2 c, Vec2 s, Transform *p);

	Transform& operator = (const Transform &other);
};

Transform::Transform ()
	: Transform ({0}, {0.0f, 0.0f}, {1.0f, 1.0f}, nullptr)
{}

Transform::Transform (Entity e, Vec2 c, Vec2 s, Transform *p)
	: Component (ComponentType::TRANSFORM, e),
	coordinate (c), lastCoordinate (c), scale (s), parent (p)
{}

Transform& Transform::operator = (const Transform &other)
{
	owner = other.owner;
	coordinate = other.coordinate;
	scale = other.scale;
	parent = other.parent;
	return *this;
}

}

#endif // KFTG_COMPONENT_TRANSFORM
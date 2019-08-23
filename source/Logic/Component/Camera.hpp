#ifndef KFTG_COMPONENT_CAMERA
#define KFTG_COMPONENT_CAMERA

#include "Component.hpp"
#include "../../Core/types.hpp"
#include "../../Core/Math.hpp"

namespace KFTG
{

struct Camera : public Component
{
	u32 width;
	f32 range; // horizontal

	Camera ();
	Camera (Entity e, u32 w, f32 r);

	Camera& operator = (const Camera &other);
};

Camera::Camera ()
	: Camera ({0}, 0, 0.0f)
{}

Camera::Camera (Entity e, u32 w, f32 r)
	: Component (ComponentType::CAMERA, e),
	width (w), range (r)
{}

Camera& Camera::operator = (const Camera &other)
{
	owner = other.owner;
	width = other.width;
	range = other.range;
	return *this;
}

}

#endif // KFTG_COMPONENT_CAMERA
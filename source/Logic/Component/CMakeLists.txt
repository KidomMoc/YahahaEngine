set(HEADERS
	Animator.hpp
	Camera.hpp
	Component.hpp
	ComponentHandle.hpp
	ComponentManager.hpp
	Joystick.hpp
	Motion.hpp
	Sprite.hpp
	State.hpp
	Transform.hpp
)

set(SOURCES
	ComponentHandle.cpp
	ComponentManager.cpp
	Components.cpp
)

add_library(Component
	${HEADERS}
	${SOURCES}
)

target_link_libraries(Component
	Logic
)
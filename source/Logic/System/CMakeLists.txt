set(HEADERS
	AnimationSystem.hpp
	MovementSystem.hpp
	PlayerSystem.hpp
	RenderSystem.hpp
	System.hpp
)

set(SOURCES
	AnimationSystem.cpp
	MovementSystem.cpp
	PlayerSystem.cpp
	RenderSystem.cpp
	System.cpp
)

add_library(System
	${HEADERS}
	${SOURCES}
)

target_link_libraries(System
	Logic
)
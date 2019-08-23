project(Logic)

set(HEADERS
	generator.hpp
	Logic.hpp
)

set(SOURCES
	generator.cpp
	Logic.cpp
)

add_library(Logic
	${HEADERS}
	${SOURCES}
)

add_subdirectory(Component)
add_subdirectory(Entity)
add_subdirectory(System)
add_subdirectory(World)

target_link_libraries(Logic
	Component
	Core
	Entity
	System
	World
)
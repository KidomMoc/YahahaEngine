add_executable(${GAME_NAME} main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(LIBS)

find_library(glew_LIB glew32.dll ${CMAKE_SOURCE_DIR}/lib)
if(glew_LIB)
	set(LIBS ${LIBS} ${glew_LIB})
else()
	message("not found glew")
endif(glew_LIB)

find_library(glfw_LIB glfw3.dll ${CMAKE_SOURCE_DIR}/lib)
if(glfw_LIB)
	set(LIBS ${LIBS} ${glfw_LIB})
else()
	message("not found glfw")
endif(glfw_LIB)

find_library(zlib_LIB libzlib.dll ${CMAKE_SOURCE_DIR}/lib)
if(zlib_LIB)
	set(LIBS ${LIBS} ${zlib_LIB})
else()
	message("not found zlib")
endif(zlib_LIB)

find_library(libpng_LIB libpng16.dll ${CMAKE_SOURCE_DIR}/lib)
if(libpng_LIB)
	set(LIBS ${LIBS} ${libpng_LIB})
else()
	message("not found libpng")
endif(libpng_LIB)

target_link_libraries(${GAME_NAME} ${LIBS})
file(COPY ${LIBS} DESTINATION ${EXECUTABLE_OUTPUT_PATH})

add_subdirectory(Core)
add_subdirectory(Logic)

target_link_libraries(${GAME_NAME}
	Core
	Logic
)
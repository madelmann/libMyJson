INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
        main.cpp
)

SET(HEADERS
)

SET(DEPENDENCIES
	Json
)

SET(MODULES
)

add_include(Json)

SET(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/MyJsonTestApp)
build_app(MyJsonTestApp "${MODULES}")

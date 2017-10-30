# directories
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)   # binary root
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)      # library root

SET(CMAKE_CXX_FLAGS "-pedantic -fPIC -Wall -Werror -Wunused -Wno-long-long -Wnon-virtual-dtor -std=c++14")

if( "${BUILD}" STREQUAL "" OR "${BUILD}" MATCHES "Debug")

    # by default we build debug!
    MESSAGE("Setting build to: Debug")

    SET(CMAKE_BUILD_TYPE "Debug")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")

    # do more logging
    add_definitions(-DDEBUG)

    # suppress "veraltete Konvertierung von Zeichenkettenkonstante in »char*« [-Werror=write-strings]"
    add_definitions(-Wno-write-strings)

elseif("${BUILD}" MATCHES "Release")

    MESSAGE("Setting build to: Release")

    SET(CMAKE_BUILD_TYPE "Release")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing -O3")

    # suppress "veraltete Konvertierung von Zeichenkettenkonstante in »char*« [-Werror=write-strings]"
    add_definitions(-Wno-write-strings)

else()

    MESSAGE(FATAL_ERROR "Specify a valid build type: cmake -DBUILD=Release|Debug")

endif()

# common used functionality and functions
INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Common.cmake)

# now run the build that takes care of other arguments
INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Builder.cmake)


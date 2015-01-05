cmake_minimum_required(VERSION 2.6)

# cmake policy changes. use "cmake --help-policy <policyid>" for details
cmake_policy(SET CMP0000 OLD)
if ( CMAKE_VERSION VERSION_LESS "2.6.4" )
else()
	cmake_policy(SET CMP0011 NEW)
endif()

# verbose makefiles
# SET(CMAKE_VERBOSE_MAKEFILE ON)

# directories
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)   # binary root
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)      # library root

#SET(CMAKE_CXX_FLAGS "-ansi -pedantic -fPIC -Wall -Werror -Wunused -Wno-long-long -Wnon-virtual-dtor") # -std=c++0x ;-(
SET(CMAKE_CXX_FLAGS "-pedantic -fPIC -Wall -Werror -Wunused -Wno-long-long -Wnon-virtual-dtor") # -std=c++0x ;-(

if( "${JSON_BUILD}" STREQUAL "" OR "${JSON_BUILD}" MATCHES "Debug")

    # by default we build debug!
    # MESSAGE("Setting default build to: Debug")
    SET(CMAKE_BUILD_TYPE "Debug")

    # do more logging
    add_definitions(-DJSON_DEBUG)

    # suppress "veraltete Konvertierung von Zeichenkettenkonstante in »char*« [-Werror=write-strings]"
    add_definitions(-Wno-write-strings)

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")

elseif("${JSON_BUILD}" MATCHES "Release")

    # MESSAGE("Setting default build to: Release")
    SET(CMAKE_BUILD_TYPE "Release")
    SET(CMAKE_CXX_FLAGS "")

    # do less logging
    add_definitions(-DJSON_NO_DEBUG_LOG)

    # suppress "veraltete Konvertierung von Zeichenkettenkonstante in »char*« [-Werror=write-strings]"
    add_definitions(-Wno-write-strings)

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing")

else()

    MESSAGE(FATAL_ERROR "Specify a valid build type: cmake -DJSON_BUILD=Release|Debug")

endif()

# common used functionality and functions
INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Common.cmake)

# now run the build that takes care of other arguments
INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Builder.cmake)

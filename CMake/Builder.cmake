
function(build_static_lib target modules)

        _handle_modules_pre_linker("${modules}")

        add_library(${target} ${SOURCES} ${HEADERS})

        LIST(LENGTH DEPENDENCIES num_dependencies)
        if ( num_dependencies GREATER 0 )
            target_link_libraries(${target} ${DEPENDENCIES})
        endif()

        _handle_modules_post_linker("${modules}" ${target})

endfunction()

function(build_app target modules)

        _handle_modules_pre_linker("${modules}")

        SET(CMAKE_CXX_FLAGS "-Wl,--as-needed")

        add_executable(${target} ${SOURCES} ${HEADERS})

        # link against specified libs
        target_link_libraries(${target} ${DEPENDENCIES})

        _handle_modules_post_linker("${modules}" ${target})

endfunction()

function(_handle_modules_pre_linker modules)

endfunction()

function(_handle_modules_post_linker modules target)

endfunction()

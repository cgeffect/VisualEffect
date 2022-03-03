cmake_minimum_required(VERSION 3.1)

project(PAG)

# Uncomment the next 4 lines to build libpag for Intel cpus on Apple Silicon devices.
#if (APPLE AND NOT IOS)
#    SET(CMAKE_SYSTEM_PROCESSOR x86_64)
#    SET(CMAKE_OSX_ARCHITECTURES x86_64)
#endif ()

add_compile_options(-fPIC)
add_compile_options(-Wall)
#set(CMAKE_VERBOSE_MAKEFILE ON)

set(IPHONE_VERSION_MIN 11.4)
# Options for building libpag
option(PAG_BUILD_SHARED "Build shared library" ON)
option(PAG_USE_OPENGL "allow use of OpenGL as GPU backend" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
cmake_policy(SET CMP0063 NEW)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)


# collects pag include directories.
set(PAG_INCLUDES 
        src/vgx/core/
        src/vgx/input/
        src/vgx/output/
        src/vgx/public/*.h
        src/vgx/shader/
        src/vgx/utils/)

# collects pag source files.
file(GLOB_RECURSE PAG_FILES
        src/vgx/core/*.*
        src/vgx/input/*.*
        src/vgx/output/*.*
        src/vgx/public/*.*
        src/vgx/shader/*.*
        src/vgx/utils/*.*)
        

if (PAG_USE_OPENGL)

    find_library(OpenGL_LIBS OpenGL REQUIRED)
    list(APPEND PAG_PLATFORM_STATIC_LIBS ${OpenGL_LIBS})
    add_definitions(-DGL_SILENCE_DEPRECATION)

endif ()

if (PAG_BUILD_SHARED)
    add_library(pag SHARED ${PAG_VENDOR_TARGET} ${PAG_FILES})
    target_compile_definitions(pag PUBLIC PAG_DLL)
    target_include_directories(pag PUBLIC ${PAG_INCLUDES} )
    target_link_libraries(pag ${PAG_PLATFORM_STATIC_LIBS})
else ()
    add_library(pag STATIC ${PAG_VENDOR_TARGET} ${PAG_FILES} ${PAG_PLATFORM_FILES} ${TGFX_PLATFORM_FILES})
    merge_libraries_into(pag ${PAG_PLATFORM_STATIC_LIBS})
    target_include_directories(pag PUBLIC ${PAG_INCLUDES} ${PAG_PLATFORM_INCLUDES})
    target_link_libraries(pag)
endif ()


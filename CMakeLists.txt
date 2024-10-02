# Example for using cURL, SDL libs on Windows:
# 1) Install + Open MSYS2
# 2) pacman -Syu
# 3) pacman -Sy mingw-w64-x86_64-curl
# 4) pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_image mingw-w64-x86_64-SDL2_mixer mingw-w64-x86_64-SDL2_ttf mingw-w64-x86_64-SDL2_net
# -lcurl, -lSDL2/-lSDL2_image/etc should now work.

cmake_minimum_required(VERSION 3.5)

### PROJECT SETTINGS ###
# Project name
set(PROJ_OUT "Example-Project")
# Set executable target settings depending on OS...
if(WIN32)
    set(PROJ_OUT "${PROJ_OUT}-win-x86_64")
    # Show console (FALSE=show, TRUE=don't show)
    set(CMAKE_WIN32_EXECUTABLE FALSE)
endif(WIN32)
if(UNIX)
    EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )
    set(PROJ_OUT "${PROJ_OUT}-unix-${ARCHITECTURE}")
endif(UNIX)
# Project version and flags
project(${PROJ_OUT} VERSION 0.1.1.0 LANGUAGES C CXX)
set(CMAKE_C_FLAGS "-std=c++11 -o")

### SETUP DEPENDENCIES ###
# Get list of sources and headers (.cpp, .h)
file (GLOB_RECURSE PROJ_SOURCES CONFIGURE_DEPENDS FOLLOW_SYMLINKS "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/include/*.cpp")
file (GLOB_RECURSE PROJ_HEADERS CONFIGURE_DEPENDS FOLLOW_SYMLINKS "${CMAKE_SOURCE_DIR}/src/*.h" "${CMAKE_SOURCE_DIR}/include/*.h")
# Build list of includes
set (PROJ_SRC_DIRS "")
foreach (_headerFile ${PROJ_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND PROJ_SRC_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES PROJ_SRC_DIRS)
# Add executable
add_executable(${PROJ_OUT} ${PROJ_SOURCES})
set_target_properties(${PROJ_OUT} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

### INCLUDE DEPENDENCIES ###
# Linking
target_link_libraries(${PROJ_OUT} PRIVATE "-lcurl -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net")
# Add include directories (everywhere there is a header file: libraries and BTE src dirs)
target_include_directories(${PROJ_OUT} PRIVATE ${PROJ_SRC_DIRS})
target_include_directories(${PROJ_OUT} PRIVATE "include")

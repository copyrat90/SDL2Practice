cmake_minimum_required(VERSION 3.11)
project(SDL2Template)

# Set C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set default build type to debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Set dependency locations if it's on Windows
if(WIN32)
    set(CMAKE_PREFIX_PATH
        "D:/Library/SDL2/i686-w64-mingw32/lib/cmake/SDL2;"
    )
    set(LUA_INCLUDE_DIR "D:/Library/Lua5.4/include")
    set(LUA_LIBDIR "D:/Library/Lua5.4")
    set(LUA_LIBRARIES "lua54")
endif()

# Find dependencies
find_package(SDL2 REQUIRED)
if(NOT WIN32)
    find_package(Lua5.4 REQUIRED)
endif()

# Find all *.cpp files on ./src directory
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

# Compile & Link
add_executable(game ${SRC_FILES})

target_include_directories(game
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${SDL2_INCLUDE_DIRS}
    ${LUA_INCLUDE_DIR}
)
target_link_directories(game
PRIVATE
    ${SDL2_LIBDIR}
    ${LUA_LIBDIR}
)
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set(SDL2_LIBRARIES mingw32 SDL2main SDL2)
endif()
target_link_libraries(game
    ${SDL2_LIBRARIES}
    SDL2_image SDL2_ttf SDL2_mixer
    ${LUA_LIBRARIES}
)

# Copy ./asset directory to Build Directory
file(COPY
    ${CMAKE_CURRENT_SOURCE_DIR}/asset
DESTINATION
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Copy Windows dependency DLL files to Build Directory
if(WIN32)
    file(
    COPY
        D:/Library/Lua5.4/lua54.dll
    DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}
    )
    file(GLOB SDL2_DLLS
        D:/Library/SDL2/i686-w64-mingw32/bin/*.dll
    )
    file(
    COPY
        ${SDL2_DLLS}
    DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}
    )
    file(GLOB MINGW32_DLLS
        D:/Library/MinGW/mingw32/i686-w64-mingw32/lib/*.dll
    )
    file(
    COPY
        ${MINGW32_DLLS}
    DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}
    )
endif()

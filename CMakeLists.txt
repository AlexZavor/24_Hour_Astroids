cmake_minimum_required(VERSION 3.12)

project(Astroids  VERSION 1.0.0
        DESCRIPTION "Astroids made with SDL2 in under 24 hours!"
        LANGUAGES CXX)

link_directories(lib)
set(SDL2_DIR "lib/cmake/SDL2")
include_directories(include)
include_directories(include/headers)
include_directories(include/SDL2)

set(DEBUG true)

############### Main Build ###############

file(GLOB ASTROIDS_SRC CONFIGURE_DEPENDS "src/*.cpp")

add_executable(Astroids ${ASTROIDS_SRC})

find_package(SDL2 REQUIRED)

target_link_libraries(Astroids mingw32)
target_link_libraries(Astroids SDL2main)
target_link_libraries(Astroids SDL2_ttf)
target_link_libraries(Astroids SDL2)

if(DEBUG)
    set(CMAKE_CXX_FLAGS "-Wall -DDEBUG")
else()
    set(CMAKE_CXX_FLAGS "-Wl,-subsystem,windows -O3")  
endif()

add_custom_target(run 
    COMMAND .\\Astroids.exe
)
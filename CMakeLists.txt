cmake_minimum_required(VERSION 3.27)
project(falling_sands)
find_package(SDL2 CONFIG REQUIRED)


set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp
        UI/UIRenderer.cpp
        UI/UIRenderer.h
        logic/Matrix.cpp
        logic/Matrix.h
        UI/UIElement.cpp
        UI/UIElement.h
        logic/Sand.hpp
        util/Coordinate.cpp
        util/Coordinate.h
        util/Random.hpp
        Application.cpp
        Application.h
        UI/ColorGradient.hpp)
add_executable(falling_sands ${SOURCE_FILES})
message(SDL2)
target_link_libraries(falling_sands
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
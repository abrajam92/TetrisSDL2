cmake_minimum_required(VERSION 4.2)
project(SDL_Project2 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_library(SDL2_FRAMEWORK
    NAMES SDL2
    PATHS /Library/Frameworks
    NO_DEFAULT_PATH
    REQUIRED
)

set(SOURCE_FILES 

        main.cpp
        Game.cpp
        Game.h

        Tetris_Board.cpp
        Tetris_Board.h

        Tetris_Rect.h 
        Tetris_Shape.cpp 
        Tetris_Shape.h 
        Tetris_Board.cpp 
        Tetris_Board.h

        "SDL Classes/Color.h"
        "SDL Classes/Rect.cpp"
        "SDL Classes/Rect.h"
        "SDL Classes/Window.cpp" 
        "SDL Classes/Window.h" 
        "SDL Classes/Drawrout.cpp" 
        "SDL Classes/Drawrout.h"

        SDL2_Gfx/SDL2_framerate.c
        SDL2_Gfx/SDL2_framerate.h
        SDL2_Gfx/SDL2_gfxPrimitives.h
        SDL2_Gfx/SDL2_gfxPrimitives.c
        SDL2_Gfx/SDL2_gfxPrimitives_font.h
        SDL2_Gfx/SDL2_imageFilter.h
        SDL2_Gfx/SDL2_imageFilter.c
        SDL2_Gfx/SDL2_rotozoom.h
        SDL2_Gfx/SDL2_rotozoom.c 
        )

add_executable(SDL_Project2 ${SOURCE_FILES})

target_compile_definitions(SDL_Project2
    PRIVATE
        SDL_DISABLE_IMMINTRIN_H
)

target_include_directories(SDL_Project2
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/SDL2_Gfx"
        "${CMAKE_CURRENT_SOURCE_DIR}/SDL Classes"
        "${SDL2_FRAMEWORK}/Headers"
)

target_link_libraries(SDL_Project2
    PRIVATE 
        "${SDL2_FRAMEWORK}"
)

target_compile_definitions(SDL_Project2
    PRIVATE
        SDL_DISABLE_IMMINTRIN_H
)

target_compile_options(SDL_Project2
    PRIVATE
        -F/Library/Frameworks
)

target_link_options(SDL_Project2
    PRIVATE
        "-Wl,-rpath,/Library/Frameworks"
)
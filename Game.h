#ifndef _GAME_HH
#define _GAME_HH

#define DEBUGGING
//#undef DEBUGGING

#ifdef __ANDROID__
#include <SDL.h>
#include "Window.h"
#endif

#ifndef __ANDROID__
#include <SDL.h>
#include "SDL Classes/Window.h"
#endif

#include "Tetris_Board.h"

/* *********** CLASE TIMER ************ */

class Timer {

    Uint32 startTime, stopTime;

    Timer() : startTime(0), stopTime(0){}

public:

    void start(){

        startTime = SDL_GetTicks();
    }

    Uint32 getActualTime(){ return SDL_GetTicks() - startTime;}

};

/* *********** CLASE GAME ************ */

class Game{

    sdl::Window window;
    SDL_Event event;
    std::unique_ptr<TetrisBoard> board;
    std::unique_ptr<Touch_Keys> keys;

public:

    Game();
    int ejecucion();

private:

    bool inicializar();
    direction captura_Eventos();
    direction procesa_Eventos();
    void loop_Juego();
    int finalizar();
};


#endif //_GAME_H
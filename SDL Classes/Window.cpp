//
// Created by Abraham Cruz Santibañez on 24/07/17.
//

#include "Window.h"
#include <cmath>

sdl::Window::Window(const char *titulo, int x, int y, int w, int h, Uint32 wFlags, Uint32 rFlags) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER ) != 0){

        //SDL_Log("\nError en SDL_Init:");
        //SDL_Log(" %s\n", SDL_GetError());
        SDL_ClearError();
    }

    SDL_Rect rct;

    if (SDL_GetDisplayBounds(0, &rct) != 0){

        //SDL_Log("\nError en SDL_GetDisplayBounds:");
        //SDL_Log(" %s\n", SDL_GetError());
        SDL_ClearError();
    }
    else
        wind = SDL_CreateWindow(titulo, x, y, rct.w, rct.h, wFlags);

    if (wind == nullptr){

        //SDL_Log("\nError en SDL_CreateWindow:");
        //SDL_Log(" %s\n", SDL_GetError());
        SDL_ClearError();
    }

    rend = SDL_CreateRenderer(wind, -1, rFlags);

    if (rend == nullptr){

        ////SDL_Log("\nError en SDL_CreateRenderer:");
        ////SDL_Log(" %s\n", SDL_GetError());
        SDL_ClearError();
    }
}

/**
 * \note Función para Android.
 *
 * \brief
 * Transforma el valor relativo de "x" e "y" en valor
 * de pixeles multiplicandolos por w y h
 * obtenidos con SDL_GetDisplayBounds.
 * @param x val relativo x
 * @param y val relativo y
 */
void sdl::Window::get_AbsPixels(float *x, float *y){

    SDL_Rect rct;

    if (SDL_GetDisplayBounds(0, &rct) != 0){

        //SDL_Log("\nError en SDL_GetDisplayBounds:");
        //SDL_Log(" %s\n", SDL_GetError());
        SDL_ClearError();
    }

    //SDL_Log("Para x rel: %f", *x);
    *x *= ((float)rct.w);
    //SDL_Log("Su absoluto es: %f\n", *x);

    if (y != nullptr) {
        //SDL_Log("Para y rel: %f", *y);
        *y *= ((float) rct.h);
        //SDL_Log("Su absoluto es: %f\n", *y);
    }

}

/**
 * \note Funcion para Android.
 *
 * \brief Procesa desplazamiento arrojando una
 * direction si se desplazan mas de 50 pixeles.
 * @param dX Val absoluto de pixeles x.
 * @param dY Val absoluto de pixeles y.
 * @return direction Up, Down, Left, Right, None.
 */
direction sdl::Window::process_Dplcmnt(float dX, float dY) {

    if ( (std::fabs(dY)) > (std::fabs(dX)) ){ // Movimiento vertical

        //SDL_Log("Val. relativo Y es mayor que val. relativo X.\n");
        //SDL_Log("dY: %f, dX %f.\n", dY, dX);

       if (dY > 0.0){
           //SDL_Log("\n\tRetornado Down.\n");
           return Down;
       }
        else if (dY < 0.0){
           //SDL_Log("\n\tRetornado Up.\n");
           return Up;
       }
    }

    else if ( (std::fabs(dX)) > (std::fabs(dY)) ) { // Movimiento horizontal

        //SDL_Log("Val. absoluto X es mayor que val. absoluto Y.\n");
        //SDL_Log("dX: %f, dY %f.\n", dX, dY);

        if (dX > 0.0) {
            //SDL_Log("\n\tRetornado Right.\n");
            return Right;
        }
        else if (dX < 0.0){
            //SDL_Log("\n\tRetornado Left.\n");
            return Left;
        }
    }

    //SDL_Log("\n\tRetornado None.\n");
    return None;
}

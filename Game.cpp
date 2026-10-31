//
// Created by Abraham Cruz Santibañez on 09/12/16.
//

#include "Game.h"
#include <iostream>
#include <algorithm>

const char *WINDOW_LAB= {"SDL_Project 2"};


Game::Game() : window(WINDOW_LAB, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                     WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
                board(nullptr), keys(nullptr) {}

bool Game::inicializar(){

    std::srand( (unsigned) time(nullptr));

    board.reset(new TetrisBoard(window.rend));

    board->setGameState(window.goodlyAsignedWandR());

    keys.reset(new Touch_Keys(window.rend));

    return board->getGameState();
}

int Game::ejecucion() {

    if (inicializar()) {

        while (board->getGameState())
            loop_Juego();

        std::cout << "Juego terminado." << std::endl;

        finalizar();

        return 0;
    }

    else {

        std::cout << SDL_GetError() << std::endl;
        return -1;
    }

}


void Game::loop_Juego()
{
#ifdef DEBUGGING
    static int count = 1;
    std::cout << "Loop de juego # "
              << count++ << std::endl;
#endif

    // Comienzo del frame
    board->startFrame_t = SDL_GetPerformanceCounter();

    // 1. Procesar los eventos de SDL2
    direction dir = procesa_Eventos();

    // Evitar continuar si se solicitó cerrar
    if (!board->getGameState()) {
        return;
    }

    // 2. Actualizar el tablero
    board->logic(dir);

    // 3. Limpiar la pantalla
    SDL_SetRenderDrawColor(window.rend, COLOR_BACK);
    SDL_RenderClear(window.rend);

    // 4. Dibujar el estado actualizado
    board->draw();
    keys->draw();

    // 5. Presentar el frame
    SDL_RenderPresent(window.rend);

    // 6. Calcular el tiempo transcurrido
    const Uint64 endFrame = SDL_GetPerformanceCounter();

    board->finalFrame_t =
        endFrame - board->startFrame_t;

    const Uint64 frequency =
        SDL_GetPerformanceFrequency();

    const double elapsedMs =
        static_cast<double>(board->finalFrame_t)
        * 1000.0
        / static_cast<double>(frequency);

    // 7. Aplicar el retraso calculado por TetrisBoard
    const double desiredMs = board->get_Delay();

    if (elapsedMs < desiredMs) {
        SDL_Delay(
            static_cast<Uint32>(desiredMs - elapsedMs)
        );
    }
}


direction Game::captura_Eventos() {

/* =======================================================
     * Implementación por dirección de
     * movimiento no es completamente
     * funcional al mover el dedo hacia
     * arriba.

#ifdef __ANDROID__

    float x = 0, y = 0, tmpx = 0, tmpy = 0;

    while (SDL_PollEvent(&event)){

        if (event.type == SDL_QUIT){ board->setGameState(false); }

        switch (event.type) {

            case SDL_FINGERMOTION: {

                tmpx = event.tfinger.dx;
                tmpy = event.tfinger.dy;

                window.get_AbsPixels(&tmpx, &tmpy);

                x += tmpx; y += tmpy;
                tmpx = tmpy = 0;

                if ((x > 70 || x < -70) || (y > 70 || y < -70))
                    return window.process_Dplcmnt(x, y);

                break;
            }

            default: break;
        }
    }

    return None;
#endif */



/* =======================================================
     * Se probará una implementación por toques
     * hacia un teclado dibujado debajo del
     * tablero.
     * Funciona bien, después de corregir que
     * la funcion SDL_PollEvent() se quedaba
     * procesando mucho tiempo debido a que
     * todos los casos aunque no eran útiles
     * regresaban algun valor, lo que
     * propiciaba que en la próxima llamada se
     * procesaran eventos anteriores y así se
     * obtenía un retraso sigificativo. */

#ifdef __ANDROID__

    float x = 0, y = 0;

    while (SDL_PollEvent(&event)){

        switch (event.type) {

            case SDL_QUIT: { board->setGameState(false); break;}

            case SDL_FINGERUP:
                break;

            case SDL_FINGERDOWN: {

                x = event.tfinger.x;
                y = event.tfinger.y;

                //SDL_Log("\nDesplazamiento x: %f desplazamiento y: %f.\n", x, y);

                window.get_AbsPixels(&x, &y);

                if (keys->U.isPoint_Inside((Sint16)x, (Sint16)y)) {
                    //SDL_Log("\nRetornado Up\n");
                    return Up;
                }

                if (keys->D.isPoint_Inside((Sint16)x, (Sint16)y)) {
                    //SDL_Log("\nRetornado Down\n");
                    return Down;
                }

                if (keys->L.isPoint_Inside((Sint16)x, (Sint16)y)) {
                    //SDL_Log("\nRetornado Left\n");
                    return Left;
                }

                if (keys->R.isPoint_Inside((Sint16)x, (Sint16)y)) {
                    //SDL_Log("\nRetornado Right\n");
                    return Right;
                }
                break;
            }

            default:
                break;
        }
    }

    return None;

#endif

#ifndef __ANDROID__

    while (SDL_PollEvent(&event)){

        if (event.type == SDL_QUIT){

            board->setGameState(false);
        }

        else if (event.type == SDL_KEYDOWN){

            switch(event.key.keysym.sym) {

                case SDLK_ESCAPE:
                    board->setGameState(false);
                    return None;

                case SDLK_UP:
                    return Up;

                case SDLK_RIGHT:
                    return Right;

                case SDLK_DOWN:
                    return Down;

                case SDLK_LEFT:
                    return Left;

                default:
                    return None;
            }
        }
    }

    return None;

#endif
}


direction Game::procesa_Eventos()
{
    direction dir = None;

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            board->setGameState(false);
            continue;
        }

        if (event.type != SDL_KEYDOWN)
            continue;

        switch (event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                board->setGameState(false);
                break;

            case SDLK_LEFT:
                dir = Left;
                break;

            case SDLK_RIGHT:
                dir = Right;
                break;

            case SDLK_UP:
                dir = Up;
                break;

            case SDLK_DOWN:
                dir = Down;
                break;

            default:
                break;
        }
    }
    return dir;
}


int Game::finalizar(){

    if (board)
        board->_debug_streamOutFrozenPcs();
    return 0;
}
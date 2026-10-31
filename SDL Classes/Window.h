//
// Created by Abraham Cruz Santibañez on 24/07/17.
//

#ifndef SDL_PROJECT2_WINDOW_HH
#define SDL_PROJECT2_WINDOW_HH

#ifdef __ANDROID__
#   include <SDL.h>
#   include <SDL_video.h>
#   include "Tetris_Rect.h"
#endif

#ifndef __ANDROID__
#   include <SDL2/SDL.h>
#   include <SDL2/SDL_video.h>
#   include "../Tetris_Rect.h"
#endif

#include <string>

/* *********** CLASE SDL ************ */

namespace sdl {

    class Window {

        SDL_Window *wind;

    public:

        SDL_Renderer *rend, *rend2;

#ifdef __ANDROID__
        SDL_DisplayMode disp;
#endif

        Window(const char *titulo, int x, int y, int w, int h, Uint32 wFlags, Uint32 rFlags = SDL_RENDERER_ACCELERATED);

        bool goodlyAsignedWandR() { return (wind != nullptr && rend != nullptr); }

        direction process_Dplcmnt(float dX, float dY);

        direction process_Positon(float x, float y);

        void get_AbsPixels(float *x, float *y = nullptr);


        ~Window() {
            SDL_DestroyRenderer(rend);
            SDL_DestroyWindow(wind);
            SDL_Quit();
        }
    };
}

#endif //SDL_PROJECT2_WINDOW_HH

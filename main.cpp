
#ifdef __ANDROID__
#include <SDL.h>
#include "SDL2_gfxPrimitives.h"
#include "Rect.h"
#endif

#ifndef __ANDROID__
#include <SDL.h>
#include "SDL2_Gfx/SDL2_gfxPrimitives.h"
#include "SDL Classes/Rect.h"
#endif

#include "Game.h"

int main(int argc, char **argv) {
	
    Game game1;
    //SDL_SetHint(SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH, "1");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    SDL_SetThreadPriority(SDL_THREAD_PRIORITY_HIGH);
    return game1.ejecucion();
}
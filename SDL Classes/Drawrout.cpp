//
// Created by Abraham Cruz Santibañez on 31/07/17.
//

#include "Drawrout.h"

Uint8 drawThinPtdLine(SDL_Renderer *rndr, Uint32 x, Uint32 y, Uint8 interv, Uint32 length, bool vertical){

    // Comprobar que no haya errores en los parametros recibidos

if (vertical == false) {
for (int i = 0; i < length; ++i) {

if (((i + interv) % (interv + 1)) == 0)
SDL_RenderDrawPoint(rndr, x + i, y);
}
}

else
for (int i = 0; i < length; ++i) {

if (((i + interv) % (interv + 1)) == 0)
SDL_RenderDrawPoint(rndr, x, y + i);
}

return 0;
}
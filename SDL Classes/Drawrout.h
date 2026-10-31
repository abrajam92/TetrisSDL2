//
// Created by Abraham Cruz Santibañez on 31/07/17.
//

#ifndef SDL_PROJECT2_DRAWROUT_HH
#define SDL_PROJECT2_DRAWROUT_HH

#ifdef __ANDROID__
#include <SDL.h>
#endif

#ifndef __ANDROID__
#include <SDL.h>
#endif

/**
 *
 * \brief Tiene que dibujar una línea punteada
 * utilizando subrutinas SDL_DrawPoint, la
 * implementación actual solo dibuja lineas
 * horizontales o verticales y de ancho fijo.
 * @param rndr Donde renderizar.
 * @param x Inicio x.
 * @param y Inicio y.
 * @param interv Intervalo de los puntos.
 * @param length Largo.
 * @param vertical bool ? vertical : horizonal.
 * @return Regresa -1 si hay un error, 0 en
 * caso contrario.
 */
Uint8 drawThinPtdLine(SDL_Renderer *rndr, Uint32 x, Uint32 y, Uint8 interv, Uint32 length, bool vertical = false);


#endif //SDL_PROJECT2_DRAWROUT_HH

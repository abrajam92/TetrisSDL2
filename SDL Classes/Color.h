//
// Created by Abraham Cruz Santibañez on 11/12/16.
//

#ifndef SIMPLE_SNAKE_SDL_COLOR_OBJ_HH
#define SIMPLE_SNAKE_SDL_COLOR_OBJ_HH

#ifdef __ANDROID__

#include <SDL.h>

#endif

#ifndef __ANDROID__

#include <SDL.h>

#endif

#include <iostream>

namespace sdl {

/**
 * \Brief Clase que guarda los valores Red, Green, Blue, y Alpha (transparencia)
 * de un color para renderizar en SDL.
 */
    class Color {

        SDL_Color color;

    public:

        /* ----- Constructores ---------------- */

        /** Constructor por defecto */
        Color() { set_Color(0, 0, 0, 0); }

        /** Constructor copia */
        Color(const Color &other)
        { set_Color(other.getR(), other.getG(), other.getB(), other.getA()); }

        /** Constructor que mueve */
        Color(Color &&other) noexcept
        { set_Color(other.getR(), other.getG(), other.getB(), other.getA()); }

        Color(int r, int g, int b, int a = 0) { set_Color(r, g, b, a); }



        /* ----- Setters y getters ------------ */

        void set_Color(int r, int g, int b, int a = 0) {

            if ((r >= 0 && r <= 255) && (g >= 0 && g <= 255) &&
                (b >= 0 && b <= 255) && (a >= 0 && a <= 255)) {

                color.r = static_cast<Uint8>(r);
                color.g = static_cast<Uint8>(g);
                color.b = static_cast<Uint8>(b);
                color.a = static_cast<Uint8>(a);
            } else
                std::cout << "No se puede asignar color RGBA: "
                          << r << ':' << g << ':' << b << ':' << a
                          << ". Valores deben ser entre 0 y 255." << std::endl;
        }

        int getR() const { return color.r; };

        int getG() const { return color.g; };

        int getB() const { return color.b; };

        int getA() const { return color.a; };



        /* ----- Lógica ----------------------- */

        /**
         * \brief Llama a SDL_SetRenderDrawColor para setear el color de dibujo como
         * el actual.
         * @param SDL_Renderer *
         */
        void fit_Color_to_Rend(SDL_Renderer *renderer) const {
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        }



        /* ----- Operadores ------------------- */

        Color &operator=(Color &otro){

            set_Color(otro.getR(), otro.getG(), otro.getB(), otro.getA());

            return *this;
        }
    };

}

#endif //SIMPLE_SNAKE_COLOR_H
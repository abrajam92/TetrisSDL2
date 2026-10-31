//
// Created by Abraham Cruz Santibañez on 11/12/16.
//

#ifndef SIMPLE_SNAKE_SDL_RECTOBJ_HH
#define SIMPLE_SNAKE_SDL_RECTOBJ_HH

#ifdef __ANDROID__
#include <SDL.h>
#endif

#ifndef __ANDROID__
#include <SDL.h>
#endif

#include <iostream>
#include "Color.h"

namespace sdl {

/**
 *
 * \Brief Esta clase guarda un valor SDL_Rect y un color correspondiente en caso de
 * tener que dibujar el rectángulo primitivo en el renderer, también puede
 * dibujar sprites mediante texturas sobre el rectángulo.
 * \note Falta implementar mas modos de colisión.
 */
    class Rect {

    protected:

        SDL_Rect rect;
        Color color_de_rect;

    public:

        /* --------- Constructores. */

        Rect(int x, int y, int w, int h, const Color color_dibujar);

        /** Constructor por defecto */
        Rect(int x = 0, int y = 0, int w = 0, int h = 0, int r = 0, int g = 0, int b = 0, int a = 255);

        /** Constructor copia */
        Rect(const Rect &other);



        /* ---------- Funciones que dibujan. */

        /**
         * \Brief Equivalente a función SDL_RenderDrawRect(), utilizando color por default
         * seteado en el objeto.
         * @param SDL_Renderer *
         */
        void draw_Rect_on_rend(SDL_Renderer *theRenderer);


        /**
         * \brief Dibuja un rectángulo con puntas redondas según el radio, utiliza funcion
         * de biblioteca GFX.
         * @param theRenderer
         * @param radio radio en píxeles de las puntas redondeadas.
         */
        void draw_GFXRoundedRect_on_rend(SDL_Renderer *theRenderer, Sint16 radio);

        /**
         * \brief Dibuja un rectángulo relleno con puntas redondas según el radio,
         * utiliza funcion de biblioteca GFX.
         * @param theRenderer
         * @param radio radio en píxeles de las puntas redondeadas.
         */
        void fill_GFXRoundedRect_on_rend(SDL_Renderer *theRenderer, Sint16 radio);


        /*!
         * \Brief Equivalente a SDL_RenderFillRect(), utilizando color por default
         * seteado en el objeto.
         * @param SDL_Renderer *
         */
        void fill_Rect_on_rend(SDL_Renderer *theRenderer);

        /**
         * \Brief Equivalente a SDL_RenderFillRect(), pasando un color diferente para dibujar
         * del seteado por default en el objeto.
         * @param SDL_Renderer *
         * @param SDL_ColorObj *
         */
        void fill_Rect_on_rend_W_Color(SDL_Renderer *theRenderer, Color *color);

        /**
         * \brief Dibuja un sprite en el rectángulo, tomando una textura y las dimensiones a tomar
         * de la textura, tambien puede girar los grados correspondientes.
         * @param SDL_Renderer * Renderer donde dibujar.
         * @param SDL_Texture * Textura a renderizar.
         * @param SDL_Rect * Source Rect (contiene las dimensiones que se ocuparán de la textura).
         * @param double (opcional) ángulo en coma flotante
         */
        void fill_WTexture_on_rend(SDL_Renderer *theRenderer, SDL_Texture *txture,
                                   SDL_Rect *sourceRect, double angle = 0.0f);


        /* --------- Setters y getters. */

        void set(int x, int y, int w, int h, int r, int g, int b, int a = 0);

        void set(int x, int y, int w, int h, const Color &color_dibujar);

        void set_RectValues(int x, int y, int w, int h);

        void set(SDL_Rect *rectFrom, int r = 0, int g = 0, int b = 0, int a = 0);

        void addToX(const int val) { rect.x += val; }

        void addToY(const int val) { rect.y += val; }

        void setX(const int x) { rect.x = x; }

        void setY(const int y) { rect.y = y; }

        void setW(const int w) { rect.w = w; }

        void setH(const int h) { rect.h = h; }

        /**
         * \brief Devuelve el inicio en x del Rect
         * @return
         */
        int const getX() const { return rect.x; }

        /**
         * \brief Devuelve el inicio en y del Rect
         * @return
         */
        int const getY() const { return rect.y; }

        /**
         * \brief Devuelve la altura absoluta del Rect
         * @return
         */
        int const getH() const { return rect.h; }

        /**
         * \brief Devuelve la anchura absoluta del Rect
         * @return
         */
        int const getW() const { return rect.w; }

        void setColor(const Color &color) {

            color_de_rect.set_Color(color.getR(),
                                    color.getG(),
                                    color.getB(),
                                    color.getA());
        };

        void setColor(int r, int g, int b, int a = 0) {

            color_de_rect. set_Color(r, g, b, a);
        };

        SDL_Rect *getRect() { return &rect; };

        const Color &getColor() const { return color_de_rect; };


        /* ---------- Colisiones */

        /**
         * \brief Comprueba si otro SDL_RectObj tiene la misma posición X e Y que el actual, y regresa
         * true si sucede.
         * @param SDL_RectObj &
         * @return bool
         */
        bool isEqualXY(const Rect &other) const;

        /**
         * \brief Comprueba si el rectángulo toca un eje Y entre su lado mas alto y mas bajo, regresa true
         * si sucede
         * @param int
         * @return bool
         */
        bool isOver_YAxis(const int y) const;

        /**
         * \brief Comprueba si el rectángulo toca un eje X entre su lado mas alto y mas bajo, regresa true
         * si sucede
         * @param int
         * @return bool
         */
        bool isOver_XAxis(const int x) const;

        /**
         * \brief Comprueba que el eje X está adjunto a la izquierda al rectánculo, regresa true si sucede.
         *
         * @param x
         * @return bool
         */
        bool isXAxis_LeftNext(int x) const;

        /**
         * \brief Comprueba que el eje X está adjunto a la derecha al rectánculo, regresa true si sucede.
         *
         * @param x
         * @return bool
         */
        bool isXAxis_RightNext(int x) const;

        /**
         * \brief Comprueba que el eje Y está adjunto arriba del rectánculo, regresa true si sucede.
         *
         * @param x
         * @return bool
         */
        bool isYAxis_UpNext(int y) const;

        /**
         * \brief Comprueba que el eje Y está adjunto arriba del rectánculo, regresa true si sucede.
         *
         * @param x
         * @return bool
         */
        bool isYAxis_DownNext(int y) const;

        /**
         * \brief Comprueba si existe un rectángulo adjunto arriba al actual, regresa true si sucede.
         * @param other
         * @return bool
         */
        bool isOtherRect_NextUp(Rect *other) const;

        /**
         * \brief Comprueba si existe un rectángulo adjunto abajo al actual, regresa true si sucede.
         * @param other
         * @return bool
         */
        bool isOtherRect_NextDown(Rect *other) const;

        /**
         * \brief Comprueba si existe un rectángulo adjunto a la izquierda al actual, regresa true si sucede.
         * @param other
         * @return bool
         */
        bool isOtherRect_NextLeft(Rect *other) const;

        /**
         * \brief Comprueba si existe un rectángulo adjunto a la derecha al actual, regresa true si sucede.
         * @param other
         * @return bool
         */
        bool isOtherRect_NextRight(Rect *other) const;

        bool isPoint_Inside(Sint16 x, Sint16 y) const;

        /* -------- Operadores */

        Rect &operator=(const Rect &otro){

            this->set(otro.getX(), otro.getY(), otro.getW(), otro.getH(), otro.getColor());

            return *this;
        }
    };

}

#endif //SIMPLE_SNAKE_PUNTO_H
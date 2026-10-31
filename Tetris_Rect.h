//
// Created by Abraham Cruz Santibañez on 05/01/17.
//

#ifndef SDL_PROJECT2_TETRISRECT_HH
#define SDL_PROJECT2_TETRISRECT_HH

#include <vector>
#include <cstdlib>
#include <array>
#include <iostream>


#ifdef __ANDROID__
#include "Rect.h"
#include "SDL2_gfxPrimitives.h"
#include "Drawrout.h"
#endif

#ifndef __ANDROID__
#include "SDL Classes/Rect.h"
#include "SDL2_Gfx/SDL2_gfxPrimitives.h"
#include "SDL Classes/Drawrout.h"
#endif

#ifdef __ANDROID__
constexpr int UNIT = 22;
#endif

#ifndef __ANDROID__
constexpr int UNIT = 16;
#endif

constexpr int WINDOW_WIDTH = 300;
constexpr int WINDOW_HEIGHT = 480;

constexpr int BOARD_WIDTH = UNIT * 10;
constexpr int BOARD_HEIGHT = UNIT * 20;

constexpr int DELAY_T = 650;

    /**
    * \brief Debe salvaguardar el tablero en su lado mas extremo
    * izquierdo, x = 229, en 230 es donde empiezan
    * las piezas
    * */
constexpr int BOARD_X_LEFT_GUARD = ((WINDOW_WIDTH - BOARD_WIDTH) / 2) - 11;
constexpr int BOARD_X_RIGHT_GUARD = BOARD_X_LEFT_GUARD + (UNIT * 10) + 1;

constexpr int PX_START = BOARD_X_LEFT_GUARD + (UNIT * 3) + 1;
constexpr int PY_START = (UNIT * -2);

constexpr int LCAN_X = 230;
constexpr int RCAN_X = 374;

// PALETA DE COLORES NUEVA
#define COLOR_PIECE_0 255, 120, 120
#define COLOR_PIECE_1 120, 255, 120
#define COLOR_PIECE_2 120, 120, 255
#define COLOR_PIECE_3 255, 255, 0
#define COLOR_PIECE_4 255, 0, 255
#define COLOR_PIECE_5 0, 255, 255
#define COLOR_PIECE_6 255, 255, 255

/* PALETA DE COLORES NORMAL
#define COLOR_PIECE_0 100, 160, 120
#define COLOR_PIECE_1 100, 140, 160
#define COLOR_PIECE_2 100, 120, 160
#define COLOR_PIECE_3 100, 160, 100
#define COLOR_PIECE_4 100, 120, 180
#define COLOR_PIECE_5 100, 160, 160
#define COLOR_PIECE_6 100, 120, 120
 */

#define COLOR_BOARD_LINES 220, 230, 230, 255
#define COLOR_BACK 20, 18, 20, 0

enum direction {Up, Left, Down, Right, None};

class Tetris_Rect : public sdl::Rect {

    bool erased;
    SDL_Renderer *renderer;

public:

    /* ------ Constructores --------------------------------- */

    /** Constructor por defecto */
    Tetris_Rect(int x = 0, int y = 0, int r = 0, int g = 0, int b = 0, int w = UNIT, int h = UNIT) :
            Rect(x, y, w, h, r, g, b), renderer(nullptr), erased(false) {}

    /** Constructor copia */
    Tetris_Rect(Tetris_Rect &other) : renderer(other.renderer), erased(other.erased) {

        set_RectValues(other.getX(), other.getY(), other.getW(), other.getH());
        color_de_rect = other.color_de_rect;
    }



    /* ------ Funciones que dibujan. ------------------------ */

    /* Debe dibujar la siguiente figura con 6 líneas:
     *
     *  **********
     *  **      **
     *  * *    * *
     *  *  *  *  *
     *  *   **   *
     *  *   **   *
     *  *  *  *  *
     *  * *    * *
     *  **      **
     *  **********
     *
     */
    void draw(SDL_Renderer *rendr, bool includeErased = true) {

        if (!erased || includeErased) {

            if (renderer == nullptr)
                renderer = rendr;

            /* Tetris burbujas */
            draw_GFXRoundedRect_on_rend(renderer, 2);

            // Dibuja cuarto de arco simulando brillo
            SDL_Point pts[7] = {getX() + (UNIT / 6), getY() + (UNIT / 3) + 1,
                                getX() + (UNIT / 6), getY() + (UNIT / 3),
                                getX() + (UNIT / 6), getY() + (UNIT / 3) - 1,
                                getX() + (UNIT / 6) + 1, getY() + (UNIT / 3) - 2,
                                getX() + (UNIT / 6) + 2, getY() + (UNIT / 3) - 3,
                                getX() + (UNIT / 6) + 3, getY() + (UNIT / 3) - 3,
                                getX() + (UNIT / 6) + 4, getY() + (UNIT / 3) - 3};

            SDL_RenderDrawPoints(rendr, pts, 7);
        }
    }

    void drawOnWaitArea(SDL_Renderer *rendr) {

        if (renderer == nullptr)
            renderer = rendr;

        getColor().fit_Color_to_Rend(renderer);

        roundedRectangleRGBA(renderer,
                             (Sint16) (getX() + getW() - 1 + 175),
                             (Sint16) (getY() + 100),
                             (Sint16) (getX() + 175),
                             (Sint16) (getY() + getH() - 1 + 100),
                             3,
                             (Uint8) color_de_rect.getR(),
                             (Uint8) color_de_rect.getG(),
                             (Uint8) color_de_rect.getB(), 255);
    }

    /* ------ LOGICA. ---------------------------- */

    void setErased(){erased = true;}

    bool isErased() const { return erased;}



    /* ------ Operadores. ------------------------ */

    Tetris_Rect &operator=(Tetris_Rect &otro){

        this->set_RectValues(otro.getX(), otro.getY(), otro.getW(), otro.getH());
        this->setColor(otro.getColor().getR(), otro.getColor().getG(), otro.getColor().getB(), otro.getColor().getA());

        this->renderer = otro.renderer;
        this->erased = otro.erased;

        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Tetris_Rect &obj) {

        os << "x: " << obj.getX() << " y: " << obj.getY()
           << " Erased: " << (obj.isErased() ? "erased: SI." : "erased: No.");

        os << std::endl;

        return os;
    }

    friend bool operator == (Tetris_Rect &first, Tetris_Rect &sec){

        return (first.getX() == sec.getX() && first.getY() == sec.getY());
    }

    friend bool operator != (Tetris_Rect &first, Tetris_Rect &sec){

        return !operator==(first, sec);
    }


    friend bool operator<(Tetris_Rect &first, Tetris_Rect &sec){

        std::cout << "Realizando comparación" << std::endl;

        if (first.getY() < sec.getY())
            return true;

        else return first.getX() < sec.getX();
    }

    static bool cmpY(Tetris_Rect *first, Tetris_Rect *sec){

        return first->getY() < sec->getY();
    }

    friend bool operator > (Tetris_Rect &first, Tetris_Rect &sec) {

        return operator<(sec, first);
    }
};


#endif //SDL_PROJECT2_TETRISRECT_HH
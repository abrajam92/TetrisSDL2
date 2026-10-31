//
// Created by Abraham Cruz Santibañez on 11/12/16.
//

#include "Rect.h"

#ifdef __ANDROID__
#include "SDL2_gfxPrimitives.h"
#endif

#ifndef __ANDROID__
#include "../SDL2_Gfx/SDL2_gfxPrimitives.h"
#endif


namespace sdl {



/* --------- Constructores. --------- */

    Rect::Rect(int x, int y, int w, int h, const Color color_dibujar)
            : color_de_rect(color_dibujar) {

        set_RectValues(x, y, w, h);
    }

    Rect::Rect(int x, int y, int w, int h, int r, int g, int b, int a)
            : color_de_rect(r, g, b, a) {

        set_RectValues(x, y, w, h);
    }

    Rect::Rect(const Rect &other) {

        set_RectValues(other.getX(), other.getY(), other.getW(), other.getH());
        setColor(other.color_de_rect);
    }



    /* ---------- Funciones que dibujan. --------- */

    void Rect::draw_Rect_on_rend(SDL_Renderer *theRenderer) {

        color_de_rect.fit_Color_to_Rend(theRenderer);
        SDL_RenderDrawRect(theRenderer, &rect);
    }

    void Rect::draw_GFXRoundedRect_on_rend(SDL_Renderer *theRenderer, Sint16 radio){

        roundedRectangleRGBA(theRenderer, (Sint16)rect.x, (Sint16)rect.y,
                             (Sint16)(rect.x + rect.w - 1),
                             (Sint16)(rect.y + rect.h - 1),
                             radio,
                             (Uint8)color_de_rect.getR(),
                             (Uint8)color_de_rect.getG(),
                             (Uint8)color_de_rect.getB(),
                             (Uint8)color_de_rect.getA() );
    }

    void Rect::fill_GFXRoundedRect_on_rend(SDL_Renderer *theRenderer, Sint16 radio){

        roundedBoxRGBA(theRenderer, (Sint16)rect.x, (Sint16)rect.y,
                       (Sint16)(rect.x + rect.w - 1),
                       (Sint16)(rect.y + rect.h - 1),
                       radio,
                       (Uint8)color_de_rect.getR(),
                       (Uint8)color_de_rect.getG(),
                       (Uint8)color_de_rect.getB(),
                       (Uint8)color_de_rect.getA() );
    }

    void Rect::fill_Rect_on_rend(SDL_Renderer *theRenderer) {

        color_de_rect.fit_Color_to_Rend(theRenderer);
        SDL_RenderFillRect(theRenderer, &rect);
    }

    void Rect::fill_Rect_on_rend_W_Color(SDL_Renderer *theRenderer, Color *color) {

        color->fit_Color_to_Rend(theRenderer);
        SDL_RenderFillRect(theRenderer, &rect);
    }

    void Rect::fill_WTexture_on_rend(SDL_Renderer *theRenderer, SDL_Texture *txture, SDL_Rect *sourceRect,
                                            double angle) {

        if (angle == 0.0f)
            SDL_RenderCopy(theRenderer, txture, sourceRect, &rect);

        else
            SDL_RenderCopyEx(theRenderer, txture, sourceRect, &rect, angle, 0, SDL_FLIP_NONE);
    }



/* --------- Setters y getters. --------- */

    void Rect::set(int x, int y, int w, int h, int r, int g, int b, int a) {

        set_RectValues(x, y, w, h);
        setColor(r, g, b, a);
    }

    void Rect::set(int x, int y, int w, int h, const Color &color_dibujar) {

        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;

        color_de_rect.set_Color(color_dibujar.getR(),
                                color_dibujar.getG(),
                                color_dibujar.getB(),
                                color_dibujar.getA());
    }

    void Rect::set_RectValues(int x, int y, int w, int h) {

        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
    }

    void Rect::set(SDL_Rect *rectFrom, int r, int g, int b, int a) {

        set_RectValues(rectFrom->x, rectFrom->y, rectFrom->w, rectFrom->h);
        setColor(r, g, b, a);
    }



/* ---------- Colisiones --------- */

    bool Rect::isEqualXY(const Rect &other) const {

        return (other.getX() == this->getX() && other.getY() == this->getY());
    }

    bool Rect::isOver_YAxis(const int y) const {

        return ((rect.y >= y) && ((rect.y + rect.h) <= y));
    }

    bool Rect::isOver_XAxis(const int x) const {

        return ((rect.x >= x) && ((rect.x + rect.w) <= x));
    }

    bool Rect::isXAxis_LeftNext(int x) const {

        return rect.x == x + 1;
    }

    bool Rect::isXAxis_RightNext(int x) const {

        return (rect.x + rect.w) == x;
    }

    bool Rect::isYAxis_UpNext(int y) const {

        return rect.y == y + 1;
    }

    bool Rect::isYAxis_DownNext(int y) const {

        return (rect.y + rect.h) == y;
    }

    bool Rect::isOtherRect_NextUp(Rect *other) const {

        return isYAxis_UpNext(other->getY() == (getY() - getH() - 1)) && (getX() == other->getX());
    }

    bool Rect::isOtherRect_NextDown(Rect *other) const {

        return isYAxis_DownNext(other->getY()) && (getX() == other->getX());
    }

    bool Rect::isOtherRect_NextLeft(Rect *other) const {

        return isXAxis_LeftNext(other->getX() + other->getW() - 1) && (getY() == other->getY());
    }

    bool Rect::isOtherRect_NextRight(Rect *other) const {

        return isXAxis_RightNext(other->getX()) && (getY() == other->getY());
    }

    bool Rect::isPoint_Inside(Sint16 x, Sint16 y) const {

        return x >= rect.x && x <= (rect.x + rect.w - 1) && y >= rect.y && y <= (rect.y + rect.h - 1);
    }


/* ---------- Operadores --------- */

}

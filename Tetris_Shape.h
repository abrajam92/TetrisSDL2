//
// Created by Abraham Cruz Santibañez on 06/01/17.
//

#ifndef SDL_PROJECT2_TETRIS_SHAPE_HH
#define SDL_PROJECT2_TETRIS_SHAPE_HH

#include <array>
#include <list>
#include <ostream>

#ifdef __ANDROID__
#include "Window.h"
#include "SDL2_gfxPrimitives.h"
#include "Tetris_Rect.h"
#endif

#ifndef __ANDROID__
#include "SDL Classes/Window.h"
#include "SDL2_Gfx/SDL2_gfxPrimitives.h"
#include "Tetris_Rect.h"
#endif

enum Shape{q, p, o, i, t, z, s};

class Tetris_Shape{

    Shape shape;
    Uint8 rot_Angle;
    SDL_Renderer *rendr;
    bool waitState;

    std::array<Tetris_Rect *, 4> rectsInShape;

public:



    /* ------ Constructores --------------------------------- */

    /** Constructor copia */
    Tetris_Shape(const Tetris_Shape &other);

    Tetris_Shape(SDL_Renderer *rend, bool waits);

    /** Constructor por defecto */
    Tetris_Shape();

    /* ------ LOGICA ---------------------------------------- */

private:

    void shapeGen();

public:

    void move(direction dir);

    void draw();

    inline bool isWaiting() const { return waitState;}

    inline std::array<Tetris_Rect *, 4> get_TetrisSquares(){ return rectsInShape; }

    inline void changeWaitToActual(){waitState = false;}


    /* ------ Rotaciones ------------------------------------- */

    void rotate(std::vector<Tetris_Rect *> floorShapes);

    void t_Rotator(Uint8 angle, bool bckwrd = false);

    void q_Rotator(Uint8 angle, bool bckwrd = false);

    void p_Rotator(Uint8 angle, bool bckwrd = false);

    void i_Rotator(Uint8 angle);

    void s_Rotator(Uint8 angle);

    void z_Rotator(Uint8 angle);



    /* ------ Colisiones ------------------------------------ */

    bool isYAxis_UpNext(int y) const;

    bool isYAxis_DownNext(int y) const;

    bool isXAxis_LeftNext(int x) const;

    bool isXAxis_RightNext(int x) const;

    bool touchesAnyUp(Tetris_Rect *other) const;

    bool touchesAnyDown(Tetris_Rect *other) const;

    bool touchesAnyLeft(Tetris_Rect *other) const;

    bool touchesAnyRight(Tetris_Rect *other) const;



    /* ------ Colisiones con Tetris_Board  ------------------ */

    bool isOverlapping_Walls() const;

    bool isAdjuntTo_AnyWalls() const;

    bool isAdjuntTo_Walls(direction dir) const;

    bool isAdjuntTo_UpFloor(std::vector<Tetris_Rect *> shapesOnFloor) const;

    bool isAdjuntTo_DownFloor(std::vector<Tetris_Rect *> shapesOnFloor) const;

    bool isAdjuntTo_RWallsOrPcs(std::vector<Tetris_Rect *> shapesOnFloor) const;

    bool isAdjuntTo_LWallsOrPcs(std::vector<Tetris_Rect *> shapesOnFloor) const;

    bool isEqualPosAsAny(std::vector<Tetris_Rect *> shapesOnFloor) const;



    /* ------ Operadores  ----------------------------------- */

    friend std::ostream &operator<<(std::ostream &os, const Tetris_Shape &sh) {

        using namespace std;

        os << endl << "Forma #: " << sh.shape << endl
           << *sh.rectsInShape[0] << *sh.rectsInShape[1]
           << *sh.rectsInShape[2] << *sh.rectsInShape[3] << endl;
        return os;
    }

    Tetris_Shape &operator=(Tetris_Shape &otra){

        shape = otra.shape;
        rot_Angle = otra.rot_Angle;
        rendr = otra.rendr;
        waitState = otra.waitState;

        *rectsInShape[0] = *otra.rectsInShape[0];
        *rectsInShape[1] = *otra.rectsInShape[1];
        *rectsInShape[2] = *otra.rectsInShape[2];
        *rectsInShape[3] = *otra.rectsInShape[3];

        return *this;
    }

};

#endif //SDL_PROJECT2_TETRIS_SHAPE_HH
//
// Created by Abraham Cruz Santibañez on 06/01/17.
//

#include "Tetris_Board.h"
#include "Tetris_Shape.h"
#include <algorithm>



/* ----------  Constructores  -------------------------------------- */

Tetris_Shape::Tetris_Shape(SDL_Renderer *rend, bool waits) : rendr(rend), waitState(waits), rot_Angle(0){

    shapeGen();
}

Tetris_Shape::Tetris_Shape() : rendr(nullptr), waitState(false), rot_Angle(0) {

    shapeGen();
}

Tetris_Shape::Tetris_Shape(const Tetris_Shape &other) :
        rendr(other.rendr), waitState(other.waitState), rot_Angle(other.rot_Angle), shape(other.shape), rectsInShape() {}

/* ----------  LOGICA  -------------------------------------------- */


void Tetris_Shape::shapeGen() {

    int formN = std::rand() % 7;

    switch(formN){

        /*

        01 (Forma 0) "q"
         2
         3

        */
        case 0:
            rectsInShape[0] = new Tetris_Rect(PX_START, PY_START, COLOR_PIECE_0);
            rectsInShape[1] = new Tetris_Rect(PX_START + UNIT, PY_START, COLOR_PIECE_0);
            rectsInShape[2] = new Tetris_Rect(PX_START + UNIT, PY_START + UNIT, COLOR_PIECE_0);
            rectsInShape[3] = new Tetris_Rect(PX_START + UNIT, PY_START + (UNIT * 2), COLOR_PIECE_0);

            shape = q;
            break;

            /*

            10 (Forma 1) "p"
            2-
            3-

            */
        case 1:
            rectsInShape[0] = new Tetris_Rect(PX_START + UNIT, PY_START, COLOR_PIECE_1);
            rectsInShape[1] = new Tetris_Rect(PX_START, PY_START, COLOR_PIECE_1);
            rectsInShape[2] = new Tetris_Rect(PX_START, PY_START+ UNIT, COLOR_PIECE_1);
            rectsInShape[3] = new Tetris_Rect(PX_START, PY_START + (UNIT * 2), COLOR_PIECE_1);

            shape = p;
            break;

            /*

            ** (Forma 2) "o"
            **

             */
        case 2:
            rectsInShape[0] = new Tetris_Rect(PX_START, PY_START, COLOR_PIECE_2);
            rectsInShape[1] = new Tetris_Rect(PX_START + UNIT, PY_START, COLOR_PIECE_2);
            rectsInShape[2] = new Tetris_Rect(PX_START, PY_START + UNIT, COLOR_PIECE_2);
            rectsInShape[3] = new Tetris_Rect(PX_START + UNIT, PY_START + UNIT, COLOR_PIECE_2);

            shape = o;
            break;

            /*

            0- (Forma 3) "i"
            1-
            2-
            3-

            */
        case 3:
            rectsInShape[0] = new Tetris_Rect(PX_START, PY_START, COLOR_PIECE_3);
            rectsInShape[1] = new Tetris_Rect(PX_START, PY_START + UNIT, COLOR_PIECE_3);
            rectsInShape[2] = new Tetris_Rect(PX_START, PY_START + (UNIT * 2), COLOR_PIECE_3);
            rectsInShape[3] = new Tetris_Rect(PX_START, PY_START + (UNIT * 3), COLOR_PIECE_3);

            shape = i;
            break;

            /*

            -*- (Forma 4) "t"
            ***

            */
        case 4:
            rectsInShape[0] = new Tetris_Rect(PX_START + UNIT, PY_START, COLOR_PIECE_4);
            rectsInShape[1] = new Tetris_Rect(PX_START, PY_START + UNIT, COLOR_PIECE_4);
            rectsInShape[2] = new Tetris_Rect(PX_START + UNIT, PY_START + UNIT, COLOR_PIECE_4);
            rectsInShape[3] = new Tetris_Rect(PX_START + (UNIT * 2), PY_START + UNIT, COLOR_PIECE_4);

            shape = t;
            break;

            /*

            **- (Forma 5) "z"
            -**

            */
        case 5:


            rectsInShape[0] = new Tetris_Rect(PX_START, PY_START, COLOR_PIECE_5);
            rectsInShape[1] = new Tetris_Rect(PX_START + UNIT, PY_START, COLOR_PIECE_5);
            rectsInShape[2] = new Tetris_Rect(PX_START + UNIT, PY_START + UNIT, COLOR_PIECE_5);
            rectsInShape[3] = new Tetris_Rect(PX_START + (UNIT * 2), PY_START + UNIT, COLOR_PIECE_5);

            shape = z;
            break;

            /*

            -** (Forma 6) "s"
            **-

            */
        case 6:
            rectsInShape[0] = new Tetris_Rect(PX_START, PY_START + UNIT, COLOR_PIECE_6);
            rectsInShape[1] = new Tetris_Rect(PX_START + UNIT, PY_START + UNIT, COLOR_PIECE_6);
            rectsInShape[2] = new Tetris_Rect(PX_START + UNIT, PY_START, COLOR_PIECE_6);
            rectsInShape[3] = new Tetris_Rect(PX_START + (UNIT * 2), PY_START, COLOR_PIECE_6);

            shape = s;
            break;

        default:
            break;
    }
}

void Tetris_Shape::move(direction dir) {

    switch(dir){

        case Left:
            for (Tetris_Rect *i : rectsInShape)
                i->addToX(-UNIT);
            break;

        case Down:
            for (Tetris_Rect *i : rectsInShape)
                i->addToY(UNIT);
            break;

        case Right:
            for (Tetris_Rect *i : rectsInShape)
                i->addToX(UNIT);
            break;

        default:
            break;
    }
}

void Tetris_Shape::draw() {

    if (!isWaiting())
        for (Tetris_Rect *i : rectsInShape)
            i->draw(rendr);

    else
        for (Tetris_Rect *i : rectsInShape)
            i->drawOnWaitArea(rendr);

}



/* ----------  Rotaciones  ---------------------------------------- */

void Tetris_Shape::rotate(std::vector<Tetris_Rect *> floorShapes) {

    (rot_Angle < 3) ? ++rot_Angle : rot_Angle = 0;

    switch (shape){

        case p: p_Rotator(rot_Angle);
            break;
        case q: q_Rotator(rot_Angle);
            break;
        case i: i_Rotator(rot_Angle);
            break;
        case t: t_Rotator(rot_Angle);
            break;
        case z: z_Rotator(rot_Angle);
            break;
        case s: s_Rotator(rot_Angle);
            break;
        case o:
        default:
            break;
    }

        /** I detecta bien colisiones
         *  S detecta bien colisiones
         *  Z detecta bien colisiones
         *  T hay problemas
         *  Q hay problemas
         *  P hay problemas
         */
    if (!isEqualPosAsAny(floorShapes) &&
        !isOverlapping_Walls()
            ) return;

    else { (rot_Angle == 0) ? rot_Angle = 3 : --rot_Angle;

        switch (shape){

            case p: p_Rotator(rot_Angle, true);
                break;
            case q: q_Rotator(rot_Angle, true);
                break;
            case i: i_Rotator(rot_Angle);
                break;
            case t: t_Rotator(rot_Angle, true);
                break;
            case z: z_Rotator(rot_Angle);
                break;
            case s: s_Rotator(rot_Angle);
                break;
            case o:
            default:
                return;
        }
    }
}

void Tetris_Shape::p_Rotator(Uint8 angle, bool bckwrd) {

    if (!bckwrd) { switch (angle) {
            case 0: /* CORRECTO */
                rectsInShape[0]->addToX((UNIT * 2));
                rectsInShape[1]->addToX(UNIT);
                rectsInShape[1]->addToY(-UNIT);
                rectsInShape[3]->addToX(-UNIT);
                rectsInShape[3]->addToY(UNIT);
                break;
            case 1: /* CORRECTO */
                rectsInShape[0]->addToY(UNIT * 2);
                rectsInShape[1]->addToX(UNIT);
                rectsInShape[1]->addToY(UNIT);
                rectsInShape[3]->addToX(-UNIT);
                rectsInShape[3]->addToY(-UNIT);
                break;
            case 2: /* CORRECTO */
                rectsInShape[0]->addToX(-(UNIT * 2));
                rectsInShape[1]->addToX(-UNIT);
                rectsInShape[1]->addToY(UNIT);
                rectsInShape[3]->addToX(UNIT);
                rectsInShape[3]->addToY(-UNIT);
                break;
            case 3: /* CORRECTO */
                rectsInShape[0]->addToY(-(UNIT * 2));
                rectsInShape[1]->addToX(-UNIT);
                rectsInShape[1]->addToY(-UNIT);
                rectsInShape[3]->addToX(UNIT);
                rectsInShape[3]->addToY(UNIT);
                break;
            default:
                break;
        }
    } else {
        switch (angle) {

            case 0: /* CORRECTO */
                rectsInShape[0]->addToY(-(UNIT * 2));
                rectsInShape[1]->addToX(-UNIT);
                rectsInShape[1]->addToY(-UNIT);
                rectsInShape[3]->addToX(UNIT);
                rectsInShape[3]->addToY(UNIT);
                break;
            case 1: /* CORRECTO */
                rectsInShape[0]->addToX((UNIT * 2));
                rectsInShape[1]->addToX(UNIT);
                rectsInShape[1]->addToY(-UNIT);
                rectsInShape[3]->addToX(-UNIT);
                rectsInShape[3]->addToY(UNIT);
                break;
            case 2: /* CORRECTO */
                rectsInShape[0]->addToY((UNIT * 2));
                rectsInShape[1]->addToX(UNIT);
                rectsInShape[1]->addToY(UNIT);
                rectsInShape[3]->addToX(-UNIT);
                rectsInShape[3]->addToY(-UNIT);
                break;
            case 3: /* CORRECTO */
                rectsInShape[0]->addToX(-(UNIT * 2));
                rectsInShape[1]->addToX(-UNIT);
                rectsInShape[1]->addToY(UNIT);
                rectsInShape[3]->addToX(UNIT);
                rectsInShape[3]->addToY(-UNIT);
                break;
            default:
                break;
        }
    }
}

void Tetris_Shape::q_Rotator(Uint8 angle, bool bckwrd) {

/* Tiene 4 rotaciones
 *
 *  01   0 3
 *   2 321 2  123
 *   3     10 0
 */

    if (!bckwrd) { switch (angle) {
            case 0: // CORRECTO
                rectsInShape[0]->addToY(-(UNIT * 2));
                rectsInShape[1]->addToX(UNIT);
                rectsInShape[1]->addToY(-UNIT);
                rectsInShape[3]->addToX(-UNIT);
                rectsInShape[3]->addToY(UNIT);
                break;
            case 1:  // CORRECTO
                rectsInShape[0]->addToX((UNIT * 2));
                rectsInShape[1]->addToX(UNIT);
                rectsInShape[1]->addToY(UNIT);
                rectsInShape[3]->addToX(-UNIT);
                rectsInShape[3]->addToY(-UNIT);
                break;
            case 2: // CORRECTO
                rectsInShape[0]->addToY((UNIT * 2));
                rectsInShape[1]->addToX(-UNIT);
                rectsInShape[1]->addToY(UNIT);
                rectsInShape[3]->addToX(UNIT);
                rectsInShape[3]->addToY(-UNIT);
                break;
            case 3:// CORRECTO
                rectsInShape[0]->addToX(-(UNIT * 2));
                rectsInShape[1]->addToX(-UNIT);
                rectsInShape[1]->addToY(-UNIT);
                rectsInShape[3]->addToX(UNIT);
                rectsInShape[3]->addToY(UNIT);
                break;
            default:
                break;
        }
    } else switch (angle) {
            case 0: // CORRECTO
                rectsInShape[0]->addToX(-(UNIT * 2));
                rectsInShape[1]->addToX(-UNIT);
                rectsInShape[1]->addToY(-UNIT);
                rectsInShape[3]->addToX(UNIT);
                rectsInShape[3]->addToY(UNIT);
                break;

            case 1:  // CORRECTO
                rectsInShape[0]->addToY(-(UNIT * 2));
                rectsInShape[1]->addToX(UNIT);
                rectsInShape[1]->addToY(-UNIT);
                rectsInShape[3]->addToX(-UNIT);
                rectsInShape[3]->addToY(UNIT);
                break;


            case 2: // CORRECTO
                rectsInShape[0]->addToX((UNIT * 2));
                rectsInShape[1]->addToX(UNIT);
                rectsInShape[1]->addToY(UNIT);
                rectsInShape[3]->addToX(-UNIT);
                rectsInShape[3]->addToY(-UNIT);
                break;

            case 3:// CORRECTO
                rectsInShape[0]->addToY((UNIT * 2));
                rectsInShape[1]->addToX(-UNIT);
                rectsInShape[1]->addToY(UNIT);
                rectsInShape[3]->addToX(UNIT);
                rectsInShape[3]->addToY(-UNIT);
                break;

            default:
                break;
        }
}

void Tetris_Shape::t_Rotator(Uint8 angle, bool bckwrd) {

    if (!bckwrd) {
        switch (angle) {

            case 0: /*  */
                rectsInShape[0]->addToX(UNIT);
                rectsInShape[0]->addToY(-UNIT);
                rectsInShape[1]->addToX(-UNIT);
                rectsInShape[1]->addToY(-UNIT);
                rectsInShape[3]->addToX(UNIT);
                rectsInShape[3]->addToY(UNIT);
                break;

            case 1: /*  */
                rectsInShape[0]->addToX(UNIT);
                rectsInShape[0]->addToY(UNIT);
                rectsInShape[1]->addToX(UNIT);
                rectsInShape[1]->addToY(-UNIT);
                rectsInShape[3]->addToX(-UNIT);
                rectsInShape[3]->addToY(UNIT);
                break;

            case 2: /*  */
                rectsInShape[0]->addToX(-UNIT);
                rectsInShape[0]->addToY(UNIT);
                rectsInShape[1]->addToX(UNIT);
                rectsInShape[1]->addToY(UNIT);
                rectsInShape[3]->addToX(-UNIT);
                rectsInShape[3]->addToY(-UNIT);
                break;

            case 3: /*  */
                rectsInShape[0]->addToX(-UNIT);
                rectsInShape[0]->addToY(-UNIT);
                rectsInShape[1]->addToX(-UNIT);
                rectsInShape[1]->addToY(UNIT);
                rectsInShape[3]->addToX(UNIT);
                rectsInShape[3]->addToY(-UNIT);
                break;

            default:
                break;
        }
    } else { switch (angle) {

            case 0: /*  */
                rectsInShape[0]->addToX(-UNIT);
                rectsInShape[0]->addToY(-UNIT);
                rectsInShape[1]->addToX(-UNIT);
                rectsInShape[1]->addToY(UNIT);
                rectsInShape[3]->addToX(UNIT);
                rectsInShape[3]->addToY(-UNIT);
                break;

            case 1: /*  */
                rectsInShape[0]->addToX(UNIT);
                rectsInShape[0]->addToY(-UNIT);
                rectsInShape[1]->addToX(-UNIT);
                rectsInShape[1]->addToY(-UNIT);
                rectsInShape[3]->addToX(UNIT);
                rectsInShape[3]->addToY(UNIT);
                break;

            case 2: /*  */
                rectsInShape[0]->addToX(UNIT);
                rectsInShape[0]->addToY(UNIT);
                rectsInShape[1]->addToX(UNIT);
                rectsInShape[1]->addToY(-UNIT);
                rectsInShape[3]->addToX(-UNIT);
                rectsInShape[3]->addToY(UNIT);
                break;

            case 3: /*  */
                rectsInShape[0]->addToX(-UNIT);
                rectsInShape[0]->addToY(UNIT);
                rectsInShape[1]->addToX(UNIT);
                rectsInShape[1]->addToY(UNIT);
                rectsInShape[3]->addToX(-UNIT);
                rectsInShape[3]->addToY(-UNIT);
                break;

            default:
                break;
        }

    }
}

void Tetris_Shape::i_Rotator(Uint8 angle) {

    /* Tiene 2 rotaciones
     *  0 1    2 3
     *  *      *
     *  * **** * ****
     *  *      *
     *  *      *
     * */
    switch (angle) {

        case 3:
        case 1: /*  */ {

            rectsInShape[0]->addToX(-(UNIT * 2));
            rectsInShape[0]->addToY((UNIT * 2));
            rectsInShape[1]->addToX(-UNIT);
            rectsInShape[1]->addToY(UNIT);
            rectsInShape[3]->addToX(UNIT);
            rectsInShape[3]->addToY(-UNIT);
            break;
        }

        case 0:
        case 2: /*  */ {

            rectsInShape[0]->addToX(UNIT * 2);
            rectsInShape[0]->addToY(-(UNIT * 2));
            rectsInShape[1]->addToX(UNIT);
            rectsInShape[1]->addToY(-UNIT);
            rectsInShape[3]->addToX(-UNIT);
            rectsInShape[3]->addToY(UNIT);
            break;
        }

        default:
            break;
    }
}

void Tetris_Shape::s_Rotator(Uint8 angle) {

    switch (angle) {

        case 3:
        case 1: /*  */
            rectsInShape[0]->addToY(-(UNIT * 2));
            rectsInShape[1]->addToX(-UNIT);
            rectsInShape[1]->addToY(-UNIT);
            rectsInShape[3]->addToX(-UNIT);
            rectsInShape[3]->addToY(UNIT);
            break;

        case 0:
        case 2: /*  */
            rectsInShape[0]->addToY((UNIT * 2));
            rectsInShape[1]->addToX(UNIT);
            rectsInShape[1]->addToY(UNIT);
            rectsInShape[3]->addToX(UNIT);
            rectsInShape[3]->addToY(-UNIT);
            break;

        default:
            break;
    }
}

void Tetris_Shape::z_Rotator(Uint8 angle) {

    switch (angle) {

        case 3:
        case 1: /*  */
            rectsInShape[0]->addToX((UNIT * 2));
            rectsInShape[1]->addToX(UNIT);
            rectsInShape[1]->addToY(UNIT);
            rectsInShape[3]->addToX(-UNIT);
            rectsInShape[3]->addToY(UNIT);
            break;


        case 0:
        case 2: /*  */
            rectsInShape[0]->addToX(-(UNIT * 2));
            rectsInShape[1]->addToX(-UNIT);
            rectsInShape[1]->addToY(-UNIT);
            rectsInShape[3]->addToX(UNIT);
            rectsInShape[3]->addToY(-UNIT);
            break;

        default:
            break;
    }
}



/* ------ Colisiones ------------------------------------ */

bool Tetris_Shape::isYAxis_UpNext(int y) const {

    for (Tetris_Rect *i : rectsInShape)
        if (i->isYAxis_UpNext(y))
            return true;

    return false;
}

bool Tetris_Shape::isYAxis_DownNext(int y) const {

    for (Tetris_Rect *i : rectsInShape)
        if (i->isYAxis_DownNext(y))
            return true;

    return false;
}

bool Tetris_Shape::isXAxis_LeftNext(int x) const {

    for (Tetris_Rect *i : rectsInShape)
        if (i->isXAxis_LeftNext(x))
            return true;

    return false;
}

bool Tetris_Shape::isXAxis_RightNext(int x) const {

    for (Tetris_Rect *i : rectsInShape)
        if (i->isXAxis_RightNext(x))
            return true;

    return false;
}

bool Tetris_Shape::touchesAnyLeft(Tetris_Rect *other) const {

    for (Tetris_Rect *i : rectsInShape){

        if (i->isOtherRect_NextLeft(other))
            return true;
    }

    return false;
}

bool Tetris_Shape::touchesAnyRight(Tetris_Rect *other) const {

    for (Tetris_Rect *i : rectsInShape){

        if (i->isOtherRect_NextRight(other))
            return true;
    }

    return false;
}

bool Tetris_Shape::touchesAnyDown(Tetris_Rect *other) const {

    for (Tetris_Rect *i : rectsInShape){

        if (i->isOtherRect_NextDown(other))
            return true;
    }

    return false;
}

bool Tetris_Shape::touchesAnyUp(Tetris_Rect *other) const {

    for (Tetris_Rect *i : rectsInShape){

        if (i->isOtherRect_NextUp(other))
            return true;
    }

    return false;
}



/* -----------------  Colisiones con Tetris_Board  -------------------------------- */

bool Tetris_Shape::isAdjuntTo_AnyWalls() const {

    return isXAxis_LeftNext(BOARD_X_LEFT_GUARD) ||
           isXAxis_RightNext(BOARD_X_RIGHT_GUARD) ||
           isYAxis_DownNext(BOARD_HEIGHT);
}

bool Tetris_Shape::isAdjuntTo_Walls(direction dir) const {

    switch (dir){

        case Left:
            return isXAxis_LeftNext(BOARD_X_LEFT_GUARD);

        case Right:
            return isXAxis_RightNext(BOARD_X_RIGHT_GUARD);

        case Down:
            return isYAxis_DownNext(BOARD_HEIGHT);

        default:
            return false;
    }
}

bool Tetris_Shape::isAdjuntTo_UpFloor(std::vector<Tetris_Rect *> shapesOnFloor) const {

    if (!shapesOnFloor.empty()){ // Comprobar si actualShape toca alguno de los Tetris_Rect en frozenPieces

        for (Tetris_Rect *i : shapesOnFloor) {

            if (touchesAnyUp(i) || isAdjuntTo_Walls(Down))
                return true;
        }

        return isAdjuntTo_Walls(Down);
    }

    else
        return isAdjuntTo_Walls(Down);
}

bool Tetris_Shape::isAdjuntTo_DownFloor(std::vector<Tetris_Rect *> shapesOnFloor) const {

    if (!shapesOnFloor.empty()){ // Comprobar si actualShape toca alguno de los Tetris_Rect en frozenPieces

        for (Tetris_Rect *i : shapesOnFloor) {

            if (touchesAnyDown(i) || isAdjuntTo_Walls(Down))
            return true;
        }

        return isAdjuntTo_Walls(Down);
    }

    else
        return isAdjuntTo_Walls(Down);
}

bool Tetris_Shape::isAdjuntTo_LWallsOrPcs(std::vector<Tetris_Rect *> shapesOnFloor) const {

    if (!shapesOnFloor.empty()) {

        for (Tetris_Rect *i : shapesOnFloor) {

            if (touchesAnyLeft(i) || isAdjuntTo_Walls(Left))
                return true;
        }
    }

    return isAdjuntTo_Walls(Left);
}

bool Tetris_Shape::isAdjuntTo_RWallsOrPcs(std::vector<Tetris_Rect *> shapesOnFloor) const {

    if (!shapesOnFloor.empty()) {

        for (Tetris_Rect *i : shapesOnFloor) {

            if (touchesAnyRight(i) || isAdjuntTo_Walls(Right))
                return true;
        }
    }

    return isAdjuntTo_Walls(Right);
}

bool Tetris_Shape::isOverlapping_Walls() const {

    for (auto i : rectsInShape) {

        if (i->getX() >= BOARD_X_RIGHT_GUARD || i->getX() <= BOARD_X_LEFT_GUARD)
            return true;
        if (i->getY() > BOARD_HEIGHT)
            return true;
    }

    return false;
}

bool Tetris_Shape::isEqualPosAsAny(std::vector<Tetris_Rect *> shapesOnFloor) const {

    bool returned = false;

    if (!shapesOnFloor.empty())
        for (auto i : rectsInShape)
            returned = std::any_of(shapesOnFloor.begin(), shapesOnFloor.end(),
                                   [=](Tetris_Rect *rct) { return i->isEqualXY(*rct); });

    return returned;
}

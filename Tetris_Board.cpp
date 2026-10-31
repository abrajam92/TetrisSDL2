//
// Created by Abraham Cruz Santibañez on 06/01/17.
//

#include "Tetris_Board.h"

#ifdef __ANDROID__
#include "Drawrout.h"
#include "SDL2_gfxPrimitives.h"
#endif

#ifndef __ANDROID__
#include "SDL Classes/Drawrout.h"
#include "SDL2_Gfx/SDL2_gfxPrimitives.h"
#endif

#include <iostream>
#include <algorithm>

#define DEBUGGING

/* ----------  Constructores ------------------------- */

TetrisBoard::TetrisBoard(SDL_Renderer *rnd) : renderer(rnd), gameState(true), pauseState(false),
                                              frozenPieces(), delay_t(DELAY_T), lines_Made(0),
                                              linesToMoveOverPieces(0), null_Iterator(), bdlines(rnd) {

    pieces_over_erased = null_Iterator;

    actual = new Tetris_Shape(renderer, false);
    next = new Tetris_Shape(renderer, true);
}



/* ----------  Funciones que dibujan  ---------------- */

void TetrisBoard::draw() {

    drawBoard();
    drawWaitingArea();
    actual->draw();
    next->draw();

#ifdef DEBUGGING

    using std::cout; using std::endl;
    cout << "La forma actual se compone de: ";
    cout << *actual << endl;

#endif

    if(!frozenPieces.empty()) {
        for (Tetris_Rect *i : frozenPieces) {
            i->draw(renderer);
        }
    }
}

void TetrisBoard::drawBoard() {

    bdlines.draw();

    std::string str = std::to_string(lines_Made);

    gfxPrimitivesSetFont(nullptr, 0, 0);
    stringRGBA(renderer, BOARD_X_RIGHT_GUARD + 50, BOARD_HEIGHT - 140, "LINES MADE", 255, 255, 255, 255);
    stringRGBA(renderer, BOARD_X_RIGHT_GUARD + 50, BOARD_HEIGHT - 120, str.c_str(), 255, 255, 255, 255);
}

// Debe contener a futuro las líneas que delimitan el area de espera
void TetrisBoard::drawWaitingArea() {
    thickLineRGBA(renderer, BOARD_X_RIGHT_GUARD + 46, BOARD_HEIGHT - 260, BOARD_X_RIGHT_GUARD + 46, BOARD_HEIGHT - 180, 1, COLOR_BOARD_LINES);
    thickLineRGBA(renderer, BOARD_X_RIGHT_GUARD + 46, BOARD_HEIGHT - 260, BOARD_X_RIGHT_GUARD + 130, BOARD_HEIGHT - 260, 1, COLOR_BOARD_LINES);
    thickLineRGBA(renderer, BOARD_X_RIGHT_GUARD + 130, BOARD_HEIGHT - 260, BOARD_X_RIGHT_GUARD + 130, BOARD_HEIGHT - 180, 1, COLOR_BOARD_LINES);
    thickLineRGBA(renderer, BOARD_X_RIGHT_GUARD + 46, BOARD_HEIGHT - 180, BOARD_X_RIGHT_GUARD + 130, BOARD_HEIGHT - 180, 1, COLOR_BOARD_LINES);
}

void TetrisBoard::shake(){

    /* Tiene que mover las líneas del tablero
     * (incluyendo las líneas punteadas) y
     * las piezas congeladas.
     *
     * La pieza actual, la siguiente, las
     * lineas de borde del área de espera y
     * las letras se deben dibujar pero sin
     * mover (Tampoco el teclado virtual en
     * Android).
     */

#ifndef __ANDROID__

    SDL_SetRenderDrawColor(renderer ,COLOR_BACK);
    SDL_RenderClear(renderer);
    bdlines.moveX(13); // 13 a la derecha
    bdlines.draw();
    for (auto i : frozenPieces) i->addToX(13), i->draw(renderer, true);
    actual->draw(); next->draw();
    SDL_RenderPresent(renderer);

    SDL_Delay(45);

    SDL_SetRenderDrawColor(renderer ,COLOR_BACK);
    SDL_RenderClear(renderer);
    bdlines.moveX(-26); // 13 a la izquierda
    bdlines.draw();
    for (auto i : frozenPieces) i->addToX(-26), i->draw(renderer, true);
    actual->draw(); next->draw();
    SDL_RenderPresent(renderer);

    SDL_Delay(50);

    SDL_SetRenderDrawColor(renderer ,COLOR_BACK);
    SDL_RenderClear(renderer);
    bdlines.moveX(21); // 8 a la derecha
    bdlines.draw();
    for (auto i : frozenPieces) i->addToX(21), i->draw(renderer, true);
    actual->draw(); next->draw();
    SDL_RenderPresent(renderer);

    SDL_Delay(50);

    SDL_SetRenderDrawColor(renderer ,COLOR_BACK);
    SDL_RenderClear(renderer);
    bdlines.moveX(-16); // 8 a la izquierda
    bdlines.draw();
    for (auto i : frozenPieces) i->addToX(-16), i->draw(renderer, true);
    actual->draw(); next->draw();
    SDL_RenderPresent(renderer);

    SDL_Delay(58);

    SDL_SetRenderDrawColor(renderer ,COLOR_BACK);
    SDL_RenderClear(renderer);
    bdlines.moveX(13); // 5 a la derecha
    bdlines.draw();
    for (auto i : frozenPieces) i->addToX(13), i->draw(renderer, true);
    actual->draw(); next->draw();
    SDL_RenderPresent(renderer);

    SDL_Delay(65);

    SDL_SetRenderDrawColor(renderer ,COLOR_BACK);
    SDL_RenderClear(renderer);
    bdlines.moveX(-10); // 5 a la izquierda
    bdlines.draw();
    for (auto i : frozenPieces) i->addToX(-10), i->draw(renderer, true);
    actual->draw(); next->draw();
    SDL_RenderPresent(renderer);

    SDL_Delay(72);

    SDL_SetRenderDrawColor(renderer ,COLOR_BACK);
    SDL_RenderClear(renderer);
    bdlines.moveX(7); // 2 a la derecha
    bdlines.draw();
    for (auto i : frozenPieces) i->addToX(7), i->draw(renderer, true);
    actual->draw(); next->draw();
    SDL_RenderPresent(renderer);

    SDL_Delay(85);

    SDL_SetRenderDrawColor(renderer ,COLOR_BACK);
    SDL_RenderClear(renderer);
    bdlines.moveX(-4); // 2 a la izquierda
    bdlines.draw();
    for (auto i : frozenPieces) i->addToX(-4), i->draw(renderer, true);
    actual->draw(); next->draw();
    SDL_RenderPresent(renderer);

    SDL_Delay(100);

    SDL_SetRenderDrawColor(renderer ,COLOR_BACK);
    SDL_RenderClear(renderer);
    bdlines.moveX(3); // 1 a la derecha
    bdlines.draw();
    for (auto i : frozenPieces) i->addToX(3), i->draw(renderer, true);
    actual->draw(); next->draw();
    SDL_RenderPresent(renderer);

    bdlines.moveX(-1);
    for (auto i : frozenPieces) i->addToX(-1);

#endif

#ifdef __ANDROID__

    SDL_SetRenderDrawColor(renderer ,COLOR_BACK);
    SDL_RenderClear(renderer);
    bdlines.moveX(13); // 13 a la derecha
    bdlines.draw();
    for (auto i : frozenPieces) i->addToX(13), i->draw(renderer);
    actual->draw(); next->draw();
    SDL_RenderPresent(renderer);


    SDL_SetRenderDrawColor(renderer ,COLOR_BACK);
    SDL_RenderClear(renderer);
    bdlines.moveX(-26); // 13 a la izquierda
    bdlines.draw();
    for (auto i : frozenPieces) i->addToX(-26), i->draw(renderer);
    actual->draw(); next->draw();
    SDL_RenderPresent(renderer);


    SDL_SetRenderDrawColor(renderer ,COLOR_BACK);
    SDL_RenderClear(renderer);
    bdlines.moveX(21); // 8 a la derecha
    bdlines.draw();
    for (auto i : frozenPieces) i->addToX(21), i->draw(renderer);
    actual->draw(); next->draw();
    SDL_RenderPresent(renderer);


    SDL_SetRenderDrawColor(renderer ,COLOR_BACK);
    SDL_RenderClear(renderer);
    bdlines.moveX(-16); // 8 a la izquierda
    bdlines.draw();
    for (auto i : frozenPieces) i->addToX(-16), i->draw(renderer);
    actual->draw(); next->draw();
    SDL_RenderPresent(renderer);


    SDL_SetRenderDrawColor(renderer ,COLOR_BACK);
    SDL_RenderClear(renderer);
    bdlines.moveX(13); // 5 a la derecha
    bdlines.draw();
    for (auto i : frozenPieces) i->addToX(13), i->draw(renderer);
    actual->draw(); next->draw();
    SDL_RenderPresent(renderer);


    SDL_SetRenderDrawColor(renderer ,COLOR_BACK);
    SDL_RenderClear(renderer);
    bdlines.moveX(-10); // 5 a la izquierda
    bdlines.draw();
    for (auto i : frozenPieces) i->addToX(-10), i->draw(renderer);
    actual->draw(); next->draw();
    SDL_RenderPresent(renderer);


    SDL_SetRenderDrawColor(renderer ,COLOR_BACK);
    SDL_RenderClear(renderer);
    bdlines.moveX(7); // 2 a la derecha
    bdlines.draw();
    for (auto i : frozenPieces) i->addToX(7), i->draw(renderer);
    actual->draw(); next->draw();
    SDL_RenderPresent(renderer);


    SDL_SetRenderDrawColor(renderer ,COLOR_BACK);
    SDL_RenderClear(renderer);
    bdlines.moveX(-4); // 2 a la izquierda
    bdlines.draw();
    for (auto i : frozenPieces) i->addToX(-4), i->draw(renderer);
    actual->draw(); next->draw();
    SDL_RenderPresent(renderer);


    SDL_SetRenderDrawColor(renderer ,COLOR_BACK);
    SDL_RenderClear(renderer);
    bdlines.moveX(3); // 1 a la derecha
    bdlines.draw();
    for (auto i : frozenPieces) i->addToX(3), i->draw(renderer);
    actual->draw(); next->draw();
    SDL_RenderPresent(renderer);

    bdlines.moveX(-1);
    for (auto i : frozenPieces) i->addToX(-1);

#endif
}

/* ----------  LOGICA  ------------------------------- */

void TetrisBoard::logic(direction direc) {

    static bool linesErased = false;

    if (humanMovePiece(direc)) {

#ifdef __ANDROID__
        //SDL_Log("\nHuman move piece done.");
#endif
        delay_t = DELAY_T / 6;
    }

    else {

#ifdef __ANDROID__
        //SDL_Log("\nAutomatic move piece done.");
#endif
        if (pieces_over_erased != null_Iterator)
            shake();
        
        movePcs_overErased();
        eraseLines();

        if (actual->isAdjuntTo_DownFloor(frozenPieces))
            moveActualTo_frozenPieces();

        checkGameOverState();
        actual->move(Down);
        delay_t = DELAY_T - (lines_Made * 4);
    }
}

void TetrisBoard::_debug_streamOutFrozenPcs() const {

    using namespace std;

    if (!frozenPieces.empty()) {

        cout << "Floor is:" << endl;

        for (Tetris_Rect *i : frozenPieces)
            cout << *i;
    }

    else
        cout << "Floor is empty." << endl;
}

bool TetrisBoard::humanMovePiece(direction dir) {

    switch (dir) {

        case Left:

            if (!actual->isAdjuntTo_LWallsOrPcs(frozenPieces))
                actual->move(Left);
            return true;

        case Right:

            if (!actual->isAdjuntTo_RWallsOrPcs(frozenPieces))
                actual->move(Right);
            return true;

        case Down:

            if (!actual->isAdjuntTo_DownFloor(frozenPieces))
                actual->move(Down);
            return true;

        case Up:

            actual->rotate(frozenPieces);
            return true;

        case None:
        default:
            return false;

    }
}

void TetrisBoard::moveActualTo_frozenPieces(){

    for (Tetris_Rect *i : actual->get_TetrisSquares())
        frozenPieces.push_back(i);

    actual = next;

        actual->changeWaitToActual();

    next = new Tetris_Shape(renderer, true);

    /* Para eliminar posteriormente las líneas hay que ordenar de menor a mayor
     * las Y y despues encontrar en el vector 10 coincidencias de Y para poder
     * eliminarlas, (se intentó antes ordenar por medio de una algoritmo que
     * comparaba ambas X e Y, pero no se logró implementar correctamente, y en
     * vista de que no es necesario tener ordenadas las X para poder borrar una
     * línea seguida, se decidió solamente ordenar las Y, lo cual sucede correc-
     * tamente en todos los casos) */
    std::sort(frozenPieces.rbegin(), frozenPieces.rend(), Tetris_Rect::cmpY);

    checkIfLines();
}

/*
 * Habiendo ordenado por Y las frozenPieces, buscar la primera incidencia
 * de cada Y, comparar la Y de la primera incidencia con 9 posiciones mas
 * adelante y si coincide en dado valor, existe una línea y así ambos
 * iteradores se pueden pasar como un rango...
 */
void TetrisBoard::checkIfLines() {

    if (frozenPieces.size() > 10) {

        std::vector<Tetris_Rect *>::iterator i = frozenPieces.begin(),
                                             j = frozenPieces.end();

        for (int yVal = BOARD_HEIGHT; yVal > 0; yVal -= UNIT) {

            double count = std::count_if(i, j, [yVal](Tetris_Rect *it)
                                                     {return it->getY() == yVal;});

            if (count == 10) {

                for(auto tmp = i; tmp != i + 10; ++tmp)
                    (*tmp)->setErased();

                pieces_over_erased = (i += 10);
                ++linesToMoveOverPieces;
            }

            else
                i = std::find_if(i, j, [yVal](Tetris_Rect *it)
                                             { return it->getY() != yVal; });
        }
    }
}

/*
 * Checar si es lo suficientemente rápido usar
 * la función erase() y si no crear otro vector
 * a partir del primero y reasignar las partes
 * necesarias
 */
void TetrisBoard::eraseLines() {

    while (std::any_of(frozenPieces.begin(), frozenPieces.end(),
                       [](Tetris_Rect * rct){ return rct->isErased();})) {

        frozenPieces.erase(std::find_if(frozenPieces.begin(), frozenPieces.end(),
                                         [](Tetris_Rect * rct){ return rct->isErased();}));
    }
}

bool TetrisBoard::movePcs_overErased() {

    if (pieces_over_erased != null_Iterator) {

        for (; pieces_over_erased != frozenPieces.end(); ++pieces_over_erased)
            (*pieces_over_erased)->addToY(UNIT * linesToMoveOverPieces);

        lines_Made += linesToMoveOverPieces;
        linesToMoveOverPieces = 0;

        pieces_over_erased = null_Iterator;

        return true;
    }

    return false;
}

void TetrisBoard::checkGameOverState() {

    if (frozenPieces.size() > 15) {

        if (std::any_of(frozenPieces.begin(), frozenPieces.end(),
                        [](Tetris_Rect *rct) { return rct->getY() == PY_START; }))
            gameState = false;
    }
}


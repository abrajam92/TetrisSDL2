//
// Created by Abraham Cruz Santibañez on 06/01/17.
//

#ifndef SDL_PROJECT2_TETRIS_BOARD_HH
#define SDL_PROJECT2_TETRIS_BOARD_HH

#include "Tetris_Shape.h"

#define DEBUGGING
#undef DEBUGGING

class BoardLines{

    struct point{
        Uint16 x, y;
    };

    SDL_Renderer *renderer;

    point in1, in2, in3, in4,
            out1, out2, out3, out4;

    std::array<Uint32, 9> xDottedLinePts;
    Uint8 interval;

public:

    BoardLines(SDL_Renderer *rnd) : renderer(rnd) {

        // Lineas afuera de tablero
        out1.x = BOARD_X_LEFT_GUARD - 5;
        out1.y = 0;
        out2.x = BOARD_X_LEFT_GUARD - 5;
        out2.y = BOARD_HEIGHT + 5;
        out3.x = BOARD_X_RIGHT_GUARD + 5;
        out3.y = BOARD_HEIGHT + 5;
        out4.x = BOARD_X_RIGHT_GUARD + 5;
        out4.y = 0;

        // Lineas adentro de tablero
        in1.x = BOARD_X_LEFT_GUARD;
        in1.y = 0;
        in2.x = BOARD_X_LEFT_GUARD;
        in2.y = BOARD_HEIGHT + 1;
        in3.x = BOARD_X_RIGHT_GUARD;
        in3.y = BOARD_HEIGHT + 1;
        in4.x = BOARD_X_RIGHT_GUARD;
        in4.y = 0;

        interval = UNIT - 1;

        xDottedLinePts = {(Uint32)BOARD_X_LEFT_GUARD + UNIT,
                          (Uint32)BOARD_X_LEFT_GUARD + (UNIT * 2),
                          (Uint32)BOARD_X_LEFT_GUARD + (UNIT * 3),
                          (Uint32)BOARD_X_LEFT_GUARD + (UNIT * 4),
                          (Uint32)BOARD_X_LEFT_GUARD + (UNIT * 5),
                          (Uint32)BOARD_X_LEFT_GUARD + (UNIT * 6),
                          (Uint32)BOARD_X_LEFT_GUARD + (UNIT * 7),
                          (Uint32)BOARD_X_LEFT_GUARD + (UNIT * 8),
                          (Uint32)BOARD_X_LEFT_GUARD + (UNIT * 9)};
    }

    // Función que se llama para hacer efecto temblor al completar líneas
    void moveX(Sint16 x){

        in1.x += x;
        in2.x += x;
        in3.x += x;
        in4.x += x;
        out1.x += x;
        out2.x += x;
        out3.x += x;
        out4.x += x;

        for (Uint32 i = 0; i < xDottedLinePts.size(); i++) xDottedLinePts[i] += x;
    }

    void draw(){

        /* Bordes de tablero ------------------------------------------------------------------------------- */
        // Lineas del lado izquierdo del tablero
        thickLineRGBA(renderer, out1.x, out1.y, out2.x, out2.y,
                      2, COLOR_BOARD_LINES);

        thickLineRGBA(renderer, in1.x, in1.y, in2.x, in2.y,
                      1, COLOR_BOARD_LINES);

        // Lineas debajo del tablero
        thickLineRGBA(renderer, out2.x, out2.y, out3.x, out3.y,
                      2, COLOR_BOARD_LINES);

        thickLineRGBA(renderer, in2.x, in2.y, in3.x, in3.y,
                      1, COLOR_BOARD_LINES);

        // Lineas del lado derecho del tablero
        thickLineRGBA(renderer, out3.x, out3.y, out4.x, out4.y,
                      2, COLOR_BOARD_LINES);

        thickLineRGBA(renderer, in3.x, in3.y, in4.x, in4.y,
                      1, COLOR_BOARD_LINES);

        /* Lineas adentro de tablero ------------------------------------------------------------------------ */

        // Color de líneas
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0);

        // Verticales
        drawThinPtdLine(renderer, xDottedLinePts[0], 0, interval, (Uint32) BOARD_HEIGHT - 1, true);
        drawThinPtdLine(renderer, xDottedLinePts[1], 0, interval, (Uint32) BOARD_HEIGHT - 1, true);
        drawThinPtdLine(renderer, xDottedLinePts[2], 0, interval, (Uint32) BOARD_HEIGHT - 1, true);
        drawThinPtdLine(renderer, xDottedLinePts[3], 0, interval, (Uint32) BOARD_HEIGHT - 1, true);
        drawThinPtdLine(renderer, xDottedLinePts[4], 0, interval, (Uint32) BOARD_HEIGHT - 1, true);
        drawThinPtdLine(renderer, xDottedLinePts[5], 0, interval, (Uint32) BOARD_HEIGHT - 1, true);
        drawThinPtdLine(renderer, xDottedLinePts[6], 0, interval, (Uint32) BOARD_HEIGHT - 1, true);
        drawThinPtdLine(renderer, xDottedLinePts[7], 0, interval, (Uint32) BOARD_HEIGHT - 1, true);
        drawThinPtdLine(renderer, xDottedLinePts[8], 0, interval, (Uint32) BOARD_HEIGHT - 1, true);

    }
};

class Touch_Keys {

public:

    SDL_Window *wind;
    SDL_Renderer *rnd;

    sdl::Rect U, D, L, R;

    Touch_Keys(SDL_Renderer *rend) : rnd(rend) {

        U = sdl::Rect( 200, BOARD_HEIGHT + 30, UNIT * 4, UNIT * 4, 255, 0, 0, 255);
        D = sdl::Rect( 200, BOARD_HEIGHT + 290, UNIT * 4, UNIT * 4, 255, 0, 0, 255);
        L = sdl::Rect( 70, BOARD_HEIGHT + 160, UNIT * 4, UNIT * 4, 255, 0, 0, 255);
        R = sdl::Rect( 330, BOARD_HEIGHT + 160, UNIT * 4, UNIT * 4, 255, 0, 0, 255);

        U.setColor(150, 110, 130, 42);
        D.setColor(150, 110, 130, 42);
        L.setColor(150, 110, 130, 42);
        R.setColor(150, 110, 130, 42);
    }

    void draw(){

        U.fill_GFXRoundedRect_on_rend(rnd, 8);
        D.fill_GFXRoundedRect_on_rend(rnd, 8);
        L.fill_GFXRoundedRect_on_rend(rnd, 8);
        R.fill_GFXRoundedRect_on_rend(rnd, 8);
    }
};

class TetrisBoard {

public:

    Uint32 startFrame_t,
           finalFrame_t,
           lastFrame_t;
private:

    SDL_Renderer *renderer;

    Tetris_Shape *actual;
    Tetris_Shape *next;

    BoardLines bdlines;

    bool gameState;
    bool pauseState;

    int delay_t;

    int lines_Made, linesToMoveOverPieces;

    /**
     * \brief Se refiere a las Tetris_Shape que caen y quedan
     * congeladas en el tablero. */
    std::vector<Tetris_Rect *> frozenPieces;

    std::vector<Tetris_Rect *>::iterator pieces_over_erased,
    /**
     * \Brief C++ no tiene asignación nula a iteradores, así que
     * hay que crear la asignación nula adecuada al contenedor y
     * tipo contenido para poder hacer comparaciones, como aquí
     * que cree un null_Iterator para iteradores a
     * std::vector<Tetris_Rect *>.
     */
                                            null_Iterator;



    /* ----------  Constructores ------------------------- */

public:

    /** Constructor */
    TetrisBoard(SDL_Renderer *rnd);



    /* ----------  Funciones que dibujan  ---------------- */

public:

    void draw();

private:

    void drawBoard();

    void drawWaitingArea();

    void shake();



    /* ----------  LOGICA  ------------------------------- */

public:

    void logic(direction direc);

    void _debug_streamOutFrozenPcs() const;

private:

    bool humanMovePiece(direction dir);

    void moveActualTo_frozenPieces();

    void checkIfLines();

    void eraseLines();

    bool movePcs_overErased();

    void checkGameOverState();


    /* ----------  Setters y getters  -------------------- */

public:

    inline bool getGameState() const { return gameState;}

    inline void setGameState(bool val) {gameState = val;}

    inline int get_Delay() const { return delay_t; }

};

#endif //SDL_PROJECT2_TETRIS_BOARD_HH
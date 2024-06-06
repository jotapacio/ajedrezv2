//board.h: interface for the board class: contains only the logic of the game

#ifndef __TABLERO_H__
#define __TABLERO_H__

#include <iostream>
#include "piece.h"


using namespace std;

class Tablero {
private:
    const int filas;
    const int columnas;
    Pieza** tab;

public:
    Tablero(int filas, int columnas) : filas(filas), columnas(columnas) {
        tab = new Pieza * [filas];
        for (int i = 0; i < filas; i++) {
            tab[i] = new Pieza[columnas];
        }

        // Configurar posición inicial de las piezas
        tab[0][0].setCasilla(0, 0, Pieza::TORRE_NEGRA);
        tab[0][1].setCasilla(0, 1, Pieza::PIEZA_NEGRA);
        tab[0][2].setCasilla(0, 2, Pieza::REY_NEGRO);
        tab[0][3].setCasilla(0, 3, Pieza::TORRE_NEGRA);
        tab[1][0].setCasilla(1, 0, Pieza::PEON_NEGRO);
        tab[1][1].setCasilla(1, 1, Pieza::PEON_NEGRO);
        tab[1][2].setCasilla(1, 2, Pieza::PEON_NEGRO);
        tab[1][3].setCasilla(1, 3, Pieza::PEON_NEGRO);

        tab[filas - 1][0].setCasilla(filas - 1, 0, Pieza::TORRE_BLANCA);
        tab[filas - 1][1].setCasilla(filas - 1, 1, Pieza::PIEZA_BLANCA);
        tab[filas - 1][2].setCasilla(filas - 1, 2, Pieza::REY_BLANCO);
        tab[filas - 1][3].setCasilla(filas - 1, 3, Pieza::TORRE_BLANCA);
        tab[filas - 2][0].setCasilla(filas - 2, 0, Pieza::PEON_BLANCO);
        tab[filas - 2][1].setCasilla(filas - 2, 1, Pieza::PEON_BLANCO);
        tab[filas - 2][2].setCasilla(filas - 2, 2, Pieza::PEON_BLANCO);
        tab[filas - 2][3].setCasilla(filas - 2, 3, Pieza::PEON_BLANCO);
    }

    ~Tablero() {
        for (int i = 0; i < filas; i++)
            delete[] tab[i];
        delete[] tab;
    }

    int getFilas() { return filas; }
    int getColumnas() { return columnas; }
    Pieza** getTab() { return tab; }

    pair<int, int> findKing(string color);

    bool isKingInCheck(string color);

    bool movimientoPosible(int from_x, int from_y, int to_x, int to_y);

    bool movePiece(int from_x, int from_y, int to_x, int to_y);
};

#endif


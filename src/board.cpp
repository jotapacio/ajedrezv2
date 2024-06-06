//board.cpp
#include "board.h"
#include "piece.h"
#include <iostream>

using namespace std;

pair<int, int> Tablero::findKing(string color) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (tab[i][j].getColor() == color &&
                (tab[i][j].getTipo() == Pieza::REY_BLANCO || tab[i][j].getTipo() == Pieza::REY_NEGRO)) {
                return { i, j };
            }
        }
    }
    return { -1, -1 };  // No se encontró el rey
}

bool Tablero::isKingInCheck(string color) { //Evalua el jaque al rey del color que se ponga aqui
    pair<int, int> kingPosition = findKing(color);  // Encuentra la posición del rey
    if (kingPosition.first == -1) {  // Si no se encuentra el rey, no puede estar en jaque
        return false;
    }

    string enemyColor = (color == "BLANCO") ? "NEGRO" : "BLANCO";
    // Recorre todas las piezas del tablero
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            Pieza& attackingPiece = tab[i][j];
            if (attackingPiece.getColor() == enemyColor) {
                // Simula el movimiento de cada pieza enemiga hacia la posición del rey
                if (movimientoPosible(i, j, kingPosition.first, kingPosition.second)) {
                    return true;  // Si alguna pieza enemiga puede moverse a la posición del rey, él está en jaque
                }
            }
        }
    }
    return false;
}

bool Tablero::movimientoPosible(int from_x, int from_y, int to_x, int to_y) {
    if (from_x == to_x && from_y == to_y) {
        return false;  // No es válido moverse a la misma casilla.
    }

    Pieza& piezaOrigen = tab[from_x][from_y];
    Pieza& piezaDestino = tab[to_x][to_y];
    Pieza piezaOriginalDestino = piezaDestino;
    Pieza piezaOriginalOrigen = piezaOrigen;

    // Determinar si la pieza se mueve en línea recta o una casilla en cualquier dirección para el rey
    bool movimientoLineaRecta = (from_x == to_x) || (from_y == to_y);
    bool movimientoDiagonal = abs(to_x - from_x) == abs(to_y - from_y);

    bool esFueraDeTablero = (from_x < 0 || from_x >= filas || from_y < 0 || from_y >= columnas || to_x < 0 || to_x >= filas || to_y < 0 || to_y >= columnas);
    if (esFueraDeTablero) return false;

    bool esRey = ((piezaOrigen.getTipo() == Pieza::REY_BLANCO) || (piezaOrigen.getTipo() == Pieza::REY_NEGRO));
    bool esReina = ((piezaOrigen.getTipo() == Pieza::PIEZA_BLANCA) || (piezaOrigen.getTipo() == Pieza::PIEZA_NEGRA));
    bool esTorre = ((piezaOrigen.getTipo() == Pieza::TORRE_BLANCA) || (piezaOrigen.getTipo() == Pieza::TORRE_NEGRA));
    bool esPeonNegro = (piezaOrigen.getTipo() == Pieza::PEON_NEGRO);
    bool esPeonBlanco = (piezaOrigen.getTipo() == Pieza::PEON_BLANCO);
    bool esPeon = ((piezaOrigen.getTipo() == Pieza::PEON_BLANCO) || (piezaOrigen.getTipo() == Pieza::PEON_NEGRO));
    bool esNegra = (piezaOrigen.getColor() == "NEGRO");

    // Calcular el paso de incremento para verificar el camino bloqueado
    int dx = (to_x - from_x == 0) ? 0 : (to_x - from_x > 0 ? 1 : -1);
    int dy = (to_y - from_y == 0) ? 0 : (to_y - from_y > 0 ? 1 : -1);

    int x = from_x + dx;
    int y = from_y + dy;

    if (esPeonBlanco) {
        //      cout << "Entra en esPeonBlanco" << endl;
        if (from_x <= to_x) {  // Los peones blancos solo pueden moverse hacia abajo en la matriz (incrementando x)
            return false;
        }

        if (movimientoDiagonal) {  // Movimiento diagonal para capturar
            if (((piezaDestino.getColor() == piezaOrigen.getColor()) || piezaDestino.getTipo() == Pieza::CASILLA_VACIA) || abs(to_x - from_x) > 1) {
                return false;  // No se puede mover diagonalmente a menos que sea para capturar una pieza enemiga
            }
        }
        else if (dy == 0 && dx == -1) {  // Movimiento vertical hacia adelante
            if (piezaDestino.getTipo() != Pieza::CASILLA_VACIA) {
                return false;  // No puede avanzar a una casilla no vacía
            }
        }
        else {
            return false;  // Otros movimientos son inválidos
        }
    }
    else if (esPeonNegro) {
        if (from_x >= to_x) {  // Los peones negros solo pueden moverse hacia arriba en la matriz (decrementando x)
            return false;
        }

        if (movimientoDiagonal) {  // Movimiento diagonal para capturar
            if (((piezaDestino.getColor() == piezaOrigen.getColor()) || piezaDestino.getTipo() == Pieza::CASILLA_VACIA) || abs(to_x - from_x) > 1) {
                return false;  // No se puede mover diagonalmente a menos que sea para capturar una pieza enemiga
            }
        }
        else if (dy == 0 && dx == 1) {  // Movimiento vertical hacia adelante
            if (piezaDestino.getTipo() != Pieza::CASILLA_VACIA) {
                return false;  // No puede avanzar a una casilla no vacía
            }
        }
        else {
            return false;  // Otros movimientos son inválidos
        }
    }

    if (esTorre) {
        //        cout << "Entra en esTorre" << endl;
        if (movimientoLineaRecta == false) {
            return false;        // Las torres sólo pueden moverse en línea recta.
        }
    }

    if (esRey) {
        if (abs(to_x - from_x) > 1 || abs(to_y - from_y) > 1) {
            return false;  // El rey solo puede moverse una casilla en cualquier dirección.
        }
    }

    if (esReina) {
        // Movimiento diagonal para piezas genéricas no reyes
        if (!movimientoLineaRecta && abs(to_x - from_x) != abs(to_y - from_y)) {
            return false;
        }
    }

    // Verifica si el camino está libre, excepto para el rey que mueve solo una casilla
    if (!esRey || (esRey && (abs(to_x - from_x) > 1 || abs(to_y - from_y) > 1))) {
        while (x != to_x || y != to_y) {
            if (tab[x][y].getTipo() != Pieza::CASILLA_VACIA) {
                return false;  // Camino bloqueado
            }
            x += dx;
            y += dy;
        }
    }

    // Verifica la celda de destino para prevenir captura de piezas del mismo equipo (EN NEGRAS)
    if (piezaDestino.getTipo() != Pieza::CASILLA_VACIA) {
        if (piezaDestino.getColor() == piezaOrigen.getColor()) {
            return false;  // No puedes capturar tus propias piezas, incluyendo al propio rey
        }
    }

    return true;

}

bool Tablero::movePiece(int from_x, int from_y, int to_x, int to_y) {

    if (from_x == to_x && from_y == to_y) {
        cout << "Una pieza no puede moverse a su misma casilla" << endl;
        return false;  // No es válido moverse a la misma casilla.
    }

    Pieza& piezaOrigen = tab[from_x][from_y];
    Pieza& piezaDestino = tab[to_x][to_y];
    Pieza piezaOriginalDestino = piezaDestino;
    Pieza piezaOriginalOrigen = piezaOrigen;


    // Determinar si la pieza se mueve en línea recta o una casilla en cualquier dirección para el rey
    bool movimientoLineaRecta = (from_x == to_x) || (from_y == to_y);
    bool movimientoDiagonal = abs(to_x - from_x) == abs(to_y - from_y);

    bool esFueraDeTablero = (from_x < 0 || from_x >= filas || from_y < 0 || from_y >= columnas || to_x < 0 || to_x >= filas || to_y < 0 || to_y >= columnas);
    if (esFueraDeTablero) return false;

    bool esRey = ((piezaOrigen.getTipo() == Pieza::REY_BLANCO) || (piezaOrigen.getTipo() == Pieza::REY_NEGRO));
    bool esReina = ((piezaOrigen.getTipo() == Pieza::PIEZA_BLANCA) || (piezaOrigen.getTipo() == Pieza::PIEZA_NEGRA));
    bool esTorre = ((piezaOrigen.getTipo() == Pieza::TORRE_BLANCA) || (piezaOrigen.getTipo() == Pieza::TORRE_NEGRA));
    bool esPeonNegro = (piezaOrigen.getTipo() == Pieza::PEON_NEGRO);
    bool esPeonBlanco = (piezaOrigen.getTipo() == Pieza::PEON_BLANCO);
    bool esPeon = ((piezaOrigen.getTipo() == Pieza::PEON_BLANCO) || (piezaOrigen.getTipo() == Pieza::PEON_NEGRO));
    bool esNegra = (piezaOrigen.getColor() == "NEGRO");


    // Calcular el paso de incremento para verificar el camino bloqueado
    int dx = (to_x - from_x == 0) ? 0 : (to_x - from_x > 0 ? 1 : -1);
    int dy = (to_y - from_y == 0) ? 0 : (to_y - from_y > 0 ? 1 : -1);

    int x = from_x + dx;
    int y = from_y + dy;


    if (esPeonBlanco) {
        //      cout << "Entra en esPeonBlanco" << endl;
        if (from_x <= to_x) {  // Los peones blancos solo pueden moverse hacia abajo en la matriz (incrementando x)
            return false;
        }

        if (movimientoDiagonal) {  // Movimiento diagonal para capturar
            if (((piezaDestino.getColor() == piezaOrigen.getColor()) || piezaDestino.getTipo() == Pieza::CASILLA_VACIA) || abs(to_x - from_x) > 1) {
                return false;  // No se puede mover diagonalmente a menos que sea para capturar una pieza enemiga
            }
        }
        else if (dy == 0 && dx == -1) {  // Movimiento vertical hacia adelante
            if (piezaDestino.getTipo() != Pieza::CASILLA_VACIA) {
                return false;  // No puede avanzar a una casilla no vacía
            }
        }
        else {
            return false;  // Otros movimientos son inválidos
        }
    }
    else if (esPeonNegro) {
        if (from_x >= to_x) {  // Los peones negros solo pueden moverse hacia arriba en la matriz (decrementando x)
            return false;
        }

        if (movimientoDiagonal) {  // Movimiento diagonal para capturar
            if (((piezaDestino.getColor() == piezaOrigen.getColor()) || piezaDestino.getTipo() == Pieza::CASILLA_VACIA) || abs(to_x - from_x) > 1) {
                return false;  // No se puede mover diagonalmente a menos que sea para capturar una pieza enemiga
            }
        }
        else if (dy == 0 && dx == 1) {  // Movimiento vertical hacia adelante
            if (piezaDestino.getTipo() != Pieza::CASILLA_VACIA) {
                return false;  // No puede avanzar a una casilla no vacía
            }
        }
        else {
            return false;  // Otros movimientos son inválidos
        }
    }

    if (esTorre) {
        //        cout << "Entra en esTorre" << endl;
        if (movimientoLineaRecta == false) {
            cout << "Las torres solo pueden moverse en lineas rectas" << endl;
            return false;        // Las torres sólo pueden moverse en línea recta.
        }
    }

    if (esRey) {
        //        cout << "Entra en esRey" << endl;
        if (abs(to_x - from_x) > 1 || abs(to_y - from_y) > 1) {
            cout << "Los reyes solo peden moverse una casilla" << endl;
            return false;  // El rey solo puede moverse una casilla en cualquier dirección.
        }
    }



    if (esReina) {
        //        cout << "Entra en esReina" << endl;

                // Movimiento diagonal para piezas genéricas no reyes
        if (!movimientoLineaRecta && abs(to_x - from_x) != abs(to_y - from_y)) {
            cout << "Las reinas solo se pueden mover en linea recta o diagonal" << endl;
            return false;
        }
    }

    // Verifica si el camino está libre, excepto para el rey que mueve solo una casilla
    if (!esRey || (esRey && (abs(to_x - from_x) > 1 || abs(to_y - from_y) > 1))) {
        while (x != to_x || y != to_y) {
            //          cout << "x= " << x << ", y= " << y << endl;
            if (tab[x][y].getTipo() != Pieza::CASILLA_VACIA) {
                //              cout << "Camino bloqueado" << endl;
                return false;  // Camino bloqueado
            }
            x += dx;
            y += dy;
        }
    }

    // Verifica la celda de destino para prevenir captura de piezas del mismo equipo (EN NEGRAS)
    if (piezaDestino.getTipo() != Pieza::CASILLA_VACIA) {
        if (piezaDestino.getColor() == piezaOrigen.getColor()) {
            cout << "Las piezas de un mismo color no se pueden comer" << endl;
            return false;  // No puedes capturar tus propias piezas, incluyendo al propio rey
        }
    }

    //       cout << "La pieza que se va a mover es " << piezaOrigen.getTipo() << " de color " << piezaOrigen.getColor()
     //          << " y la casilla de destino tiene una pieza " << piezaDestino.getTipo() << " de color " << piezaDestino.getColor() << endl;


    if (piezaDestino.getColor() != piezaOrigen.getColor()) { //MOVIMIENTO 
        // Realiza el movimiento
        tab[to_x][to_y] = piezaOrigen;
        tab[from_x][from_y] = Pieza(); 
        
        cout << "Movimiento realizado por una pieza de color " << tab[to_x][to_y].getColor() << endl;

        if (isKingInCheck(tab[to_x][to_y].getColor())) {
            cout << "No puedes hacer ese movimiento: Pondrias al rey " << tab[to_x][to_y].getColor() << " en Jaque" << endl;
            tab[to_x][to_y] = piezaOriginalDestino;  // Restaura la pieza original en la posición destino
            tab[from_x][from_y] = piezaOriginalOrigen;
            cout << "Movimiento deshecho" << endl;
            return false;
        }

        if (!isKingInCheck(tab[from_x][from_y].getColor())) {
            cout << "Movimiento realizado por una pieza de color " << tab[from_x][from_y].getColor() << endl;
            return true;
        }
    }

    cout << "Captura inválida de una pieza del mismo equipo" << endl;
    return false;  // Captura inválida de una pieza del mismo equipo
}

#ifndef __PIECE_H__
#define __PIECE_H__

#include <iostream>
#include "gltools.h"
#include "glut.h"
#include<string>
#include"ETSIDI.h"

using namespace std;

class Object {
public:
    enum tipo_t { PIEZA_BLANCA, PIEZA_NEGRA, TORRE_BLANCA, TORRE_NEGRA, REY_BLANCO, REY_NEGRO, PEON_BLANCO, PEON_NEGRO, CASILLA_VACIA };
    virtual void getNumeroCasilla(int& x, int& y) = 0;
    virtual tipo_t getTipo() = 0;
    virtual string getColor() = 0;
};

class Pieza : public Object {
protected:
    int x;
    int y;
    tipo_t tipo;
    string color;
public:
//    ETSIDI::Sprite torreBlanca{ "C:/Users/Daniel Sato/source/repos/glut_boardgame/imagenes/torreblanca.png",0,0,20,20 }; //Deberia ir en private
    Pieza() : x(-1), y(-1), tipo(CASILLA_VACIA) {}
    void setCasilla(int x, int y, tipo_t t) {
        this->x = x;
        this->y = y;
        this->tipo = t;
        if (t == TORRE_BLANCA || t == REY_BLANCO || t == PIEZA_BLANCA || t == PEON_BLANCO) {
            this->color = "BLANCO";
        }
        else if (t == TORRE_NEGRA || t == REY_NEGRO || t == PIEZA_NEGRA || t == PEON_NEGRO) {
            this->color = "NEGRO";
        }
        else {
            this->color = "VACIO";  // Para las casillas vacías o cualquier otra situación
        }
    }
    virtual void getNumeroCasilla(int& x, int& y) { x = this->x; y = this->y; }
    virtual tipo_t getTipo() { return tipo; }
    virtual string getColor() { return color; }
};

#endif

//boardgl.h: contains the painting functions for the board
#ifndef __BOARD_GL_H__
#define __BOARD_GL_H__

#include <string>
#include <vector>
#include "board.h"
#include"ETSIDI.h"

//AHORA SE COMEN LAS PIEZAS

//enums to eliminate dependency of glut
enum { MOUSE_LEFT_BUTTON, MOUSE_MIDDLE_BUTTON, MOUSE_RIGHT_BUTTON };
enum { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT };

using namespace std;

class TableroGL {

public:
	bool selectedPiece = false;
	int selected_x, selected_y;
	TableroGL(Tablero* pb) :m_tablero(pb) {
		width = 0.15;				//width of each cell in the grid
		filas = pb->getFilas();		//Grid filasxcolumnas
		columnas = pb->getColumnas();
		dist = 2;					//distance of viewpoint from center of the board
		center_z = 0;
	}
	virtual ~TableroGL() {}

	//Initizalization
	void init();						//enable lights

	
	//Event managers
	void Draw();
	void DrawGrid();
	void DrawCell(int i, int j);
	void KeyDown(unsigned char key);
	void SpecialKeyDown(unsigned char key);
	void MouseButton(int x, int y, int button, bool down, bool shiftKey, bool ctrlKey);
	void moveRandomBlackPiece();
	void timerMoveBlackPiece(int value);

	//info
	void setSize(int filas, int columnas) { this->filas = filas; this->columnas = columnas; }
	int getFilas() { return filas; }
	int getColumnas() { return columnas; }

	//coord
	void cell2center(int cell_x, int cell_y, float& glx, float& gly) {
		//cell_x, cell_y are the board cell coordinates (upper left hand corner is (0,0))
		//glx, gly refer to the center of the cell(cell_x,cell_y) in world coordinates
		glx = cell_y * width + width / 2.0f;
		gly = -cell_x * width - width / 2.0f;
	}

	void world2cell(double x, double y, int& cell_x, int& cell_y) {
		//world coordinates to cell
		cell_x = (int)(abs(y / width));
		cell_y = (int)(x / width);
	}

protected:
	float width;
	int filas, columnas;								 //size 
	Tablero* m_tablero;

	//visualization	
	double center_x, center_y, center_z;
	double dist;

	//mouse	
	int xcell_sel, ycell_sel;			//cell selected with mouse

	//mouse+special-keys combination state events 
	bool controlKey;
	bool shiftKey;
	bool leftButton;
	bool rightButton;
	bool midButton;
};

#endif

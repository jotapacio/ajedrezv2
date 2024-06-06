//Boardgl.cpp
#include "gltools.h"
#include "boardgl.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "glut.h"
#include "piece.h"
#include "board.h"
#include "board.cpp"
#include "ETSIDI.h"

#define DEG2RAD M_PI/180.0


using namespace ETSIDI;
using ETSIDI::getTexture;

void TableroGL::init() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH); // Habilitar el modelo de sombreado suave

	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_NORMALIZE); // Normaliza las normales para que la iluminación sea consistente
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);
}





void TableroGL::DrawGrid() {
	float dist_filas = filas * width;
	float dist_columnas = columnas * width;
	bool isGray = true;  // Comienza con gris

	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			glColor3f(isGray ? 0.2f : 0.8f, isGray ? 0.2f : 0.8f, isGray ? 0.2f : 0.8f);  // Gris o blanco
			glBegin(GL_QUADS);
			glVertex3f(j * width, -i * width, 0);
			glVertex3f((j + 1) * width, -i * width, 0);
			glVertex3f((j + 1) * width, -(i + 1) * width, 0);
			glVertex3f(j * width, -(i + 1) * width, 0);
			glEnd();
			isGray = !isGray;  // Alterna el color para la siguiente casilla
		}
		if (columnas % 2 == 0) isGray = !isGray; // Cambia el inicio de color en la siguiente fila si columnas es par
	}

	GLTools::Color(gltools::BLACK);
	for (int i = 0; i <= filas; i++) {
		glLineWidth(1);
		glBegin(GL_LINES);
		glVertex3f(0, -i * width, 0);
		glVertex3f(dist_columnas, -i * width, 0);
		glEnd();
	}
	for (int j = 0; j <= columnas; j++) {
		glLineWidth(1);
		glBegin(GL_LINES);
		glVertex3f(j * width, 0, 0);
		glVertex3f(j * width, -dist_filas, 0);
		glEnd();
	}

	// Dibuja el borde exterior
	glLineWidth(4);  // Ajusta el grosor del borde si es necesario
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, 0);
	glVertex3f(dist_columnas, 0, 0);
	glVertex3f(dist_columnas, -dist_filas, 0);
	glVertex3f(0, -dist_filas, 0);
	glEnd();
}


void TableroGL::DrawCell(int i, int j) {
	float glx, gly;

	switch (m_tablero->getTab()[i][j].getTipo()) {
	case Object::PIEZA_BLANCA:
		cell2center(i, j, glx, gly);
		glDisable(GL_LIGHTING);
		GLTools::Color(gltools::GREY);
		glTranslatef(glx, gly, 0);
		glutSolidSphere((width / 2.0f) * 0.9f, 50, 50);
		glTranslatef(-glx, -gly, 0);
		glEnable(GL_LIGHTING);
		break;
	case Object::PIEZA_NEGRA:
		cell2center(i, j, glx, gly);
		glDisable(GL_LIGHTING);
		GLTools::Color(gltools::BLACK);
		glTranslatef(glx, gly, 0);
	//	sprite = new ETSIDI::Sprite("C:/Users/Daniel Sato/source/repos/glut_boardgame4/imagenes/reinablanca.png", -2, -2, 1, 1);
	//	sprite->draw();
	//	torrenegra->draw();
		glutSolidSphere((width / 2.0f) * 0.9f, 50, 50);
		glTranslatef(-glx, -gly, 0);
		glEnable(GL_LIGHTING);
		break;
	case Object::TORRE_BLANCA:
		cell2center(i, j, glx, gly);
		glDisable(GL_LIGHTING);
		GLTools::Color(gltools::GREY);
		glTranslatef(glx, gly, 0);
		glutSolidCube((width / 2.0f) * 0.9f);
		glTranslatef(-glx, -gly, 0);
		glEnable(GL_LIGHTING);
		break;
	case Object::TORRE_NEGRA:
		cell2center(i, j, glx, gly);
		glDisable(GL_LIGHTING);
		GLTools::Color(gltools::BLACK);
		glTranslatef(glx, gly, 0);
		glutSolidCube((width / 2.0f) * 0.9f);
		glTranslatef(-glx, -gly, 0);
		glEnable(GL_LIGHTING);
		break;
	case Object::REY_BLANCO:
		cell2center(i, j, glx, gly);
		glDisable(GL_LIGHTING);
		GLTools::Color(gltools::GREEN);
		glTranslatef(glx, gly, 0);
		glutSolidSphere((width / 2.0f) * 0.9f, 50, 50);
		glTranslatef(-glx, -gly, 0);
		glEnable(GL_LIGHTING);
		break;
	case Object::REY_NEGRO:
		cell2center(i, j, glx, gly);
		glDisable(GL_LIGHTING);
		GLTools::Color(gltools::BLUE);
		glTranslatef(glx, gly, 0);
		glutSolidSphere((width / 2.0f) * 0.9f, 50, 50);
		glTranslatef(-glx, -gly, 0);
		glEnable(GL_LIGHTING);
		break;
	case Object::PEON_BLANCO:
		cell2center(i, j, glx, gly);
		glDisable(GL_LIGHTING);
		GLTools::Color(gltools::GREY);
		glTranslatef(glx, gly, 0);
		glutSolidSphere((width / 3.0f) * 0.9f, 50, 50);
		glTranslatef(-glx, -gly, 0);
		glEnable(GL_LIGHTING);
		break;
	case Object::PEON_NEGRO:
		cell2center(i, j, glx, gly);
		glDisable(GL_LIGHTING);
		GLTools::Color(gltools::BLACK);
		glTranslatef(glx, gly, 0);
		glutSolidSphere((width / 3.0f) * 0.9f, 50, 50);
		glTranslatef(-glx, -gly, 0);
		glEnable(GL_LIGHTING);
		break;
	case Object::CASILLA_VACIA:
	default:
		;
	}
}



void TableroGL::Draw() {
	center_x = columnas * width / 2;
	center_y = -filas * width / 2;
	center_z = 0;

	// Borrado de la pantalla    
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(center_x, center_y, dist, center_x, center_y, center_z, 0, 1, 0);

	// Dibuja el tablero y la cuadrícula
	DrawGrid();
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			DrawCell(i, j);
		}
	}

	// Dibuja un rectángulo transparente sobre el tablero para capturar la entrada del mouse con gluUnProject
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GLTools::Color(gltools::WHITE, 1.0f);
	glTranslatef(center_x, center_y, center_z);
	glRectf(columnas * width / 2.0f, filas * width / 2.0f, -columnas * width / 2.0f, -filas * width / 2.0f);
	glTranslatef(-center_x, -center_y, -center_z);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
}


void TableroGL::MouseButton(int x, int y, int button, bool down, bool sKey, bool ctrlKey) {
	/////////////////////////
	// sets state of mouse control buttons + special keys

	/////////
	//computes cell coordinates from mouse coordinates

	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	//finally cell coordinates
	world2cell(posX, posY, xcell_sel, ycell_sel);

	///////////////////////////	
	//capture other mouse events

	if (down) {
		controlKey = ctrlKey;
		shiftKey = sKey;
	}
	else {
		controlKey = shiftKey = false;
	}

	if (button == MOUSE_LEFT_BUTTON)
		leftButton = down;
	else if (button == MOUSE_RIGHT_BUTTON)
		rightButton = down;
	else if (button == MOUSE_MIDDLE_BUTTON)
		midButton = down;
	///////////////////////////

		//***WRITE ACTIONS CONNECTED TO MOUSE STATE HERE

		//print cell coordinates after click
	if (down)
		cout << "(" << xcell_sel << "," << ycell_sel << ")" << endl;
	// Calcula las coordenadas de la celda desde las coordenadas del mundo
	world2cell(posX, posY, xcell_sel, ycell_sel);

	if (down && button == MOUSE_LEFT_BUTTON) {
		if (selectedPiece) {
			// Intenta mover la pieza seleccionada a la nueva ubicación
			bool moveSuccessful = m_tablero->movePiece(selected_x, selected_y, xcell_sel, ycell_sel);
			if (moveSuccessful) {
				moveRandomBlackPiece(); // Mueve una pieza negra automáticamente si la blanca se movió
			}
			selectedPiece = false; // Deselecciona la pieza después de moverla
		}
		else {
			// Selecciona la pieza en la ubicación actual
			selected_x = xcell_sel;
			selected_y = ycell_sel;
			selectedPiece = true;
		}
	}

	glutPostRedisplay();
}

void TableroGL::KeyDown(unsigned char key) {
	//////////////////
	// enlarges or reduces grid by one

	if (key == 's') {
		//** do something
		//if(N<=8) N++;
	}
	if (key == 'a') {
		//** do something
		//if(N>=2) N--;
	}
}

void TableroGL::moveRandomBlackPiece() {

	vector<pair<int, int>> piezasNegras;
	// Encuentra todas las piezas negras, incluyendo torres
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			if (m_tablero->getTab()[i][j].getTipo() == Pieza::PIEZA_NEGRA ||
				m_tablero->getTab()[i][j].getTipo() == Pieza::TORRE_NEGRA ||
				m_tablero->getTab()[i][j].getTipo() == Pieza::REY_NEGRO ||
				m_tablero->getTab()[i][j].getTipo() == Pieza::PEON_NEGRO) {
				piezasNegras.push_back(make_pair(i, j));
			}
		}
	}
	// Intenta mover una pieza negra aleatoriamente hasta que tenga éxito
	while (!piezasNegras.empty()) {
		int randIndex = rand() % piezasNegras.size();
		int from_x = piezasNegras[randIndex].first;
		int from_y = piezasNegras[randIndex].second;

		int attempts = 0;
		bool movimientoHecho = false;
		while (attempts < 8) {
			int dx = rand() % 3 - 1; // -1, 0, 1
			int dy = rand() % 3 - 1; // -1, 0, 1
			if (dx != 0 || dy != 0) {
				int to_x = from_x + dx;
				int to_y = from_y + dy;
				if (to_x >= 0 && to_x < filas && to_y >= 0 && to_y < columnas) {
					if (m_tablero->movePiece(from_x, from_y, to_x, to_y)) {
						movimientoHecho = true;
						break;
					}
				}
			}
			attempts++;
		}

		if (movimientoHecho) {
			break;
		}
		else {
			// Elimina la pieza de la lista si no se pudo mover
			piezasNegras.erase(piezasNegras.begin() + randIndex);
		}
	}
}


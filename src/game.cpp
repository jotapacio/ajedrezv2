#include <iostream>
#include "boardgl.h"
#include "glut.h"
#include "board.h"
//khjohju


//AHORA SE COMEN LAS PIEZAS

#define FILAS	5		//filasxcolumnas grid
#define COLUMNAS 4

/////////////////////////////////
//call back declarations: will be called by glut when registered
void OnDraw(void);
void OnKeyboardDown(unsigned char key, int x, int y);
void OnMouseClick(int button, int state, int x, int y);
void OnTimer(int value);

////////////////////////////////////////////////
//global objects which make the world
Tablero gameboard(FILAS, COLUMNAS);
TableroGL scene(&gameboard);

///////////////////////////////////////////////

int main(int argc, char* argv[]) {

	//GL Initialization stuff
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("MiJuego");


	//Register callbacks
	glutDisplayFunc(OnDraw);
	glutKeyboardFunc(OnKeyboardDown);
	glutMouseFunc(OnMouseClick);
	//glutTimerFunc(25,OnTimer,0);			 //set timer if required, currently not used

	//sets light and perspective
	scene.init();

	//glut takes control
	glutMainLoop();

	return 0;
}

void OnDraw(void) {
	//////////////////////
	//captures drawing event
	//gives control to scene
	scene.Draw();
	glutSwapBuffers();
}

void OnKeyboardDown(unsigned char key, int x_t, int y_t) {
	//////////////////////
	//captures keyboard event
	//gives control to scene
	scene.KeyDown(key);
	glutPostRedisplay();
}

void OnMouseClick(int b, int state, int x, int y) {
	//////////////
	//captures clicks with mouse with or without special keys (CTRL or SHIFT)
	//gives control to board scene
	bool down = (state == GLUT_DOWN);
	int button;
	if (b == GLUT_LEFT_BUTTON) {
		button = MOUSE_LEFT_BUTTON;
	}
	if (b == GLUT_RIGHT_BUTTON) {
		button = MOUSE_RIGHT_BUTTON;
		cout << "MOUSE_RIGHT_BUTTON" << endl;
	}

	int specialKey = glutGetModifiers();
	bool ctrlKey = (specialKey & GLUT_ACTIVE_CTRL) ? true : false;
	bool sKey = specialKey & GLUT_ACTIVE_SHIFT;


	scene.MouseButton(x, y, b, down, sKey, ctrlKey);
	glutPostRedisplay();
}


void OnTimer(int value) {
	//****WRITE TIMER CODE HERE
	if (value == 1) {
		scene.moveRandomBlackPiece();  // Mueve una pieza negra
		glutPostRedisplay();  // Solicita redibujar la ventana
	}
	//sets new timer (do not delete)
//	glutTimerFunc(25,OnTimer,0);
//	glutPostRedisplay();
}

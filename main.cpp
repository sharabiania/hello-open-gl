#include "stdafx.h"
#include "gl/freeglut.h"
#include <iostream>

using namespace std;


GLdouble angleX = 0, angleY = 0;

void displayFunc(void) {
	glClear(GL_COLOR_BUFFER_BIT);


	// Cube
	glPushMatrix();
	glRotated(angleY, 0, 1, 0);
	glRotated(angleX, 1, 0, 0);
	glColor3d(0, 0, 1);
	glutWireCube(0.6);
	glPopMatrix();
	

	// Sphere
	glPushMatrix();
	glColor3d(1, 0, 0);
	glutSolidSphere(0.1, 50, 50);

	glFlush();
}

void processKeys(int key, int x, int y) {
	switch (key)
	{
	case 27:		
		exit(0);
		break;

	case GLUT_KEY_LEFT:
		cout << "left key pressed" << endl;
		angleY -= 10;
		break;

	case GLUT_KEY_RIGHT:
		cout << "right key pressed" << endl;
		angleY += 10;
		break;

	case GLUT_KEY_UP:
		angleX += 10;
		break;

	case GLUT_KEY_DOWN:
		angleX -= 10;
		break;

	}
}


int main(int argc, char** argv) {
	cout << "Hello GL";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	int width = glutGet(GLUT_SCREEN_WIDTH);
	int height = glutGet(GLUT_SCREEN_HEIGHT);
	int windowWidth = width / 2;
	int windowHeight = height / 2;

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((width - windowWidth) / 2, (height - windowHeight) / 2);
	glutCreateWindow("Hello GL");
	glutDisplayFunc(displayFunc);
	glutIdleFunc(displayFunc);

	// glutKeyboardFunc(processKeys);
	glutSpecialFunc(processKeys);

	glutMainLoop();

	cin.get();

	return 0;
}
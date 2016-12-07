#include "stdafx.h"
#include "gl/freeglut.h"
#include <iostream>

using namespace std;


GLdouble angleX = 10, angleY = 20;

class Color {
	
public:
	GLdouble red = 0, green = 0, blue = 0;
	Color(GLdouble red, GLdouble green, GLdouble blue)
		:red(red), green(green), blue(blue)
	{}	
};

class Object {
protected:
	GLdouble vx = 0, vy = 0, vz = 0;
	GLdouble posx = 0, posy = 0, posz = 0;
public:
	virtual void draw() {};
	void setVelocity(GLdouble vx, GLdouble vy, GLdouble vz) {
		this->vx = vx;
		this->vy = vy;
		this->vz = vz;
	}

	void setPosition(GLdouble x, GLdouble y, GLdouble z) {
		posx = x;
		posy = y;
		posz = z;
	}

	virtual void update() {
		
		posx += vx;		
		posy += vy;
		posz += vz;
	}
};

class Ball : public Object {

private:
	double radius;
	GLint slices, stacks;
	Color color;
public:
	Ball(double radius, GLint slices, GLint stacks, Color color)
		:radius(radius), slices(slices), stacks(stacks), color(color)
	{}

	~Ball() {
		cout << "Ball dtor\n";
	}

	void draw() {
		glPushMatrix();
		glColor3d(color.red, color.green, color.blue);
		glTranslated(posx, posy, posz);
		glutWireSphere(radius, slices, stacks);
		glPopMatrix();
	}

	void update() {
		posx += vx;
		posy += vy;
		posz += vz;

		// Collision detection (kind of!)

		if(posx + radius < -0.5) {
			posx = -0.5;
			vx = -vx;
		}

		if (posx + radius > 0.5) {
			posx = 0,5;
			vx = -vx;
		}

		if (posy + radius < -0.5) {
			posy = -0.5;
			vy = -vy;
		}

		if (posy + radius > 0.5) {
			posy = 0.5;
			vy = -vy;
		}

		if (posz + radius < -0.5) {
			posz = -0.5;
			vz = -vz;
		}

		if (posz + radius > 0.5) {
			posz = 0.5;
			vz = -vz;
		}

	}
};

class Scene {
public:
	Ball ball = Ball(0.1, 20, 20, Color(1, 0, 0));;

	Scene() {	
	}

	void update() {
		ball.update();
	}

	void draw() {
		ball.draw();
	}
}scene;

void displayFunction(void) {

	
	glClear(GL_COLOR_BUFFER_BIT);


	// Camera Rotation
	glPushMatrix();
	glRotated(angleY, 0, 1, 0);
	glRotated(angleX, 1, 0, 0);	
	
	glColor3d(0, 0, 1);
	glutWireCube(1);

	scene.draw();

	glPopMatrix();
	glFlush();
}

void timerFunction(int value) {
	scene.update();

	glutPostRedisplay();
	glutTimerFunc(100, timerFunction, 0);

}

GLdouble vx, vy, vz = 0;

void specialFunction(int key, int x, int y) {
	switch (key)
	{
	case 27:
		exit(0);
		break;

	case GLUT_KEY_LEFT:
		cout << "left key pressed" << endl;
		vx -= 0.1;		
		scene.ball.setVelocity(vx, vy, vz);
		break;

	case GLUT_KEY_RIGHT:
		cout << "right key pressed" << endl;
		vx += 0.15;
		vy += 0.1;
		vz += 0.05;
		scene.ball.setVelocity(vx, vy, vz);
		break;

	case GLUT_KEY_UP:
		angleY += 10;
		break;

	case GLUT_KEY_DOWN:
		angleY -= 10;
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
	glutDisplayFunc(displayFunction);
	glutTimerFunc(100, timerFunction, 0);

	// glutKeyboardFunc(processKeys);
	glutSpecialFunc(specialFunction);

	glutMainLoop();

	cin.get();

	return 0;
}
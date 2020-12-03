#pragma once
#include <GL/freeglut.h>


class Camera {
private:
	double x, y, z;
	double angle_x, angle_y, dist;
public:
	Camera() : x{ 0 }, y{ 0 }, z{ 0 }, angle_x{ 0 }, angle_y{ 0 }, dist{ 0 } {
	
	}

	Camera(double x, double y, double z) : x{ x }, y{ y }, z{ z }, angle_x{ 0 }, angle_y{ 0 }, dist{ z } {
		int window_w = glutGet(GLUT_WINDOW_WIDTH);
		int window_h = glutGet(GLUT_WINDOW_HEIGHT);

		//Initialize the camera (perspective)
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90, (double)window_w / (double)window_h, 1.0, 1000.0);
		gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
		glMatrixMode(GL_MODELVIEW);
	}
	
	//Rotates the camera about the origin by x and y degrees.
	void rotate(double xDeg, double yDeg) {
		angle_x += xDeg;
		angle_y += yDeg;

		x = dist * sin(angle_y) * cos(angle_x);
		y = dist * sin(angle_y) * sin(angle_x);
		z = dist * cos(angle_y);

		std::cout << x << ", " << y << ", " << z << std::endl;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotated(angle_x, 0.0, 1.0, 0.0);
	}
};
/*==================================================================================================
 COURSE:				  CSC 525/625
 ASSIGNMENT:			  Project 3
 PROGRAMMER:			  
 LAST MODIFIED DATE:	  11/29/2020
 DESCRIPTION:			  3D Interactive Advertisement
 NOTE:					  
 FILES:					  Project3.cpp, (ComputerGraphicsProj3.sln, ...)
 IDE/COMPILER:			  Microsoft Visual Studio 2019
 INSTRUCTION FOR COMPILATION AND EXECUTION:
		1.		Double click on ComputerGraphicsProj3.sln	to OPEN the project
		2.		Press Ctrl+F7 								to COMPILE
		3.		Press Ctrl+F5 								to EXECUTE
==================================================================================================*/
#include <iostream>
#include <GL/freeglut.h> // include GLUT library

#include "Camera.h"
#include "DebugUtils.h"
#include "MathUtils.h"

void mainWindowInit();
void helpWindowInit(); 

void menuInit();

void myDisplayCallback();
void helpDisplayCallback();

void keyboardCallback(unsigned char, int, int);
void helpKeyboardCallback(unsigned char, int, int);

void specialFuncCallback(int, int, int);
void mouseCallback(int, int, int, int);
void motionCallback(int, int);
void reshapeCallback(int, int);

constexpr int WINDOW_SIZE[]{ 800, 600 };
constexpr int HELP_SIZE[]{ 400, 400 };
int mainWindow, helpWindow;
int mouse_x, mouse_y;
int target_x{ 0 }, target_y{ 0 };

bool mouseDown = false;
Camera camera;

int main(int argc, char** argv) {

	glutInit(&argc, argv); // initialization

	glutInitWindowSize(WINDOW_SIZE[0], WINDOW_SIZE[1]); // specify a window size
	glutInitWindowPosition(0, 0);						// specify a window position
	mainWindow = glutCreateWindow("GLUT 3D Advertisement");	// create a titled window
	mainWindowInit(); // specify some settings
	menuInit();

	camera = Camera(0, 50, 200);

	glutDisplayFunc(myDisplayCallback); // register a callback
	glutKeyboardFunc(keyboardCallback);
	glutSpecialFunc(specialFuncCallback);
	glutMouseFunc(mouseCallback);
	glutMotionFunc(motionCallback);
	glutReshapeFunc(reshapeCallback);

	//TODO: This is old code for making a help window, I commented it out for now
	/*
	glutInitWindowSize(HELP_SIZE[0], HELP_SIZE[1]);
	glutInitWindowPosition(200, 50);
	helpWindow = glutCreateWindow("GLUT 3D Advertisement Help");
	helpWindowInit(); // specify some settings

	glutDisplayFunc(helpDisplayCallback);
	glutKeyboardFunc(helpKeyboardCallback);
	*/

	glutMainLoop(); // get into an infinite loop

	return 1; // something wrong happened
}

//***********************************************************************************
// Main Window and Menu Functionality
//***********************************************************************************
void mainWindowInit() {
	glClearColor(1, 1, 1, 1);  // specify a background clor: white
	
	//Specify perspective projection. Aspect ratio is the same ratio of the current (init) window width and height,
	//near plane is just in front of camera, and far plane is a sizeable 1000.0 units away from the camera's origin
	
	glEnable(GL_DEPTH_TEST);

	//Initialize the menu used for the main window
	menuInit();
}

void menuInit() {

}

void myDisplayCallback() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//TODO: Perform all drawing operations

	//DebugUtils::draw_axes();
	DebugUtils::draw_grid();

	glFlush();
}

void keyboardCallback(unsigned char, int, int) {
	//Not needed currently - Do we have any uses for keyboard callbacks in the main 3D advertisement window?
}

void specialFuncCallback(int, int, int) {
	//Not needed currently
}

void mouseCallback(int button, int state, int x, int y) {
	//TODO: Daniel make this let the user change orientation of camera
	mouseDown = (button == GLUT_LEFT && state == GLUT_DOWN);
	mouse_x = x;
	mouse_y = y;
}

void motionCallback(int x, int y) {
	//TODO: Daniel
	int dx = mouse_x - x;
	int dy = mouse_y - y;
	mouse_x = x;
	mouse_y = y;

	target_x = dx;// Maths::lerp(target_x, target_x + dx, 0.99);
	target_y = dy;// Maths::lerp(target_y, target_y + dy, 0.99);

	if (mouseDown) {
		camera.rotate((double)target_x, (double)-target_y);
	}
	myDisplayCallback();
}

void reshapeCallback(int, int) {
	//TODO: Window resizing, all we really need to do is modify the camera frustum
	//I think this can be done simply by re-calling gluPerspective, with new parameters?
}

//***********************************************************************************
// Help Window and Menu functionality
//***********************************************************************************

void helpWindowInit() {

}

void helpDisplayCallback() {

}

void helpKeyboardCallback(unsigned char, int, int) {

}

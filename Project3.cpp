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
#include <GL/freeglut.h> // include GLUT library
#include "DebugUtils.h"

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

int main(int argc, char** argv) {

	glutInit(&argc, argv); // initialization

	glutInitWindowSize(WINDOW_SIZE[0], WINDOW_SIZE[1]); // specify a window size
	glutInitWindowPosition(0, 0);						// specify a window position
	mainWindow = glutCreateWindow("GLUT 3D Advertisement");	// create a titled window
	mainWindowInit(); // specify some settings
	menuInit();

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
	gluPerspective(90, (double)WINDOW_SIZE[0] / (double)WINDOW_SIZE[1], 1.0, 1000.0);
	gluLookAt(200, 200, 200, 0, 0, 0, 0, 1, 0);
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

void mouseCallback(int, int, int, int) {
	//TODO: Daniel make this let the user change orientation of camera
}

void motionCallback(int, int) {
	//TODO: Daniel
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

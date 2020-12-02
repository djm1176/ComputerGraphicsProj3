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
	gluOrtho2D(0, WINDOW_SIZE[0], WINDOW_SIZE[1], 0);  // specify a viewing area

}

void menuInit() {

}

void myDisplayCallback() {

}

void keyboardCallback(unsigned char, int, int) {

}

void specialFuncCallback(int, int, int) {

}

void mouseCallback(int, int, int, int) {

}

void motionCallback(int, int) {

}

void reshapeCallback(int, int) {

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

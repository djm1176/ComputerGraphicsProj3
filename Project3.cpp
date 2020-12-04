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

void mainMenuHandler(int choice) {
	switch (choice) {
	case 0:
		// Reset camera position
		break;
	case 1:
		// Terminate the program and close all open windows
		glutDestroyWindow(helpWindow);
		glutDestroyWindow(mainWindow);
		break;
	default:
		break;
	}
}

void rotationSpeedMenuHandler(int choice) {
	switch (choice) {
	case 0:
		// Increase Rotation Speed
		break;
	case 1:
		// Decrease Rotation Speed
		break;
	default:
		break;
	}
}

void helpMenuHandler(int choice) {
	switch (choice) {
	case 0:
		// Show help menu
		break;
	case 1:
		// Hide help menu
		break;
	default:
		break;
	}
}

void textControlMenuHandler(int choice) {
	switch (choice) {
	case 0:
		// Show 3d text
		break;
	case 1:
		// Hide 3d text
		break;
	default:
		break;
	}
}

void rotationControlMenuHandler(int choice) {
	switch (choice) {
	case 0:
		// Enable rotation
		break;
	case 1:
		// Pause rotation
		break;
	case 2:
		// Disable rotation
		break;
	default:
		break;
	}
}

void debugMenuHandler(int choice) {
	switch (choice) {
	case 0:
		// Toggle axis arrows
		break;
	case 1:
		// Toggle grid
		break;
	default:
		break;
	}
}

//***********************************************************************************
// Main Window and Menu Functionality
//***********************************************************************************
void mainWindowInit() {
	glClearColor(1, 1, 1, 1);  // specify a background clor: white
	gluOrtho2D(0, WINDOW_SIZE[0], WINDOW_SIZE[1], 0);  // specify a viewing area

}

void menuInit() {
	int debugMenu = glutCreateMenu(debugMenuHandler);
	glutAddMenuEntry("Toggle axis arrows", 0);
	glutAddMenuEntry("Toggle grid", 1);
	int rotationControlMenu = glutCreateMenu(rotationControlMenuHandler);
	glutAddMenuEntry("Enable rotation", 0);
	glutAddMenuEntry("Pause rotation", 1);
	glutAddMenuEntry("Disable rotation", 2);
	int rotationSpeedMenu = glutCreateMenu(rotationSpeedMenuHandler);
	glutAddMenuEntry("Increase speed", 0);
	glutAddMenuEntry("Decrease speed", 1);
	int textControlMenu = glutCreateMenu(textControlMenuHandler);
	glutAddMenuEntry("Show text", 0);
	glutAddMenuEntry("Hide text", 1);
	int helpMenu = glutCreateMenu(helpMenuHandler);
	glutAddMenuEntry("Show", 0);
	glutAddMenuEntry("Hide", 1);
	int mainMenu = glutCreateMenu(mainMenuHandler);
	glutAddSubMenu("Rotation Control", rotationControlMenu);
	glutAddSubMenu("Adjust Rotation Speed", rotationSpeedMenu);
	glutAddSubMenu("3D Text Control", textControlMenu);
	glutAddSubMenu("Help Window", helpMenu);
	glutAddSubMenu("Debugging Graphics", debugMenu);
	glutAddMenuEntry("Reset Camera Position", 0);
	glutAddMenuEntry("Exit Program", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutCreateMenu(mainMenuHandler);
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

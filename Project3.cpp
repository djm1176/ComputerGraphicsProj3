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

constexpr bool USE_MULTISAMPLE = true;		// Set to true to use anti-aliasing
constexpr int WINDOW_SIZE[]{ 800, 600 };	// The main window's width and height at start
constexpr int HELP_SIZE[]{ 400, 400 };		// The help window's width and height at start

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
void timer(int);

void drawText(float, float, float, const char*, float);

int mainWindow, helpWindow;
int mouse_x, mouse_y;
int target_x{ 0 }, target_y{ 0 };

bool autoRotate = true;
bool mouseDown = false;
Camera camera;

int main(int argc, char** argv) {

	glutInit(&argc, argv); // initialization
	if (USE_MULTISAMPLE) {
		glutInitDisplayMode(GLUT_MULTISAMPLE);
	}

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
	glutTimerFunc(0, timer, 0);

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

void mainMenuHandler(int choice) {
	switch (choice) {
	case 0:
		camera.resetPosition();
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
		// Toggle debug axis
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
	
	//Specify perspective projection. Aspect ratio is the same ratio of the current (init) window width and height,
	//near plane is just in front of camera, and far plane is a sizeable 1000.0 units away from the camera's origin
	
	glEnable(GL_DEPTH_TEST);

	//Initialize the menu used for the main window
	menuInit();
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//TODO: Perform all drawing operations

	DebugUtils::draw_grid();
	DebugUtils::draw_axes();

	glColor3ub(100, 100, 100);
	//x, y, z, text, font size 
	drawText(-100, 10, 50, "iPhone 3GS", 0.25);

	glFlush();
}

void drawText(float x, float y, float z, const char* string, float fontSize)
{
	const char* c;
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(fontSize, fontSize, fontSize);

	for (c = string; *c != '\0'; c++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glPopMatrix();
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
	autoRotate = !(mouseDown);
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

void timer(int value) {
	const double static_x{ 1.0 };
	const double static_y{ 0.0 };
	if (autoRotate) {
		camera.rotate(static_x, static_y);
	}
	myDisplayCallback();
	glutTimerFunc(30, timer, 0);
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

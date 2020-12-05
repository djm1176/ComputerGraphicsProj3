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
#include <string>

#include "Camera.h"
#include "DebugUtils.h"
#include "MathUtils.h"
#include "Obj.h"

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
void addRotationSpeed(double);

void drawText(float, float, float, const char*, float);

int mainWindow, helpWindow;
int mouse_x, mouse_y;
double target_x{ 0.0 }, target_y{ 0.0 }, mouse_dx{ 0.0 }, mouse_dy{ 0.0 };

bool debug_axes{ false }, debug_grid{ false }, draw_text{ true };

double model_scale{ 5.0 };


//enabled		The camera is currently rotating automatically
//paused		The user is dragging, and auto-rotation is 'paused' and will resume on mouse release
//disabled		Auto rotation is disabled until re-enabled in the right-click menu
enum RotationMode { enabled, paused, disabled };
RotationMode autoRotation = RotationMode::enabled;
double rotationSpeed{ 0.25 };

bool mouseDown = false, motionLastFrame = false;
Camera camera;
ObjFile teddy{"./models/porche.obj"};

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
		addRotationSpeed(1.0);
		break;
	case 1:
		// Decrease Rotation Speed
		addRotationSpeed(-1.0);
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
		draw_text = true;
		break;
	case 1:
		// Hide 3d text
		draw_text = false;
		break;
	default:
		break;
	}
}

void rotationControlMenuHandler(int choice) {
	switch (choice) {
	case 0:
		// Enable rotation
		autoRotation = RotationMode::enabled;
		break;
	case 1:
		// Disable rotation
		autoRotation = RotationMode::disabled;
		break;
	default:
		break;
	}
}

void debugMenuHandler(int choice) {
	switch (choice) {
	case 0:
		// Toggle axis arrows
		debug_axes = !debug_axes;
		break;
	case 1:
		// Toggle debug axis
		debug_grid = !debug_grid;
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
	glutAddMenuEntry("Disable rotation", 1);
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

	if (debug_axes) DebugUtils::draw_axes();

	if (debug_grid) DebugUtils::draw_grid();

	if (draw_text) {
		//Place all text drawing operations here


		glColor3ub(100, 100, 100);
		drawText(-100, 10, 50, "iPhone 3GS", 0.25);
		drawText(0, 100, 0, std::to_string(target_x).c_str(), 0.05);
		drawText(0, 92, 0, std::to_string(target_y).c_str(), 0.05);
	}

	//Perform smooth camera rotation
	target_x = Maths::lerp(target_x, mouse_dx, 0.1);
	target_y = Maths::lerp(target_y, mouse_dy, 0.1);

	if (!motionLastFrame) {
		//These values don't get set to 0 from "no mouse movement"
		//since the motionCallback doesn't happen when mouse doesn't move
		mouse_dx = 0;
		mouse_dy = 0;
	}
	if (mouseDown) {
		camera.rotate(target_x, -target_y);
	}

	//Draw the model

	glPointSize(5);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < teddy.getFaceCount(); i++) {
		int col = rand() % 100 + 155;
		glColor3ub(col, col, col);
		for (auto vertex : teddy.getTriangle(i)) {
			glVertex3f(vertex[0] * model_scale, vertex[1] * model_scale, vertex[2] * model_scale);
		}
	}

	glEnd();



	motionLastFrame = false;
	glFlush();
}

void drawText(float x, float y, float z, const char* string, float fontSize) {
	const char* c;
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(fontSize, fontSize, fontSize);

	for (c = string; *c != '\0'; c++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glPopMatrix();
}

void keyboardCallback(unsigned char ch, int x, int y) {
	switch (ch) {
	case 'e':
		addRotationSpeed(0.05);
		break;
	case 'q':
		addRotationSpeed(-0.05);
		break;
	}
}

void specialFuncCallback(int, int, int) {
	//Not needed currently
}

void mouseCallback(int button, int state, int x, int y) {
	//TODO: Daniel make this let the user change orientation of camera
	mouseDown = (button == GLUT_LEFT && state == GLUT_DOWN);

	//Auto rotation
	if (mouseDown) {
		//Pause the rotation (if the feature is enabled)
		if (autoRotation == RotationMode::enabled) {
			autoRotation = RotationMode::paused;
		}
	} else {
		//Only re-enable rotation if it's paused (shouldn't rotate if it's disabled)
		if (autoRotation == RotationMode::paused) {
			autoRotation = RotationMode::enabled;
		}
	}

	mouse_x = x;
	mouse_y = y;
}

void motionCallback(int x, int y) {
	mouse_dx = mouse_x - x;
	mouse_dy = mouse_y - y;
	mouse_x = x;
	mouse_y = y;

	//Camera movement with mouse click moved to a linearly-interpolated function in displayFunc (Ask Daniel)
	//target_x = dx;
	//target_y = dy;

	motionLastFrame = true;
	myDisplayCallback();
}

void reshapeCallback(int, int) {
	//TODO: Window resizing, all we really need to do is modify the camera frustum
	//I think this can be done simply by re-calling gluPerspective, with new parameters?
}

void timer(int value) {
	if (autoRotation == RotationMode::enabled) {
		camera.rotate(rotationSpeed, 0.0);
	}
	myDisplayCallback();
	glutTimerFunc(16, timer, 0); //16msec = 60fps
}

//Add or subtract to the current camera auto rotation
void addRotationSpeed(double offset) {
	//Add or subtract, and clamp the value between some magic numbers
	rotationSpeed = Maths::clamp(rotationSpeed + offset, 3.0, 0.05);
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

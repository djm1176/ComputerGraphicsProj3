/*==================================================================================================
 COURSE:				  CSC 525/625
 ASSIGNMENT:			  Project 3
 PROGRAMMER:			  Eric McCullough
							* Contributions
								* Constant Frame Rate, Camera Auto Rotation
							* Contribution %
								* 14.3%
						  Alex Webber
							* Contributions
								* Right-Click Menus
							* Contribution %
								* 14.3%
						  Tyler Cardwell
							* Contributions
								* Obj File Format Research
							* Contribution %
								* 14.3%
						  Daniel Moore
							* Contributions
								* Camera Movement, Mouse/Keyboard Controls
								* Obj File Format Implementation
							* Contribution %
								* 14.3%
						  John Meents
							* Contributions
								* Stroke and Bitmap Text Rendering Functions
							* Contribution %
								* 14.3%
						  Ben Jinkerson
							* Contributions
								* Obj File Format Implementation
								* Mesh Color Generation
							* Contribution %
								* 14.3%
						  Dallas Bramel
							* Contributions
								* Help Window
							* Contribution %
								* 14.3%
 LAST MODIFIED DATE:	  12/6/2020
 DESCRIPTION:			  3D Interactive Advertisement
 NOTE:					  Copy the 'models' folder into the "C:/TEMP/" directory
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

constexpr bool USE_MULTISAMPLE = true; // Set to true to use anti-aliasing
constexpr int WINDOW_SIZE[]{800, 600}; // The main window's width and height at start
constexpr int HELP_SIZE[]{750, 300};   // The help window's width and height at start

void mainWindowInit();
void helpWindowInit();

void menuInit();

void myDisplayCallback();
void helpDisplayCallback();

void keyboardCallback(unsigned char, int, int);
void helpKeyboardCallback(unsigned char, int, int);

void specialFuncCallback(int, int, int);
void mouseCallback(int, int, int, int);
void wheelCallback(int, int, int, int);
void motionCallback(int, int);
void reshapeCallback(int, int);
void timer(int);
void addRotationSpeed(double);
void resetRotationSpeed();

void drawText(float, float, float, const char*, float);
void drawBitmapText(float, float, float, const char*, float);
void drawHelp();
void drawHelpText(std::string text, int length, int x, int y);

int mainWindow, helpWindow;
int mouse_x, mouse_y;
double target_x{0.0}, target_y{0.0}, mouse_dx{0.0}, mouse_dy{0.0};

bool debug_axes{false}, debug_grid{false}, draw_text{true};

double model_scale{5.0};

//enabled		The camera is currently rotating automatically
//paused		The user is dragging, and auto-rotation is 'paused' and will resume on mouse release
//disabled		Auto rotation is disabled until re-enabled in the right-click menu
enum RotationMode
{
	enabled,
	paused,
	disabled
};
RotationMode autoRotation = RotationMode::enabled;
double rotationSpeed{0.25};

bool mouseDown = false, motionLastFrame = false;
Camera camera;
ObjFile teddy{"C:/temp/models/teddy.obj"};

int main(int argc, char **argv)
{

	glutInit(&argc, argv); // initialization
	if (USE_MULTISAMPLE)
	{
		glutInitDisplayMode(GLUT_MULTISAMPLE);
	}

	glutInitWindowSize(WINDOW_SIZE[0], WINDOW_SIZE[1]);		// specify a window size
	glutInitWindowPosition(0, 0);							// specify a window position
	mainWindow = glutCreateWindow("GLUT 3D Advertisement"); // create a titled window
	mainWindowInit();										// specify some settings
	menuInit();

	camera = Camera(0, 50, 250);

	glutDisplayFunc(myDisplayCallback); // register a callback
	glutKeyboardFunc(keyboardCallback);
	glutSpecialFunc(specialFuncCallback);
	glutMouseFunc(mouseCallback);
	glutMouseWheelFunc(wheelCallback);
	glutMotionFunc(motionCallback);
	glutReshapeFunc(reshapeCallback);
	glutTimerFunc(0, timer, 0);

	glutInitWindowSize(HELP_SIZE[0], HELP_SIZE[1]);
	glutInitWindowPosition(16, 200);
	helpWindow = glutCreateWindow("GLUT 3D Advertisement Help");
	helpWindowInit(); // specify some settings
	glutDisplayFunc(helpDisplayCallback);
	glutKeyboardFunc(helpKeyboardCallback);

	glutMainLoop(); // get into an infinite loop

	return 1; // something wrong happened
}

void mainMenuHandler(int choice)
{
	switch (choice)
	{
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

void rotationSpeedMenuHandler(int choice)
{
	switch (choice)
	{
	case 0:
		// Increase Rotation Speed
		addRotationSpeed(1.0);
		break;
	case 1:
		// Decrease Rotation Speed
		addRotationSpeed(-1.0);
		break;
	case 2:
		resetRotationSpeed();
	default:
		break;
	}
}

void helpMenuHandler(int choice)
{
	switch (choice)
	{
	case 0:
		glutSetWindow(helpWindow);
		glutShowWindow(); // Show help menu
		break;
	case 1:
		glutSetWindow(helpWindow);
		glutHideWindow(); // Hide help menu
		break;
	default:
		break;
	}
}

void textControlMenuHandler(int choice)
{
	switch (choice)
	{
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

void rotationControlMenuHandler(int choice)
{
	switch (choice)
	{
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

void debugMenuHandler(int choice)
{
	switch (choice)
	{
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
void mainWindowInit()
{
	glClearColor(1, 1, 1, 1); // specify a background clor: white

	//Specify perspective projection. Aspect ratio is the same ratio of the current (init) window width and height,
	//near plane is just in front of camera, and far plane is a sizeable 1000.0 units away from the camera's origin

	glEnable(GL_DEPTH_TEST);

	//Initialize the menu used for the main window
	menuInit();
}

void menuInit()
{
	int debugMenu = glutCreateMenu(debugMenuHandler);
	glutAddMenuEntry("Toggle axis arrows", 0);
	glutAddMenuEntry("Toggle grid", 1);
	int rotationControlMenu = glutCreateMenu(rotationControlMenuHandler);
	glutAddMenuEntry("Enable rotation", 0);
	glutAddMenuEntry("Disable rotation", 1);
	int rotationSpeedMenu = glutCreateMenu(rotationSpeedMenuHandler);
	glutAddMenuEntry("Increase speed", 0);
	glutAddMenuEntry("Decrease speed", 1);
	glutAddMenuEntry("Reset to default", 2);
	int textControlMenu = glutCreateMenu(textControlMenuHandler);
	glutAddMenuEntry("Show text", 0);
	glutAddMenuEntry("Hide text", 1);
	int helpMenu = glutCreateMenu(helpMenuHandler);
	glutAddMenuEntry("Show window", 0);
	glutAddMenuEntry("Hide window", 1);
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

void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//TODO: Perform all drawing operations

	if (debug_axes)
		DebugUtils::draw_axes();

	glColor3ub(100, 100, 100);

	if (debug_grid)
		DebugUtils::draw_grid();

	if (draw_text)
	{
		//Place all text drawing operations here
		//x, y, z, text, font size 
		drawText(-75, 120, 50, "Teddy Bear", 0.2);
		drawBitmapText(60, 60, 0, "REAL FUR!", 0.30);
		drawBitmapText(-140, 40, 0, "EXTRA soft!", 0.30);
		drawBitmapText(0, -200, 0, "Includes lifetime warranty!", 0.30);
		drawBitmapText(0, -225, 0, "On sale for $9.99 today only!", .10);
		glColor3ub(100, 100, 100);

	}

	//Perform smooth camera rotation
	target_x = Maths::lerp(target_x, mouse_dx, 0.075);
	target_y = Maths::lerp(target_y, mouse_dy, 0.075);

	if (!motionLastFrame)
	{
		//These values don't get set to 0 from "no mouse movement"
		//since the motionCallback doesn't happen when mouse doesn't move
		mouse_dx = 0;
		mouse_dy = 0;
	}
	if (mouseDown)
	{
		camera.rotate(target_x, -target_y);
	}

	//Draw the model

	glPointSize(5);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < teddy.getFaceCount(); i++)

	{
		glColor3ub(teddy.obj_colors[i][0], teddy.obj_colors[i][1], teddy.obj_colors[i][2]);
		for (auto vertex : teddy.getTriangle(i)) {

			glVertex3f(vertex[0] * model_scale, vertex[1] * model_scale, vertex[2] * model_scale);
		}
	}

	glEnd();

	motionLastFrame = false;
	glFlush();
}

void drawText(float x, float y, float z, const char* text, float fontSize)
{
	const char *c;
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(fontSize, fontSize, fontSize);

	for (c = text; *c != '\0'; c++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glPopMatrix();
}

void drawBitmapText(float x, float y, float z, const char* text, float fontSize)
{
	const char* c;
	glRasterPos3f(x, y, z);

	for (c = text; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

void keyboardCallback(unsigned char ch, int x, int y)
{
	switch (ch)
	{
	case 'e':
		addRotationSpeed(0.05);
		break;
	case 'q':
		addRotationSpeed(-0.05);
		break;
	}
}

void specialFuncCallback(int, int, int)
{
	//Not needed currently
}

void mouseCallback(int button, int state, int x, int y)
{
	//TODO: Daniel make this let the user change orientation of camera
	mouseDown = (button == GLUT_LEFT && state == GLUT_DOWN);

	//Auto rotation
	if (mouseDown)
	{
		//Pause the rotation (if the feature is enabled)
		if (autoRotation == RotationMode::enabled)
		{
			autoRotation = RotationMode::paused;
		}
	}
	else
	{
		//Only re-enable rotation if it's paused (shouldn't rotate if it's disabled)
		if (autoRotation == RotationMode::paused)
		{
			autoRotation = RotationMode::enabled;
		}
	}

	mouse_x = x;
	mouse_y = y;
}

void wheelCallback(int wheel, int dir, int x, int y) {
	camera.zoom(dir * 10);
}

void motionCallback(int x, int y)
{
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

void reshapeCallback(int, int)
{
	//TODO: Window resizing, all we really need to do is modify the camera frustum
	//I think this can be done simply by re-calling gluPerspective, with new parameters?
}

void timer(int value)
{
	glutSetWindow(mainWindow);
	if (autoRotation == RotationMode::enabled)
	{
		camera.rotate(rotationSpeed, 0.0);
	}
	myDisplayCallback();
	glutTimerFunc(16, timer, 0); //16msec = 60fps
}

//Add or subtract to the current camera auto rotation
void addRotationSpeed(double offset)
{
	//Add or subtract, and clamp the value between some magic numbers
	rotationSpeed = Maths::clamp(rotationSpeed + offset, 3.0, 0.05);
}

// Reset rotation speed to initial value
void resetRotationSpeed()
{
	rotationSpeed = .25;
}

//***********************************************************************************
// Help Window and Menu functionality
//***********************************************************************************

void helpWindowInit()
{
	glClearColor(0, 0, 0, 0);		  // specify a background clor: black
	gluOrtho2D(-200, 200, -200, 200); // specify a viewing area
}

void helpDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT); // draw the background

	drawHelp();

	glFlush(); // flush out the buffer contents
	glutSwapBuffers();
}
void drawHelp()
{
	int x = -195;
	int y = 180;
	std::string helpItems[] = {"Welcome to the 3D Advertisement for Teddy Bear, Version 1.0, December 2020",
								 "To change properties about the 3D model, right click the editor to view the menu",
								 "Select 'Rotation control' to enable or disable rotation", "Select 'Adjust Rotation speed' to change the speed of rotation",
								 "Select '3D Text Control' control the 3d text", "Select 'Help Window' to show or hide the help window",
								 "Select 'Debugging Graphics' to toggle axis arrows or toggle debug axis", "Select 'Reset Camera Position' to reset the camera's position", "Press 'Q' to slow rotation",
								 "Press 'E' to speed up rotation", "Select 'Exit' to leave the program", "", "Note: Rotation must be disabled before resetting the camera back to defaults.",
								 "Use Scroll Wheel to zoom in and out of the model."
	}; //

	for (int i = 0; i < sizeof(helpItems) / sizeof(helpItems[0]); i++)
	{
		drawHelpText(helpItems[i], 0, x, y);
		y -= 22;
	}
}
void drawHelpText(std::string text, int length, int x, int y)
{
	glColor3ub(100, 100, 100);
	glRasterPos2i(x, y);
	for (auto c : text)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)c);
	}
}
void helpKeyboardCallback(unsigned char, int, int)
{
}

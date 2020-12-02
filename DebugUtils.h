#pragma once
/*==================================================================================================
Performs utility debug features for the main program
==================================================================================================*/

#include <GL/freeglut.h>
namespace DebugUtils {
	
	//Draws XYZ coordinate axes at the origin, with each line extending 50 units.
	void draw_axes() {
		glBegin(GL_LINES);
		glColor3ub(100, 100, 100);
		glVertex3i(0, 0, 0);
		glVertex3i(50, 0, 0);

		glVertex3i(0, 0, 0);
		glVertex3i(0, 50, 0);

		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, 50);
		glEnd();
	}

	//Draws a grid on the XY coordinate plane for a 1000x1000 area. The effect looks like a checkerboard on the "floor".
	void draw_grid() {
		glBegin(GL_LINES);
		glColor3ub(100, 100, 100);
		
		for (int x = -500; x <= 500; x += 100) {
			glVertex3i(x, 0, -500);
			glVertex3i(x, 0, 500);
		}
		for (int y = -500; y <= 500; y += 100) {
			glVertex3i(-500, 0, y);
			glVertex3i(500, 0, y);
		}

		glEnd();
	}
}

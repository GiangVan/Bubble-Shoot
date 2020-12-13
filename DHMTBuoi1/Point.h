#pragma once
#include "Dependencies/glew/glew.h";
#include "Dependencies/freeglut/freeglut.h";


class Point {

//--------------------------------------------------------------------------
	public:
//--------------------------------------------------------------------------
	GLfloat x, y, z;

	Point(GLfloat _x = 0.0f, GLfloat _y = 0.0f, GLfloat _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}
};
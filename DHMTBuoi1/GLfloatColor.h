#pragma once
#include "Dependencies/glew/glew.h";
#include "Dependencies/freeglut/freeglut.h";


class GLfloatColor {

//--------------------------------------------------------------------------
	public:
//--------------------------------------------------------------------------
	GLfloat red, green, blue;

	GLfloatColor(GLfloat _red = 1.0f, GLfloat _green = 1.0f, GLfloat _blue = 1.0f) {
		red = _red;
		green = _green;
		blue = _blue;
	}
};
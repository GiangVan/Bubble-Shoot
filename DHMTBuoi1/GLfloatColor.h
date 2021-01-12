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

    static GLfloatColor getRandomColor(int minColor = 1, int maxColor = 100) {
        return GLfloatColor(
            (GLfloat)(rand() % (maxColor - minColor + 1) + minColor) / maxColor, 
            (GLfloat)(rand() % (maxColor - minColor + 1) + minColor) / maxColor, 
            (GLfloat)(rand() % (maxColor - minColor + 1) + minColor) / maxColor
        );
    }

    static GLfloatColor redColor() {
        return GLfloatColor(1.0f, 0.0f, 0.0f);
    }

    static GLfloatColor blueColor() {
        return GLfloatColor(0.0f, 0.0f, 1.0f);
    }

    static GLfloatColor greenColor() {
        return GLfloatColor(0.0f, 1.0f, 0.0f);
    }

    static GLfloatColor orangeColor() {
        return GLfloatColor(1.0f, 0.4f, 0.0f);
    }
};
#pragma once
///////////////////////////////////////////////////////////////////////////////////////
//                                                                                   //
//	    Class này sử dụng quản lý camera                                             //
//      ------------------------------------------------                             //
//	    1.  Gọi hàm display() mỗi khi tiến hành render để camera được update         //
//                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////

#include "Point.h";
#include "Dependencies/glew/glew.h";
#include "Dependencies/freeglut/freeglut.h";


class CameraEntity {

//--------------------------------------------------------------------------
    public:             
//--------------------------------------------------------------------------
    CameraEntity(){ }

    Point eyePoint = Point(0.0f, 0.0f, 10.0f);


    void display() {
        glLoadIdentity();
        gluLookAt(eyePoint.x, eyePoint.y, eyePoint.z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    }

    void keyboardHadler(unsigned char key, int x, int y) {
        GLfloat speed = 1.0f;

        switch (key) {
            case 'w':
                eyePoint.y += speed;
                break;
            case 's':
                eyePoint.y -= speed;
                break;
            case 'a':
                eyePoint.x -= speed;
                break;
            case 'd':
                eyePoint.x += speed;
                break;
            default:   
                break;
        }
    }
};
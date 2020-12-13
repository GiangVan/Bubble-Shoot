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
    Point centerPoint = Point(0.0f, 0.0f, 0.0f);
    Point upPoint = Point(0.0f, 1.0f, 0.0f);
    Point mousePoint = Point();


    void display() {
        glLoadIdentity();
        gluLookAt(
            eyePoint.x, eyePoint.y, eyePoint.z,             //eye
            centerPoint.x, centerPoint.y, centerPoint.z,    //center
            upPoint.x, upPoint.y, upPoint.z                 //up
        );
    }

    void mouseClickHandler(int button, int state, int x, int y) {
        if (state == GLUT_DOWN) {
            mousePoint.x = x;
            mousePoint.y = y;
        }
    }

    void mouseMoveHandler(int x, int y) {
        int distanceX = x - mousePoint.x;
        int distanceY = y - mousePoint.y;

        centerPoint.x -= distanceX / 200.0f;
        centerPoint.y += distanceY / 200.0f;

        mousePoint.x = x;
        mousePoint.y = y;
    }

    void keyboardHadler(unsigned char key, int x, int y) {
        GLfloat speed = 1.5f;

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
            case '8':
                upPoint.y += speed * 10;
                break;
            case '2':
                upPoint.y -= speed * 10;
                break;
            case '4':
                upPoint.x -= speed * 10;
                break;
            case '6':
                upPoint.x += speed * 10;
                break;
            default:   
                break;
        }
    }
};
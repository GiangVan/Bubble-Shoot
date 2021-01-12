#pragma once
///////////////////////////////////////////////////////////////////////////////////////
//                                                                                   //
//	    Class này sử dụng để variable hóa các models                                 //
//      ------------------------------------------------                             //
//	    1.  Gọi hàm display() mỗi khi tiến hành render để model được hiển thị        //
//	    2.  Gọi hàm update() sau khi render để cập nhập các thuộc tính cho model     //
//                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////

#include <string>;
#include <list>;
#include "Point.h";
#include "GLfloatColor.h";
#include "Dependencies/glew/glew.h";
#include "Dependencies/freeglut/freeglut.h";


class DisplayEntity {      
    
//--------------------------------------------------------------------------
    public:             
//--------------------------------------------------------------------------
    DisplayEntity(){ }


    std::string name;
    std::string type;
    Point translatePoint = Point();
    GLfloat angle = 0.0f;
    GLfloat centerAngle = 0.0f;
    GLfloat speed = 0.0f;
    GLfloatColor color = GLfloatColor();
    void (*modelRenderingFunc)(DisplayEntity model) = 0;
    void (*modelUpdatingFunc)(DisplayEntity *model) = 0;
    bool isDestroy = false;
    std::list<DisplayEntity*> neighbors;

    
    void display(DisplayEntity model) {
        if (!isDestroy) {
            glColor3f(color.red, color.green, color.blue);

            if (modelRenderingFunc != 0) {
                modelRenderingFunc(model);
            }
        }
    }

    void update(DisplayEntity *model) {
        if (modelUpdatingFunc != 0) {
            modelUpdatingFunc(model);
        }
    }

    void setColor(GLfloat red, GLfloat green, GLfloat blue){
        color.red = red;
        color.green = green;
        color.blue = blue;
    }

    void setTranslatePoint(GLfloat x, GLfloat y, GLfloat z){
        translatePoint.x = x;
        translatePoint.y = y;
        translatePoint.z = z;
    }

    void randomTranslatePoint(int min, int max, GLfloat distance = 0){
        GLfloat random = (GLfloat)(rand() % (max - min + 1) + min);
        if (random * random < distance * distance) {
            if (random < 0) {
                distance *= -1;
            }
            random += distance;
        }
        translatePoint.x = random;
        random = (GLfloat)(rand() % (max - min + 1) + min);
        if (random * random < distance * distance) {
            if (random < 0) {
                distance *= -1;
            }
            random += distance;
        }
        translatePoint.y = random;
        random = (GLfloat)(rand() % (max - min + 1) + min);
        if (random * random < distance * distance) {
            if (random < 0) {
                distance *= -1;
            }
            random += distance;
        }
        translatePoint.z = random;
    }
};

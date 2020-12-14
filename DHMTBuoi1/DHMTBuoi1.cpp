﻿// DHMTBuoi1.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <stdlib.h>;
#include <stdio.h>;
#include <list>;
#include <math.h>;

#include "Dependencies/glew/glew.h";
#include "Dependencies/freeglut/freeglut.h";
#include "DisplayEntity.h";
#include "initDisplayEntityList.h";
#include "CameraEntity.h";
#include "getMilliCount.h";
#include "handleFrame.h";

using namespace std;

//Init variables
list<DisplayEntity> displayEntidyList;
CameraEntity cameraEntity;


void render(void) {
    int beginframe = getMilliCount();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //--------------------------------------------------------------------------//
    // Hiển thị các models                                                      //
    //--------------------------------------------------------------------------//
    for(DisplayEntity item : displayEntidyList){                               //
        item.display(item);                                                   //
    }                                                                           //
    //--------------------------------------------------------------------------//
  
    glMatrixMode(GL_MODELVIEW);
    //--------------------------------------------------------------------------//
    // Update hiển thị camera                                                   //
    //--------------------------------------------------------------------------//
    cameraEntity.display();                                                     //
    //--------------------------------------------------------------------------//

    glutSwapBuffers();

    //--------------------------------------------------------------------------//
    // Xử lý frame                                                              //
    //--------------------------------------------------------------------------//
    handleFrame(beginframe);                                                    //
    //--------------------------------------------------------------------------//
}

void update() {
    //--------------------------------------------------------------------------//
    // Thuộc tính của các models được update                                    //
    //--------------------------------------------------------------------------//
    for(DisplayEntity &item : displayEntidyList){                               //
        DisplayEntity* ptr = &item;
        ptr->update(&item);                                                     //
    }                                                                           //
    //--------------------------------------------------------------------------//

    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void inputProcess(unsigned char key, int x, int y) {
    //--------------------------------------------------------------------------//
    // Handle move camera follow keybord                                        //
    //--------------------------------------------------------------------------//
    cameraEntity.keyboardHadler(key, x, y);                                     //
    //--------------------------------------------------------------------------//
}

void mouseClickProcess(int button, int state, int x, int y) {
    //--------------------------------------------------------------------------//
    // Handle move camera follow mouse                                          //
    //--------------------------------------------------------------------------//
    cameraEntity.mouseClickHandler(button, state, x, y);                        //
    //--------------------------------------------------------------------------//
}

void mouseMoveProcess(int x, int y) {
    //--------------------------------------------------------------------------//
    // Handle move camera follow mouse                                          //
    //--------------------------------------------------------------------------//
    cameraEntity.mouseMoveHandler(x, y);                                        //
    //--------------------------------------------------------------------------//
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
}

int main(int argc, char** argv)
{
    //--------------------------------------------------------------------------//
    // Thêm các models lúc khởi tạo                                             //
    //--------------------------------------------------------------------------//
    displayEntidyList = initDisplayEntidyList();                                //
    //--------------------------------------------------------------------------//
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);

    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(inputProcess);
    glutMouseFunc(mouseClickProcess);
    glutMotionFunc(mouseMoveProcess);
    glutIdleFunc(update);
    glutMainLoop();
    return 0;
}




﻿// DHMTBuoi1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <sys/timeb.h>;
#include <sys/utime.h>;
#include <stdlib.h>;
#include <stdio.h>;
#include <vector>;
#include <math.h>;

#include "Dependencies/glew/glew.h";
#include "Dependencies/freeglut/freeglut.h";
#include "DisplayEntity.h";
#include "initDisplayEntityList.h";
#include "CameraEntity.h";

using namespace std;

//Init variables
vector<DisplayEntity> displayEntidyList;
CameraEntity cameraEntity;

int maxFrame = 25;
int chuky = 1000 / maxFrame;
// code nào mà ko có khúc này
// mặc định là lụm trên mạng
// khỏi suy nghĩ, rớt môn
int getMilliCount() {
    timeb tb;
    ftime(&tb);
    int nCount = tb.millitm +(tb.time & 0xfffff)*1000;
    return nCount;
}
// lấy thời điểm hiện tại theo ms
void sleep(int sleeptime)
{
    int count = 0;
    int beginsleep = getMilliCount();
    while (getMilliCount() - beginsleep < sleeptime)
    {
        count++;
    }
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
}

void render(void) {
    int beginframe = getMilliCount();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //--------------------------------------------------------------------------//
    // Hiển thị các models                                                      //
    //--------------------------------------------------------------------------//
    for(int i=0; i < displayEntidyList.size(); i++){                            //
        displayEntidyList[i].display(displayEntidyList[i]);                     //
    }                                                                           //
    //--------------------------------------------------------------------------//
  
    glMatrixMode(GL_MODELVIEW);
    //--------------------------------------------------------------------------//
    // Update hiển thị camera                                                   //
    //--------------------------------------------------------------------------//
    cameraEntity.display();                                                     //
    //--------------------------------------------------------------------------//

    glutSwapBuffers();

    int timeDiff = getMilliCount() - beginframe;
    if (timeDiff < chuky)
    {
        sleep(chuky - timeDiff);
    }
}

void update() {
    //--------------------------------------------------------------------------//
    // Thuộc tính của các models được update                                    //
    //--------------------------------------------------------------------------//
    for(int i=0; i < displayEntidyList.size(); i++){                            //
        displayEntidyList[i].update(&displayEntidyList[i]);                     //
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
    glutIdleFunc(update);
    glutMainLoop();
    return 0;
}




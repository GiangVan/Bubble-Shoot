// DHMTBuoi1.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <stdlib.h>;
#include <stdio.h>;
#include <list>;
#include <string>;
#include <math.h>;
#include <algorithm>
#include <sstream>

#include "Dependencies/glew/glew.h";
#include "Dependencies/freeglut/freeglut.h";

float score = 0.0f;

unsigned char gunKeyPressed;
const unsigned char GUN_KEY_LEFT = '4';
const unsigned char GUN_KEY_RIGHT ='6';
const GLfloat GUN_RANGE = 10.0f;

const GLfloat MAX_RANGE = 20.0f;
const GLfloat GUN_SPEED = 0.15f;
const float MINIMUM_SCORE = 1.0f;
const unsigned int GENERATE_TIME = 45;
const unsigned int START_TIME = 2000;
const std::string COLLISION_CHECK_TYPE = "collision_check";
const std::string FOOD_TYPE = "food";
const std::string ENEMIES_TYPE = "enemies";
const std::string MAIN_TYPE = "main";
const std::string REMOVED_STATUS = "removed";

#include "DisplayEntity.h";
#include "initDisplayEntityList.h";
#include "getScore.h";
#include "CameraEntity.h";
#include "checkCollision.h";
#include "createRandomBall.h";
#include "clearItemFromList.h";
#include "randomFloat.h";
#include "containsInStringList.h";
#include "getMilliCount.h";
#include "handleFrame.h";
#include "GLfloatColor.h";
#include "simpledrawtext.h"

using namespace std;

//Init variables
list<DisplayEntity> displayEntidyList;
CameraEntity cameraEntity;
SimpleDrawText showtext;

void moveGunProcess() {
    DisplayEntity* gunPtr = nullptr;
    for (DisplayEntity& item : displayEntidyList) {
        if (item.name == "Gun") {
            gunPtr = &item;
        }
    }
    if (gunPtr != NULL) {
        if (gunKeyPressed == GUN_KEY_LEFT && gunPtr->translatePoint.z < GUN_RANGE) {
            gunPtr->translatePoint.x -= GUN_SPEED;
            gunPtr->translatePoint.z += GUN_SPEED;
        }
        else if (gunKeyPressed == GUN_KEY_RIGHT && gunPtr->translatePoint.x < GUN_RANGE) {
            gunPtr->translatePoint.x += GUN_SPEED;
            gunPtr->translatePoint.z -= GUN_SPEED;
        }
    }
}

void render(void) {
    int beginframe = getMilliCount();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Hiển thị các models    
    displayEntidyList = clearItemFromList(displayEntidyList);
    for(DisplayEntity item : displayEntidyList){                                      
        item.display(item);
    }                                                                           
  
    glMatrixMode(GL_MODELVIEW);
    std::ostringstream ss;
    ss << score;
    std::string showscore(ss.str());
   
    showtext.drawText("Score:"+showscore, 250, 550, 1, 1, 0);
    // Update hiển thị camera                                                   
    cameraEntity.display();                                                    

    glutSwapBuffers();

    // Xử lý frame                                                              
    handleFrame(beginframe);                                                    
}

void update() {
    // Thuộc tính của các models được update   
    list<DisplayEntity> removedList;
    displayEntidyList = clearItemFromList(displayEntidyList);
    for(DisplayEntity &item : displayEntidyList){
        DisplayEntity* ptr = &item;
        ptr->update(&item);
    }  

    // Kiểm tra va chạm
    checkCollision(&displayEntidyList, COLLISION_CHECK_TYPE);

    glutPostRedisplay();

    moveGunProcess();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.01, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyDownGun(unsigned char key) {
    if (key == GUN_KEY_LEFT || key == GUN_KEY_RIGHT) {
        gunKeyPressed = key;
    }
}

void keyUpGun(unsigned char key) {
    if (key == GUN_KEY_LEFT || key == GUN_KEY_RIGHT) {
        gunKeyPressed = ' ';
    }
}

void keyDownProcess(unsigned char key, int x, int y) {
    // Handle move camera follow keybord                                        
    cameraEntity.keyboardHadler(key, x, y); 
    // 
    keyDownGun(key);
}

void keyUpProcess(unsigned char key, int x, int y) {
    keyUpGun(key);
}

void mouseClickProcess(int button, int state, int x, int y) {
    // Handle move camera follow mouse                                          
    cameraEntity.mouseClickHandler(button, state, x, y);                        
}

void mouseMoveProcess(int x, int y) {
    // Handle move camera follow mouse                                          
    cameraEntity.mouseMoveHandler(x, y);                                        
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
}

void timerProcess(int time) {
    DisplayEntity ball = createRandomBall();
    displayEntidyList.push_back(ball);
    glutTimerFunc(GENERATE_TIME, timerProcess, 0);
}

int main(int argc, char** argv)
{
    // Thêm các models lúc khởi tạo                                             
    displayEntidyList = initDisplayEntidyList();  

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1200, 800);

    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyDownProcess);
    glutKeyboardUpFunc(keyUpProcess);
    glutMouseFunc(mouseClickProcess);
    glutMotionFunc(mouseMoveProcess);
    glutTimerFunc(START_TIME, timerProcess, 0);
    glutIdleFunc(update);
    glutMainLoop();
    return 0;
}




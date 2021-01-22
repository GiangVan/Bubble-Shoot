// DHMTBuoi1.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <stdlib.h>;
#include <stdio.h>;
#include <list>;
#include <string>;
#include <math.h>;
#include <algorithm>

#include "Dependencies/glew/glew.h";
#include "Dependencies/freeglut/freeglut.h";

float score = 0.0f;

const GLfloat MAX_RANGE = 20.0f;
const GLfloat GUN_SPEED = 0.2f;
const float MINIMUM_SCORE = 1000.0f;
const unsigned int GENERATE_TIME = 80;
const unsigned int START_TIME = 2000;
const std::string COLLISION_CHECK_TYPE = "collision_check";
const std::string FOOD_TYPE = "food";
const std::string ENEMIES_TYPE = "enemies";
const std::string MAIN_TYPE = "main";
const std::string REMOVED_STATUS = "removed";

#include "DisplayEntity.h";
#include "initDisplayEntityList.h";
#include "CameraEntity.h";
#include "checkCollision.h";
#include "createRandomBall.h";
#include "clearItemFromList.h";
#include "randomFloat.h";
#include "containsInStringList.h";
#include "getMilliCount.h";
#include "handleFrame.h";
#include "GLfloatColor.h";

using namespace std;

//Init variables
list<DisplayEntity> displayEntidyList;
CameraEntity cameraEntity;



void render(void) {
    int beginframe = getMilliCount();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Hiển thị các models    
    displayEntidyList = clearItemFromList(displayEntidyList);
    for(DisplayEntity item : displayEntidyList){                                      
        item.display(item);
    }                                                                           
  
    glMatrixMode(GL_MODELVIEW);

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

void keyboardGun(unsigned char key, int x, int y, DisplayEntity* model) {
    GLfloat speed = 0.5f;

   switch (key) {
    case '6':
        model->translatePoint.x += GUN_SPEED;
        model->translatePoint.z -= GUN_SPEED;
        break;
    case '4':
        model->translatePoint.x -= GUN_SPEED;
        model->translatePoint.z += GUN_SPEED;
        break;
    default:
        break;
    }
}

void inputProcess(unsigned char key, int x, int y) {
    cameraEntity.keyboardHadler(key, x, y); 
    // Handle move camera follow keybord                                        
    DisplayEntity* gunPtr = nullptr;
    for (DisplayEntity& item : displayEntidyList) {
        if (item.name == "Gun") {
            gunPtr = &item;
        }
    }
    if (gunPtr != NULL) {
        keyboardGun(key, x, y, gunPtr);
        /*keyboardShoot(key, x, y, gunPtr);*/
    }
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

void UpdateTokens(int time) {
    DisplayEntity ball = createRandomBall();
    displayEntidyList.push_back(ball);
    glutTimerFunc(GENERATE_TIME, UpdateTokens, 0);
}

int main(int argc, char** argv)
{
    // Thêm các models lúc khởi tạo                                             
    displayEntidyList = initDisplayEntidyList();  

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
    glutTimerFunc(START_TIME, UpdateTokens, 0);
    glutIdleFunc(update);
    glutMainLoop();
    return 0;
}




// DHMTBuoi1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Dependencies/glew/glew.h";
#include "Dependencies/freeglut/freeglut.h";
#include <stdio.h>;
#include "DisplayEntity.h";
#include <vector>;


using namespace std;

#include <sys/timeb.h>;
#include <sys/utime.h>;
#include <stdlib.h>;
#include <math.h>;
//
vector<DisplayEntity> displayEntidyList;

// -1 là qua trái.
double camY = 1; // biến vị trí cam theo trục Y

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
// code trên mạng ko có hàm sleep này đâu, yên tâm mà copy
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
}

void render(void) {
    int beginframe = getMilliCount();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	for(int i=0; i < displayEntidyList.size(); i++){
		displayEntidyList[i].display();
	}


  
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, camY, 0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glutSwapBuffers();

    int timeDiff = getMilliCount() - beginframe;
    if (timeDiff < chuky)
    {
        sleep(chuky - timeDiff);
    }
}

// tốc độ quay của chái đất
void update() {
// mỗi frame, vị trí của trái đất sẽ tăng 1 độ
    
	for(int i=0; i < displayEntidyList.size(); i++){
		displayEntidyList[i].update(&displayEntidyList[i]);
	}

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


double tocdotemp = 0;
// biến lưu trữ tạm tốc độ hiện tại của trái đất
void inputProcess(unsigned char key, int x, int y) {
    switch (key) {
		case 'w':
			// tốc độ sẽ đẩy lên 0.2 mỗi lần ấn 1
			camY = camY + 1;
			break;
		case 's':
			camY = camY - 1;
			break;
		default:   
			break;
    }
}


void initDisplayEntidyList() {
	//------------------------------------------------------
	// Init Model 1
	//------------------------------------------------------
	DisplayEntity a;
	a.name = "Sun";
	a.mode = "rotate";
	a.modelUpdatingFunc = [](DisplayEntity *model) { 
		model->angle = model->angle + 1;
		// đủ 360 độ sẽ quay về tính lại là 0
		if (model->angle > 360)
		{
			model->angle = 0;
		}
	};
	a.setColor(1.0, 0.0, 0.0);
	a.modelRenderingFunc = []() { 
		glutWireSphere(2.0, 50, 40); 
	};
	displayEntidyList.push_back(a);

	//------------------------------------------------------
	// Init Model 2
	//------------------------------------------------------
	a = DisplayEntity();
	a.name = "Earth";
	a.setColor(1.0, 1.0, 1.0);
	a.modelRenderingFunc = []() { 
		glutWireSphere(0.5, 100, 80);
	};
	a.mode = "translate";
	a.modelUpdatingFunc = [](DisplayEntity *model) { 
		model->angle = model->angle + 10;
		// đủ 360 độ sẽ quay về tính lại là 0
		if (model->angle > 360)
		{
			model->angle = 0;
		}
		// theo trục x và z thì côgn thức học cấp
		// 3 cho biết thế này:
		model->translatePoint.x = 3 * sin(model->angle*3.14/180);
		model->translatePoint.z = 3 * cos(model->angle*3.14/180);
	};
	displayEntidyList.push_back(a);

	//------------------------------------------------------
	// Init Model 3
	//------------------------------------------------------
	a = DisplayEntity();
	a.name = "Earth 2";
	a.setColor(1.0f, 1.0f, 1.0f);
	a.modelRenderingFunc = []() { 
		glutWireSphere(0.5, 100, 80);
	};
	a.mode = "translate";
	a.modelUpdatingFunc = [](DisplayEntity *model) { 
		//change color
		int maxColor = 100;
		int minColor = 10;
		model->setColor(
			(GLfloat)(rand() % (maxColor - minColor + 1) + minColor) / maxColor, 
			(GLfloat)(rand() % (maxColor - minColor + 1) + minColor) / maxColor, 
			(GLfloat)(rand() % (maxColor - minColor + 1) + minColor) / maxColor
		);
		//
		model->angle = model->angle + 20;
		// đủ 360 độ sẽ quay về tính lại là 0
		if (model->angle > 360)
		{
			model->angle = 0;
		}
		// theo trục x và z thì côgn thức học cấp
		// 3 cho biết thế này:
		model->translatePoint.y = 3 * sin(model->angle*3.14/180);
		model->translatePoint.z = 3 * cos(model->angle*3.14/180);
	};
	displayEntidyList.push_back(a);
}


int main(int argc, char** argv)
{
	initDisplayEntidyList();

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




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
// dùng thư viện math để tính căn bậc 2

double rtd = 3;
// bán kính của quỹ đạo trái đất

double anpha = 0;
// góc hiện tại của trái đất so với mặt trời


float x = rtd* sin(anpha/3.14);
float z = rtd * cos(anpha / 3.14);
// x là vị trí khởi tạo của cục xanh
int chieu = 1;
// chiều 1 tương ứng qua phải
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
    // //glRotatef((GLfloat)year, 0.0, 1.0, 0.0); 








    // chú ý thay x và z để chỉ định vị trí mới
    // y luôn  = 0

  
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
double tocdo = 0;
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
    case '1':
        // tốc độ sẽ đẩy lên 0.2 mỗi lần ấn 1
        tocdo = tocdo + 0.2;
        camY = camY + 1;
        break;
    case '2':
        tocdo = tocdo - 0.2;
        camY = camY - 1;
        break;
    case '3':
        if (tocdo != 0)
        {
            tocdotemp = tocdo;
            tocdo = 0;
        }
        else
        {
            tocdo = tocdotemp;
        }
        break;
    default:          break;
    }
}


void initDisplayEntidyList() {
	DisplayEntity a;
	a.name = "Sun";
	a.setColor(1.0, 0.0, 0.0);
	a.setCurrentPoint(0.0, 0.0, 3.0);
	a.modelRenderingFunc = []() { 
		glutWireSphere(2.0, 50, 40); 
	};
	displayEntidyList.push_back(a);

	a = DisplayEntity();
	a.name = "Earth";
	a.setColor(1.0, 1.0, 1.0);
	a.modelRenderingFunc = []() { 
		glutWireSphere(0.5, 100, 80);
	};
	a.modelUpdatingFunc = [](DisplayEntity *model) { 
		anpha= anpha + 10;
		// đủ 360 độ sẽ quay về tính lại là 0
		if (anpha > 360)
		{
			anpha = 0;
		}
		// theo trục x và z thì côgn thức học cấp
		// 3 cho biết thế này:
		model->currentPoint.x = rtd * sin(anpha*3.14/180);
		model->currentPoint.z = rtd * cos(anpha*3.14/180);
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




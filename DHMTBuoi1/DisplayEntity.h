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
	Point translatePoint = Point();
	GLfloat angle = 0.0f;
	GLfloatColor color;
	void (*modelRenderingFunc)() = 0;
	void (*modelUpdatingFunc)(DisplayEntity *model) = 0;
	std::string mode = "none";


	void display() {
		glColor3f(color.red, color.green, color.blue);

		if(mode != "none"){
			glPushMatrix();
		}

		if (mode == "translate") {
 			glTranslatef(translatePoint.x, translatePoint.y, translatePoint.z);
		}
		if (mode == "rotate") {
 			glRotatef(angle, 0.0, 1.0, 0.0); 
		}

		if (modelRenderingFunc != 0) {
			modelRenderingFunc();
		}

		if(mode != "none"){
			glPopMatrix();
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
};

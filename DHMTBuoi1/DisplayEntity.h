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
	DisplayEntity(){
		init();
	}


	std::string name;
	Point initPoint;   
	Point currentPoint;
	Point destinationPoint;
	GLfloatColor color;
	void (*modelRenderingFunc)();
	void (*modelUpdatingFunc)(DisplayEntity *model) = 0;
	int mode;


	void display() {
		glPushMatrix();
		glColor3f(color.red, color.green, color.blue);
		modelRenderingFunc();
 		glTranslatef(currentPoint.x, currentPoint.y, currentPoint.z);
		glPopMatrix();
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

	void setCurrentPoint(GLfloat x, GLfloat y, GLfloat z){
		currentPoint.x = x;
		currentPoint.y = y;
		currentPoint.z = z;
	}

	void setInitPoint(GLfloat x, GLfloat y, GLfloat z){
		initPoint.x = x;
		initPoint.y = y;
		initPoint.z = z;
	}

	void setDestinationPoint(GLfloat x, GLfloat y, GLfloat z){
		destinationPoint.x = x;
		destinationPoint.y = y;
		destinationPoint.z = z;
	}

//--------------------------------------------------------------------------
	private:
//--------------------------------------------------------------------------
	void init(){
		GLfloat initPointValue = 0.0;
		initPoint.x = initPoint.y = initPoint.z = initPointValue;
		currentPoint.x = currentPoint.y = currentPoint.z = initPointValue;
		destinationPoint.x = destinationPoint.y = destinationPoint.z = initPointValue;

		mode = 0;
	}
};

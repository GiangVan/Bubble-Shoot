#pragma once
////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                            //
//	    Function này sử dụng để khai báo các models sẽ sử dụng lúc chương trình khởi tạo      //                             //
//      ------------------------------------------------                                      //
//	    1.  Khai báo những hiển thị cho model tại con trỏ hàm modelRenderingFunc (Hàm         //       
//          sẽ được gọi mỗi khi render)                                                       //
//	    2.  Khai báo update thuộc tính của model tại con trỏ hàm modelUpdatingFunc (Hàm       //
//          sẽ được gọi sau khi render)                                                       //
//                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////

#include "DisplayEntity.h";
#include <list>;


std::list<DisplayEntity> initDisplayEntidyList() {
    std::list<DisplayEntity> displayEntidyList;

    //------------------------------------------------------
    // 1.   Sun model
    //------------------------------------------------------
    DisplayEntity sunModel;
    sunModel.name = "Sun";
    sunModel.setColor(1.0f, 0.0f, 0.0f);
    sunModel.modelUpdatingFunc = [](DisplayEntity *model) { 
        model->angle += 0.5f;
        // đủ 360 độ sẽ quay về tính lại là 0
        if (model->angle > 360)
        {
            model->angle = 0;
        }
    };
    sunModel.setColor(1.0, 0.0, 0.0);
    sunModel.modelRenderingFunc = [](DisplayEntity model) { 
        glPushMatrix();
        glRotatef(model.angle, 0.0, 1.0, 0.0);
        glutWireSphere(2.0, 50, 40);
        glPopMatrix();
    };
    displayEntidyList.push_back(sunModel);

    //------------------------------------------------------
    // 2.   Earth model
    //------------------------------------------------------
    DisplayEntity earthModel;
    earthModel.name = "Earth";
    earthModel.type = "collision_check";
    earthModel.modelRenderingFunc = [](DisplayEntity model) { 
        glPushMatrix();
        glTranslatef(model.translatePoint.x, model.translatePoint.y, model.translatePoint.z);
        glutWireSphere(0.5, 50, 10);
        glPopMatrix();
    };
    earthModel.modelUpdatingFunc = [](DisplayEntity *model) { 
        model->angle += 3.0f;
        // đủ 360 độ sẽ quay về tính lại là 0
        if (model->angle > 360)
        {
            model->angle = 0;
        }
        // theo trục x và z thì côgn thức học cấp
        // 3 cho biết thế này:
        model->translatePoint.x = 3 * sin(model->angle*3.14/180);
        model->translatePoint.y = 3 * cos(model->angle*3.14/180);
    };
    displayEntidyList.push_back(earthModel);

    //------------------------------------------------------
    // 3.   Venus model
    //------------------------------------------------------
    DisplayEntity venusModel;
    venusModel.name = "Venus";
    venusModel.type = "collision_check";
    venusModel.modelRenderingFunc = [](DisplayEntity model) { 
        glPushMatrix();
        glTranslatef(model.translatePoint.x, model.translatePoint.y, model.translatePoint.z);
        glutWireSphere(0.5, 100, 80);
        glPopMatrix();
    };
    venusModel.modelUpdatingFunc = [](DisplayEntity *model) { 
        model->angle += 3.0f;
        // đủ 360 độ sẽ quay về tính lại là 0
        if (model->angle > 360)
        {
            model->angle = 0;
        }
        // 3 cho biết thế này:
        model->translatePoint.x = 3 * sin(model->angle*3.14/180);
        model->translatePoint.z = 3 * cos(model->angle*3.14/180);
    };
    displayEntidyList.push_back(venusModel);

    //------------------------------------------------------
    // 4.   Mars model
    //------------------------------------------------------
    DisplayEntity mars;
    mars.name = "Mars";
    mars.type = "collision_check";
    mars.modelRenderingFunc = [](DisplayEntity model) { 
        glPushMatrix();
        glTranslatef(model.translatePoint.x, model.translatePoint.y, model.translatePoint.z);
        glutWireSphere(0.5, 100, 80);
        glPopMatrix();
    };
    mars.modelUpdatingFunc = [](DisplayEntity *model) { 
        model->angle += 3.0f;
        // đủ 360 độ sẽ quay về tính lại là 0
        if (model->angle > 360)
        {
            model->angle = 0;
        }
        // theo trục y và z thì côgn thức học cấp
        // 3 cho biết thế này:
        model->translatePoint.y = 3 * sin(model->angle*3.14/180);
        model->translatePoint.z = 3 * cos(model->angle*3.14/180);
    };
    displayEntidyList.push_back(mars);

    //------------------------------------------------------
    // 5.   Line X model
    //------------------------------------------------------
    DisplayEntity lineXModel;
    lineXModel.name = "Line X";
    lineXModel.neighbors.push_back(&displayEntidyList.back());
    lineXModel.modelRenderingFunc = [](DisplayEntity model) { 
        glBegin(GL_LINES);
	    glVertex3f(-100, 0, 0);
	    glVertex3f(100, 0, 0);
	    glEnd();
    };
    displayEntidyList.push_back(lineXModel);

    //------------------------------------------------------
    // 6.   Line Y model
    //------------------------------------------------------
    DisplayEntity lineYModel;
    lineYModel.name = "Line Y";
    lineYModel.neighbors.push_back(&displayEntidyList.back());
    lineYModel.modelRenderingFunc = [](DisplayEntity model) { 
        glBegin(GL_LINES);
	    glVertex3f(0, -100, 0);
	    glVertex3f(0, 100, 0);
	    glEnd();
    };
    displayEntidyList.push_back(lineYModel);

    //------------------------------------------------------
    // 7.   Line Z model
    //------------------------------------------------------
    DisplayEntity lineZModel;
    lineZModel.name = "Line Z";
    lineZModel.neighbors.push_back(&displayEntidyList.back());
    lineZModel.modelRenderingFunc = [](DisplayEntity model) { 
        glBegin(GL_LINES);
	    glVertex3f(0, 0, -100);
	    glVertex3f(0, 0, 100);
	    glEnd();
    };
    displayEntidyList.push_back(lineZModel);


    return displayEntidyList;
}
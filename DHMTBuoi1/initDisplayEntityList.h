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
    /*DisplayEntity sunModel;
    sunModel.name = "sun";
    sunModel.setColor(1.0f, 0.0f, 0.0f);
    sunModel.modelRenderingFunc = [](DisplayEntity model) { 
        glPushMatrix();
        glutWireSphere(2.0, 50, 40);
        glPopMatrix();
    };
    displayEntidyList.push_back(sunModel);*/
    
    //------------------------------------------------------
    // 3.   Venus model
    //------------------------------------------------------
    DisplayEntity venusModel;
    venusModel.name = "venus";
    venusModel.type = "collision_check";
    venusModel.color = GLfloatColor::orangeColor();
    venusModel.modelRenderingFunc = [](DisplayEntity model) { 
        glPushMatrix();
        glTranslatef(model.translatePoint.x, model.translatePoint.y, model.translatePoint.z);
        glutWireSphere(1, 100, 80);
        glPopMatrix();
    };
    venusModel.modelUpdatingFunc = [](DisplayEntity *model) { 
        model->angle += 1.5f;
        // đủ 360 độ sẽ quay về tính lại là 0
        if (model->angle > 360)
        {
            model->angle = 0;
        }
        // 3 cho biết thế này:
        model->translatePoint.x = 5 * sin(model->angle*3.14/180);
        model->translatePoint.z = 5 * cos(model->angle*3.14/180);
    };
    //displayEntidyList.push_back(venusModel);

    //------------------------------------------------------
    // 2.   Earth model
    //------------------------------------------------------
    //DisplayEntity earthModel;
    //earthModel.name = "earth";
    //earthModel.type = "collision_check";
    //earthModel.color = GLfloatColor::greenColor();
    //earthModel.modelRenderingFunc = [](DisplayEntity model) { 
    //    glPushMatrix();
    //    glTranslatef(model.translatePoint.x, model.translatePoint.y, model.translatePoint.z);
    //    glRotatef(model.centerAngle, 0.0, 1.0, 0.0);
    //    glutWireSphere(0.5, 50, 10);
    //    glPopMatrix();
    //};
    //earthModel.modelUpdatingFunc = [](DisplayEntity *model) { 
    //    //quay quanh chinh no
    //    model->centerAngle += 10.0f;
    //    // đủ 360 độ sẽ quay về tính lại là 0
    //    if (model->centerAngle > 360)
    //    {
    //        model->centerAngle = 0;
    //        model->color = GLfloatColor::getRandomColor();
    //    }
    //    //
    //    model->angle += 1.0f;
    //    // đủ 360 độ sẽ quay về tính lại là 0
    //    if (model->angle > 360)
    //    {
    //        model->angle = 0;
    //    }
    //    // theo trục x và z thì côgn thức học cấp
    //    // 3 cho biết thế này:
    //    model->translatePoint.x = 3 * sin(model->angle*3.14/180);
    //    model->translatePoint.z = 3 * cos(model->angle*3.14/180);
    //};
    //displayEntidyList.push_back(earthModel);

    //------------------------------------------------------
    // 4.   Moon model
    //------------------------------------------------------
    //DisplayEntity moon;
    //moon.name = "moon";
    //moon.neighbors.push_back(&displayEntidyList.back());
    //moon.type = "collision_check";
    //moon.modelRenderingFunc = [](DisplayEntity model) { 
    //    glPushMatrix();
    //    glTranslatef(model.translatePoint.x, model.translatePoint.y, model.translatePoint.z);
    //    glutWireSphere(0.2, 100, 80);
    //    glPopMatrix();
    //};
    //moon.modelUpdatingFunc = [](DisplayEntity *model) { 
    //    model->angle += 30.0f;
    //    // đủ 360 độ sẽ quay về tính lại là 0
    //    if (model->angle > 360)
    //    {
    //        model->angle = 0;
    //    }
    //    // theo trục y và z thì côgn thức học cấp
    //    // 3 cho biết thế này:
    //    model->translatePoint.x = model->neighbors.back()->translatePoint.x + 1 * sin(model->angle*3.14/180);
    //    model->translatePoint.z = model->neighbors.back()->translatePoint.z + 1 * cos(model->angle*3.14/180);
    //};
    //displayEntidyList.push_back(moon);

    //------------------------------------------------------
    // 5.   Line X model
    //------------------------------------------------------
    DisplayEntity lineXModel;
    lineXModel.name = "Line X";
    lineXModel.setColor(1,0,0);
    //lineXModel.neighbors.push_back(&displayEntidyList.back());
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
    lineYModel.setColor(0, 1, 0);

    //lineYModel.neighbors.push_back(&displayEntidyList.back());
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
    lineZModel.setColor(0, 0, 1);

    //lineZModel.neighbors.push_back(&displayEntidyList.back());
    lineZModel.modelRenderingFunc = [](DisplayEntity model) { 
        glBegin(GL_LINES);
	    glVertex3f(0, 0, -100);
	    glVertex3f(0, 0, 100);
	    glEnd();
    };
    displayEntidyList.push_back(lineZModel);
    //------------------------------------------------------
   // 7.   Draw Gun
   //------------------------------------------------------
    DisplayEntity GunModel;
    GunModel.name = "Gun";
    GunModel.setColor(0, 0, 1);
    GunModel.setTranslatePoint(5.0f, 0.0f, 5.0f);
    GunModel.modelRenderingFunc = [](DisplayEntity model) {
        glPushMatrix();
        glTranslatef(model.translatePoint.x, model.translatePoint.y, model.translatePoint.z);
        glBegin(GL_QUADS);
        // Vẽ mặt trên 
        glNormal3d(0, 1, 0);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-1.0f, 0.0f, -1.0f);
        glVertex3f(-1.0f, 0.0f, 0.0f);
        // Vẽ mặt trước
        glNormal3d(0, 0, 1);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-1.0f, -1.0, 0.0f);
        glVertex3f(0.0f, -1.0f, 0.0f);
        // Vẽ mặt bên phải
        glNormal3d(1, 0, 0);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, -1.0f, 0.0f);
        glVertex3f(0.0f, -1.0f, -1.0f);
        glVertex3f(0.0f, 0.0f, -1.0f);
        // Vẽ mặt bên trái 
        glNormal3d(-1, 0, 0);
        glVertex3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-1.0f, 0.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        // Vẽ mặt dưới 
        glNormal3d(0, -1, 0);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        // Vẽ mặt sau 
        glNormal3d(0, 0, -1);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(-1.0f, 0.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(0.0f, -1.0f, -1.0f);
        glEnd();
        glPopMatrix(); // Quay lại trạng thái biến đổi đã lưu. 
    };
    displayEntidyList.push_back(GunModel);




    return displayEntidyList;
}
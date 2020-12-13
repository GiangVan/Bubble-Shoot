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


std::list<DisplayEntity*> initDisplayEntidyList() {
    std::list<DisplayEntity*> displayEntidyList = std::list<DisplayEntity*>();
    //------------------------------------------------------
    // 1.   Sun model
    //------------------------------------------------------
    DisplayEntity sunModel;
    sunModel.name = "Sun";
    sunModel.modelUpdatingFunc = [](DisplayEntity *model) { 
        model->angle += 1.0f;
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
    displayEntidyList.push_back(&sunModel);

    //------------------------------------------------------
    // 2.   Earth model
    //------------------------------------------------------
    DisplayEntity earthModel;
    earthModel.name = "Earth";
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
        model->translatePoint.z = 3 * cos(model->angle*3.14/180);
    };
    displayEntidyList.push_back(&earthModel);

    //------------------------------------------------------
    // 3.   Venus model
    //------------------------------------------------------
    DisplayEntity venusModel;
    venusModel.name = "Venus";
    venusModel.modelRenderingFunc = [](DisplayEntity model) { 
        glPushMatrix();
        glTranslatef(model.translatePoint.x, model.translatePoint.y, model.translatePoint.z);
        glutWireSphere(0.5, 100, 80);
        glPopMatrix();
    };
    venusModel.modelUpdatingFunc = [](DisplayEntity *model) { 
        //change color
        int maxColor = 100;
        int minColor = 10;
        model->setColor(
            (GLfloat)(rand() % (maxColor - minColor + 1) + minColor) / maxColor, 
            (GLfloat)(rand() % (maxColor - minColor + 1) + minColor) / maxColor, 
            (GLfloat)(rand() % (maxColor - minColor + 1) + minColor) / maxColor
        );
        //
        model->angle += 20.0f;
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
    displayEntidyList.push_back(&venusModel);

    //------------------------------------------------------
    // 4.   Moon model
    //------------------------------------------------------
    DisplayEntity moonModel;
    moonModel.name = "Moon";
    moonModel.neighbors.push_back(&earthModel);
    moonModel.modelRenderingFunc = [](DisplayEntity model) { 
        glPushMatrix();
        glTranslatef(
            model.neighbors.back()->translatePoint.x + model.translatePoint.x, 
            model.neighbors.back()->translatePoint.y + model.translatePoint.y, 
            model.neighbors.back()->translatePoint.z + model.translatePoint.z
        );
        glutWireSphere(0.1, 100, 80);
        glPopMatrix();
    };
    moonModel.setColor(0.0f, 1.0f, 0.0f);
    moonModel.modelUpdatingFunc = [](DisplayEntity *model) { 
        model->angle -= 30.0f;
        // đủ 360 độ sẽ quay về tính lại là 0
        if (model->angle > 360)
        {
            model->angle = 0;
        }
        // theo trục y và z thì côgn thức học cấp
        // 3 cho biết thế này:
        model->translatePoint.y = 1 * sin(model->angle*3.14/180);
        model->translatePoint.z = 1 * cos(model->angle*3.14/180);
    };
    displayEntidyList.push_back(&moonModel);


    return displayEntidyList;
}
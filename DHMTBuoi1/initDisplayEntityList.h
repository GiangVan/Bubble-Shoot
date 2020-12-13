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
#include <vector>;


std::vector<DisplayEntity> initDisplayEntidyList() {
    std::vector<DisplayEntity> displayEntidyList;
    //------------------------------------------------------
    // Model 1
    //------------------------------------------------------
    DisplayEntity a;
    a.name = "Sun";
    a.modelUpdatingFunc = [](DisplayEntity *model) { 
        model->angle = model->angle + 1;
        // đủ 360 độ sẽ quay về tính lại là 0
        if (model->angle > 360)
        {
            model->angle = 0;
        }
    };
    a.setColor(1.0, 0.0, 0.0);
    a.modelRenderingFunc = [](DisplayEntity model) { 
        glPushMatrix();
        glRotatef(model.angle, 0.0, 1.0, 0.0);
        glutWireSphere(2.0, 50, 40);
        glPopMatrix();
    };
    displayEntidyList.push_back(a);

    //------------------------------------------------------
    // Model 2
    //------------------------------------------------------
    a = DisplayEntity();
    a.name = "Earth";
    a.modelRenderingFunc = [](DisplayEntity model) { 
        glPushMatrix();
        glTranslatef(model.translatePoint.x, model.translatePoint.y, model.translatePoint.z);
        glutWireSphere(0.5, 100, 80);
        glPopMatrix();
    };
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
    // Model 3
    //------------------------------------------------------
    a = DisplayEntity();
    a.name = "Earth 2";
    a.modelRenderingFunc = [](DisplayEntity model) { 
        glPushMatrix();
        glTranslatef(model.translatePoint.x, model.translatePoint.y, model.translatePoint.z);
        glutWireSphere(0.5, 100, 80);
        glPopMatrix();
    };
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


    return displayEntidyList;
}
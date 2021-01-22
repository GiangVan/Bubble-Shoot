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
    // Line X model
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
    // Line Y model
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
    // Line Z model
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
    // Gun
    //------------------------------------------------------
    DisplayEntity GunModel;
    GunModel.name = "Gun";
    GunModel.size = 0.4f;
    GunModel.type.push_back(COLLISION_CHECK_TYPE);
    GunModel.type.push_back(MAIN_TYPE);
    GunModel.angle = 90;
    GunModel.setColor(0, 0, 1);
    GunModel.setTranslatePoint(5.0f, 0.0f + GunModel.size / 2, 5.0f);
    GunModel.modelUpdatingFunc = [](DisplayEntity *model) {
        if (model->angle < 360) {
            model->angle += 22;
        } else {
            model->angle = 0;
        }
    };
    GunModel.modelRenderingFunc = [](DisplayEntity model) {
        glPushMatrix();
        glTranslatef(model.translatePoint.x, model.translatePoint.y, model.translatePoint.z);
        
        glScalef(model.size, model.size, model.size);
        glRotatef(model.angle,1,1,1);
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
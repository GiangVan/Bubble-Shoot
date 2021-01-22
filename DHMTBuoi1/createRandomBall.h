#pragma once
#include "DisplayEntity.h";
#include "GLfloatColor.h";

DisplayEntity createRandomBall() {
    float ballRange = randomFloat(1, 10);
    DisplayEntity ball;
    if (ballRange > 5.0f) {
        ball.type.push_back(ENEMIES_TYPE);
        ball.color = GLfloatColor::redColor();
        ball.size = randomFloat(0.1f, 0.4f);
        ball.speed = randomFloat(0.1f, 0.5f);
    }
    else {
        ball.type.push_back(FOOD_TYPE);
        ball.color = GLfloatColor::greenColor();
        ball.size = randomFloat(0.05f, 0.7f);
        ball.speed = randomFloat(0.35f, 0.7f);
    }
    ball.type.push_back(COLLISION_CHECK_TYPE);
    ball.randomTranslatePoint(-10, 10, -5.0f);
    ball.translatePoint.y = 0;
    ball.modelRenderingFunc = [](DisplayEntity model) {
        glPushMatrix();
        glTranslatef(model.translatePoint.x, model.translatePoint.y, model.translatePoint.z);
        glutWireSphere(model.size, 50, 40);
        glPopMatrix();
    };
    ball.modelUpdatingFunc = [](DisplayEntity *model) {
        model->translatePoint.x += model->speed;
        model->translatePoint.z += model->speed;

        if (model->translatePoint.x > MAX_RANGE || model->translatePoint.z > MAX_RANGE) {
            model->status = REMOVED_STATUS;
        }
    };

    return ball;
}
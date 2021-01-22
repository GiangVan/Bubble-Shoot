#pragma once
#include "DisplayEntity.h";

float getScore(DisplayEntity entity) {
    float bonus1 = MINIMUM_SCORE * entity.speed;
    float bonus2 = MINIMUM_SCORE * 1 / entity.size;
    float score = MINIMUM_SCORE + bonus1 + bonus2;

    return score;
}
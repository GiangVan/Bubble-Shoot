#pragma once
#include "DisplayEntity.h";
#include "containsInStringList.h";
#include <string>;
#include <list>;
using namespace std;


void checkCollision(list<DisplayEntity> *entities, string type) {
    // init variables
    GLfloat range;
    GLfloat distance;
    list<DisplayEntity*> checkedEntities;
    for(DisplayEntity &item : *entities){    
        if (containsInStringList(item.type, COLLISION_CHECK_TYPE)) {
            checkedEntities.push_back(&item);
        }
    } 
    // do check
    for(DisplayEntity *item : checkedEntities){    
        for(DisplayEntity *sub_item : checkedEntities){    
            if (item != sub_item) {
                distance = sqrt(
                    pow(item->translatePoint.x - sub_item->translatePoint.x, 2) +
                    pow(item->translatePoint.y - sub_item->translatePoint.y, 2) +
                    pow(item->translatePoint.z - sub_item->translatePoint.z, 2)
                );

                range = (item->size + sub_item->size) - (item->size + sub_item->size) * 0.05f;
                if (distance < range) {
                    if ((containsInStringList(item->type, MAIN_TYPE) || containsInStringList(sub_item->type, MAIN_TYPE))) {
                        if (
                                (containsInStringList(item->type, MAIN_TYPE) && containsInStringList(sub_item->type, FOOD_TYPE)) || 
                                (containsInStringList(item->type, FOOD_TYPE) && containsInStringList(sub_item->type, MAIN_TYPE))
                            ) {
                            if (containsInStringList(item->type, MAIN_TYPE)) {
                                sub_item->status = REMOVED_STATUS;
                                score += getScore(*sub_item);

                                //item->size += item->size / 40;
                                item->color = GLfloatColor::getRandomColor();
                            }
                            else {
                                item->status = REMOVED_STATUS;
                                score += getScore(*item);

                                //sub_item->size += sub_item->size / 40;
                                sub_item->color = GLfloatColor::getRandomColor();
                            }
                        }
                        else {
                            if (containsInStringList(item->type, MAIN_TYPE)) {
                                sub_item->status = REMOVED_STATUS;
                                score -= getScore(*sub_item);

                             //   item->size -= item->size / 10;
                            }
                            else {
                                item->status = REMOVED_STATUS;
                                score -= getScore(*item);

                              //  sub_item->size -= sub_item->size / 10;
                            }
                        }

                    }
                    else {

                    }
                }
            }
        } 
    } 
}
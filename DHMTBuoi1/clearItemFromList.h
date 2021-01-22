#pragma once
#include "DisplayEntity.h";
#include <string>;
#include <list>;
using namespace std;

list<DisplayEntity> clearItemFromList(list<DisplayEntity> list) {
    std::list<DisplayEntity> newList;
    for (DisplayEntity item : list) {
        if (item.status != "removed") {
            newList.push_back(item);
        }
    }

    return newList;
}
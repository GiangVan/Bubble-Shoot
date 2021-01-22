#pragma once
#include <string>;
#include <list>;
using namespace std;

bool containsInStringList(list<std::string> ls, std::string value) {
    for(std::string item : ls){    
        if (item == value) return true;
    } 

    return false;
}
#pragma once
#include "sleep.h";
#include "getMilliCount.h";

void handleFrame(int beginframe) {
    int maxFrame = 25;
    int chuky = 1000 / maxFrame;
    int timeDiff = getMilliCount() - beginframe;
    if (timeDiff < chuky)
    {
        sleep(chuky - timeDiff);
    }
}
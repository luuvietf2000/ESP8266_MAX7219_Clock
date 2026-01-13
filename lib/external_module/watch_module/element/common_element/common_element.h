#pragma once

#ifndef common_element_h
#define commom_element_h

#include <Arduino.h>

class common_element
{
private:
    unsigned long timeStep;
    unsigned long currentTime;
    uint8 *matrix;
    uint32 size;
    void resetMatrix();
public:
    uint32 getSize();
    void setSize(const uint32 &size);
    common_element();
    void setTimeStep(const unsigned long &newTime);
    unsigned long getTimeStep();
    void updateCurrentTime();
    void setPixelMaxtrix(const uint32 &index, const uint32 &row, const uint8 &data);
    uint8 getPixel(const uint32 &index, const uint32 &row);
    bool isUpdate();
    uint8 *pointer();
    ~common_element();
};


#endif
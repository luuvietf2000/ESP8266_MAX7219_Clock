#include "common_element.h"

#define Row_Size 8
#define Column_Size 8

void common_element::setSize(const uint32 &size){
    matrix = new uint8[size * Row_Size];
    resetMatrix();
}
common_element::common_element(){
}

void common_element::setTimeStep(const unsigned long &newTime){
    timeStep = newTime;
}
unsigned long common_element::getTimeStep(){
    return timeStep;
}

void common_element::resetMatrix(){
    for(uint32 i = 0; i < size * Row_Size; i++)
        *(matrix + i) = 0;
}

void common_element::setPixelMaxtrix(const uint32 &index, const uint32 &row, const uint8 &data){
    *(matrix + index * Row_Size + row) = data;
}

uint8 common_element::getPixel(const uint32 &index, const uint32 &row){
    return *(matrix + index * Row_Size + row);
}

uint32 common_element::getSize(){
    return size;
}

uint8* common_element::pointer(){
    return matrix;
}

void common_element::updateCurrentTime(){
    currentTime = millis();
}

bool common_element::isUpdate(){
    bool updateState = millis() - currentTime >= timeStep;
    if(updateState)
        updateCurrentTime();
    return updateState;
}    

common_element::~common_element(){
    delete matrix;
}
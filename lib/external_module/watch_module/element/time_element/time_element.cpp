#include "watch_module/element/time_element/time_elemnet.h"
#include "watch_module/watch_data_in_flash.cpp"
#include "custom_module/time/time_rtc_custom.h"

void time_element::initParameter(parameterTimeUnit &parameter, uint8 &value){
    parameter.current = parameter.befor = value;
    parameter.animation = 0;
}

time_element::time_element() : common_element(){
}

uint32 time_element::matrixLength(){
    return SIZE_TIME_ELEMENT_MATRIX;
}

void time_element::init(const uint16 &timeStep, const uint32 index){
    indexUnit = index;
    setTimeStep(timeStep);
    setSize(SIZE_TIME_ELEMENT_MATRIX);
    tm m_time = getTmTime();
    initUnit(indexSecond, second, m_time.tm_sec);
    initUnit(indexMinute, minute, m_time.tm_min);
    initUnit(indexHour, hour, m_time.tm_hour);
}


void time_element::updateUnit(parameterTimeUnit &parameter, uint8 value){
    if(parameter.current != value){
        parameter.befor = parameter.current;
        parameter.current = value;
        parameter.animation = 0;
    }
}

void time_element::initMatrix(indexTimeMoudule index, uint8 &value){
    for(uint8 i = 0; i < SIZE_ANIMATION; i++){
        uint8 pixelOnePlace = pgm_read_byte(&pixelsTimeModule[getOnePlace(value)][i]);
        uint8 pixelTenPlace = pgm_read_byte(&pixelsTimeModule[getTenPlace(value)][i]);
        uint8 pixel = (pixelTenPlace << 1) | (pixelOnePlace << 5);
        setPixelMaxtrix(index, i, pixel);
    }
    for(uint8 i = SIZE_ANIMATION; i < 8; i++)
        setPixelMaxtrix(index, i, 0);
}

void time_element::initUnit(indexTimeMoudule index, parameterTimeUnit &parameter, uint8 value){
    initParameter(parameter, value);
    initMatrix(index, value);
}

uint8 time_element::getTimeUnit(indexTimeMoudule index){
    tm m_time = getTmTime();
    switch (index)
    {
        case indexSecond:
            return m_time.tm_sec;
        case indexMinute:
            return m_time.tm_min;
        case indexHour:
            return m_time.tm_hour;
    }
    return 0;
}

time_element::~time_element(){

}

uint8 time_element::getOnePlace(uint8 &value){
    return value % 10;
}
uint8 time_element::getTenPlace(uint8 &value){
    return value / 10;
}


void time_element::updateMatrix(parameterTimeUnit &parameter, indexTimeMoudule index){
    uint8 value = getTimeUnit(index);
    updateUnit(parameter, value);
    if(parameter.current != parameter.befor){
        for(uint8 i = 0; i < SIZE_ANIMATION; i++){
            uint8 isAreaChoose = i < (SIZE_ANIMATION - parameter.animation - 1);
            uint8 pixelOnesPlace = pgm_read_byte(&pixelsTimeModule[isAreaChoose ? getOnePlace(parameter.befor) : getOnePlace(parameter.current)][isAreaChoose ? parameter.animation + 1 + i : i - (SIZE_ANIMATION - parameter.animation - 1)]);
            uint8 pixelTensPlace = pgm_read_byte(&pixelsTimeModule[isAreaChoose ? getTenPlace(parameter.befor) : getTenPlace(parameter.current)][isAreaChoose ? parameter.animation + 1 + i : i - (SIZE_ANIMATION - parameter.animation - 1)]);
            uint8 pixel = (pixelTensPlace << 1) | (pixelOnesPlace << 5);
            setPixelMaxtrix(index, i, pixel);
        }
        parameter.animation++;
        if(parameter.animation == SIZE_ANIMATION){
            parameter.befor = parameter.current;
        }
    }
}

bool time_element::requestUpdate(){
    if(isUpdate()){
        updateMatrix(hour, indexHour);
        updateMatrix(minute, indexMinute);
        updateMatrix(second, indexSecond);
        return true;
    }
    return false;
}
#ifndef time_watch_h
#define time_watch_h

#define SIZE_TIME_ELEMENT_MATRIX 3
#define SIZE_ANIMATION 6

#include "watch_module/element/common_element/common_element.h"

typedef enum{
    indexSecond, 
    indexMinute,
    indexHour
} indexTimeMoudule;

typedef struct{
    uint8 current;
    uint8 befor;
    uint8 animation;
} parameterTimeUnit;

class time_element : public common_element
{
private:
    parameterTimeUnit second;
    parameterTimeUnit minute;
    parameterTimeUnit hour;
    uint32 indexUnit;
    void initParameter(parameterTimeUnit &parameter, uint8 &value);
    void updateMatrix(parameterTimeUnit &parameter, indexTimeMoudule index);
    uint8 getOnePlace(uint8 &value);
    uint8 getTenPlace(uint8 &value);
    void updateUnit(parameterTimeUnit &parameter, uint8 value);
    void initUnit(indexTimeMoudule index, parameterTimeUnit &parameter, uint8 value);
    void initMatrix(indexTimeMoudule index, uint8 &value);
    uint8 getTimeUnit(indexTimeMoudule index);
public:
    uint32 matrixLength();
    bool requestUpdate();
    time_element();
    ~time_element();
    void init(const uint16 &timeStep, const uint32 index);
};


#endif
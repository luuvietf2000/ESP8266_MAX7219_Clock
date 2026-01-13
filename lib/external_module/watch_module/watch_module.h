#ifndef watch_module_h
#define watch_module_h

#include "watch_module/interface/max7912/max7912.h"
#include "watch_module/element/time_element/time_elemnet.h"
#include "watch_module/element/decor_element/decor_element.h"

#define timeUnitIndex 0
#define decorUnitIndex 3

class watch_module : public max7912
{
private:
    time_element m_time;
    decor_element m_decor;
    void requestUpdateTimeModule();
    void requestUpdateDecorModule();
public:
    void begin(uint32 cs, uint32 length);
    void setTimeStepForTimeUnit(uint32 timeStep);
    void setTimeStepForDecorUnit(uint32 timeStep);
    void requestUpdate();
    watch_module();
    ~watch_module();
};



#endif
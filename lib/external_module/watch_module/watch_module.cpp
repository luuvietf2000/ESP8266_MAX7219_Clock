#include "watch_module/watch_module.h"

watch_module::watch_module() : max7912(){

}

void watch_module::begin(uint32 cs, uint32 length){
    max7912Begin(cs, length);
}

void watch_module::setTimeStepForTimeUnit(uint32 timeStep){
    m_time.init(timeStep, timeUnitIndex);
}
void watch_module::setTimeStepForDecorUnit(uint32 timeStep){
    m_decor.init(timeStep, decorUnitIndex);
}

void watch_module::requestUpdateTimeModule(){
    if(m_time.requestUpdate()){
        setMatrix(m_time.pointer(), timeUnitIndex, m_time.matrixLength());
    }
}
void watch_module::requestUpdateDecorModule(){
    if(m_decor.requestUpdate()){
        setMatrix(m_decor.pointer(), decorUnitIndex, decorUnitIndex + m_decor.matrixLenght());
    }
}
void watch_module::requestUpdate(){
    requestUpdateDecorModule();
    requestUpdateTimeModule();
}

watch_module::~watch_module(){

}
#include "watch_module/element/decor_element/decor_element.h"


decor_element::decor_element() : common_element(){
}

bool decor_element::isEndFrame(){
    return ++currentFrame >= frameLength;
}

void decor_element::init(const uint32 &timeStep, const uint32 &index){
    setSize(SIZE_DECOR_ELEMENT_MATRIX);
    setTimeStep(timeStep);
    currentFrame = frameLength = style = 0;
}

void decor_element::loadParameterStyle(){
    style = random(sizeof(varibleDecor) / sizeof(varibleDecor[0]));
    currentFrame = 0;
    frameLength = varibleDecor[style].size;
}

bool decor_element::requestUpdate(){
    if(isUpdate()){
        if(isEndFrame())
            loadParameterStyle();
        updateMatrix();
        return true;
    }
    return false;
}

uint32 decor_element::matrixLenght(){
    return SIZE_DECOR_ELEMENT_MATRIX;
}

void decor_element::updateMatrix(){
    for(uint8 i = 0; i < ROW_SIZE; i++){
        uint8 pixel = pgm_read_byte(varibleDecor[style].data + currentFrame * ROW_SIZE + 7 - i);
        setPixelMaxtrix(indexUnit, i, pixel);
    }
}

decor_element::~decor_element(){

}
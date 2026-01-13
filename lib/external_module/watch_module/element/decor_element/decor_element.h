#ifndef decor_element_h
#define decor_element_h

#include "watch_module/element/common_element/common_element.h"
#include "watch_module/watch_data_in_flash.cpp"


#define SIZE_DECOR_ELEMENT_MATRIX 1
#define ROW_SIZE 8

struct DecorData {
    const uint8* data;
    uint16_t size; 
};

const DecorData varibleDecor[] = {
    { pixelDecorStyle1, sizeof(pixelDecorStyle1) / sizeof(pixelDecorStyle1[0]) / ROW_SIZE},
    { pixelDecorStyle2, sizeof(pixelDecorStyle2) / sizeof(pixelDecorStyle2[0]) / ROW_SIZE},
    { pixelDecorStyle3, sizeof(pixelDecorStyle3) / sizeof(pixelDecorStyle3[0]) / ROW_SIZE},
    { pixelDecorStyle4, sizeof(pixelDecorStyle4) / sizeof(pixelDecorStyle4[0]) / ROW_SIZE},
    { pixelDecorStyle5, sizeof(pixelDecorStyle5) / sizeof(pixelDecorStyle5[0]) / ROW_SIZE},
};

class decor_element : public common_element
{
private:
    uint32 currentFrame;
    uint32 frameLength;
    uint32 style;
    uint32 indexUnit;
    bool isEndFrame();
    void loadParameterStyle();
    void updateMatrix();
    
public:
    void init(const uint32 &timeStep, const uint32 &index);
    bool requestUpdate();
    uint32 matrixLenght();
    decor_element();
    ~decor_element();
};


#endif
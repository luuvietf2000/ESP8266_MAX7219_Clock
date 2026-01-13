#ifndef common_strutc_h
#define common_strutc_h

#include <Arduino.h>

typedef struct{
    uint8 major;
    uint8 minor;
    uint8 patch;
} version;

typedef struct{
    char name[64];
    char psk[64];
} wifiParameter;

typedef struct{
    uint32 timeStepForTimeElement;
    uint32 timeStepForDecorElement;
    uint32 brightness;
} watchModuleParameter;


#endif
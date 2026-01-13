#ifndef max7912_h
#define max7912_h
#include <Arduino.h>
#include <SPI.h>
#include <functional>

#define SpiSpeed 10000000
#define OrderBit MSBFIRST
#define SpiMode SPI_MODE0
#define Register_Address_No_Op 0x00
#define Register_Address_Digit_0 0x01
#define Register_Address_Digit_1 0x02
#define Register_Address_Digit_2 0x03
#define Register_Address_Digit_3 0x04
#define Register_Address_Digit_4 0x05
#define Register_Address_Digit_5 0x06
#define Register_Address_Digit_6 0x07
#define Register_Address_Digit_7 0x08
#define Register_Address_Decode_Mode 0x09
#define Register_Address_Intensity 0x0A
#define Register_Address_Scan_Limit 0x0B
#define Register_Address_Shutdown 0x0C
#define Register_Address_Display_Test 0x0F
#define Size_Row 8
#define Shutdown_Mode 0x00
#define Normal_Operation 0x01

#define No_Decode 0x00
#define Column_User_Full 0x07

#define Intensity_Min 0x00
#define Intensity_Max 0x0F

#define Dislable_TestMode 0x00
#define Enable_TestMode 0x01
class max7912
{
private:
    uint32 size;
    uint32 csPin;
    void requestTranferParameter(uint8 address, uint8 data);
    void reset();
public:
    void max7912Begin(uint32 cs, uint32 length);
    void sendCommand(uint8 address, uint8 value);
    void setIntensity(uint8 brightness);
    void setDecodeMode(uint8 mode);
    void setShutdownMode(uint8 mode);
    void setScanLimit(uint8 mode);
    max7912();
    void setDisPlay(uint32 index, uint32 row, uint8 data);
    void setMatrix(uint8 *data, uint32 start, uint32 stop);
    void setDisplayTestMode(uint8 mode);
    ~max7912();
};
#endif
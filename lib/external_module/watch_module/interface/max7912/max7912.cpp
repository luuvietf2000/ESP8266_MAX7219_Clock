#include "max7912.h"

max7912::max7912(){
}
void max7912::max7912Begin(uint32 cs, uint32 length){
    csPin = cs;
    pinMode(cs, OUTPUT);
    digitalWrite(csPin, HIGH);
    size = length;
    SPI.begin();
    setDisplayTestMode(Dislable_TestMode);
    setIntensity(Intensity_Min);
    setShutdownMode(Normal_Operation);
    setDecodeMode(No_Decode);
    setScanLimit(Column_User_Full);
    reset();
}
void max7912::reset(){
    for(uint16 i = 0; i < size; i++)
        for(uint16 row = 0; row < 8; row++)
            setDisPlay(i, row, 0);
}
void max7912::sendCommand(uint8 address, uint8 value){
    SPI.transfer16(address << 8 | value);
}

void max7912::setIntensity(uint8 brightness){
    requestTranferParameter(Register_Address_Intensity, brightness);
}

void max7912::setDecodeMode(uint8 mode){
    requestTranferParameter(Register_Address_Decode_Mode, mode);
}

void max7912::setShutdownMode(uint8 mode){
    requestTranferParameter(Register_Address_Shutdown, mode);
}

void max7912::setScanLimit(uint8 mode){
    requestTranferParameter(Register_Address_Scan_Limit, mode);
}

void max7912::requestTranferParameter(uint8 address, uint8 data){
    SPI.beginTransaction(SPISettings(SpiSpeed, OrderBit, SpiMode));
    digitalWrite(csPin, LOW);
    for(uint32 i = 0; i < size; i++)
        sendCommand(address, data);
    digitalWrite(csPin, HIGH);
    SPI.endTransaction();
}

void max7912::setDisPlay(uint32 index, uint32 row, uint8 data){
    if(index >= size || row >= 8 )
    return;
    SPI.beginTransaction(SPISettings(SpiSpeed, OrderBit, SpiMode));
    uint32 address = row + Register_Address_Digit_0;
    digitalWrite(csPin, LOW);
    for(uint32 i = 0; i < size; i++){
        uint32 addr = i == index ? address : Register_Address_No_Op;  
        sendCommand(addr, data);
    }
    digitalWrite(csPin, HIGH);
    SPI.endTransaction();
}

void max7912::setDisplayTestMode(uint8 mode){
    requestTranferParameter(Register_Address_Display_Test, mode);
}

void max7912::setMatrix(uint8 *data, uint32 start, uint32 stop){
    SPI.beginTransaction(SPISettings(SpiSpeed, OrderBit, SpiMode));
    for(uint32 row = 0; row < 8; row++){
        uint32 address = row + Register_Address_Digit_0;
        digitalWrite(csPin, LOW);
        for(uint32 module = 0; module < size; module++){
            bool isNoOp = start <= module && module < stop ? false : true;
            uint8 rowAddress = isNoOp ? Register_Address_No_Op : address;
            uint8 value = isNoOp ? Register_Address_No_Op : *(data + (module - start) * Size_Row + row);
            sendCommand(rowAddress, value);
        }
        digitalWrite(csPin, HIGH);
    }
    SPI.endTransaction();

}
max7912::~max7912(){

}
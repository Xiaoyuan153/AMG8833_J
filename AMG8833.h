#ifndef _AMG8833_H
#define _AMG8833_H
#endif

#include <Wire.h>


#define AMG8833_ADDRESS 0x69

#define AMG8833_PCTL  0x00 //模式选择地址
#define AMG8833_NORMAL_MODE  0x00
#define AMG8833_SLEEP_MODE  0x01
#define AMG8833_STAND_BY_60 0x20
#define AMG8833_STAND_BY_10  0x21

/*
    0x00 = Normal Mode 普通模式
    0x01 = Sleep Mode  睡眠模式
    0x20 = Stand-by mode (60 sec intermittence) 待机模式 60 秒间歇
    0x21 = Stand-by mode (10 sec intermittence) 待机模式 10 秒间歇
*/

#define AMG8833_RST 0x01//重置寄存器
#define AMG8833_FLAG_RST 0x30
#define AMG8833_ALL_CLR_RST 0x04
#define AMG8833_INITIAL_RST 0x3F
/*    
    0x30 = flag reset (all clear status reg 0x04, interrupt flag and
    interrupt table) 0x3F = initial reset (brings flag reset and returns to
    initial setting)

*/  

#define AMG8833_FPSC 0x02
#define AMG8833_FPS_10 0x00 // 0x00 10FPS
#define AMG8833_FPS_1  0x01 // 0x01 1FPS

#define AMG8833_INTC  0x03 //数值模式选择
#define AMG8833_INT_ENABLE 0x01 //启用取整模式
#define AMG8833_INT_DISABLE 0x00 //不启用取整模式

#define AMG8833_REGISTER_TTHL 0x0E // Thermistor Output Value (Lower level)
#define AMG8833_REGISTER_TTHH 0x0F // Thermistor Output Value (Higher level)

#define AMG8833_BEGIN_L 0x80
#define AMG8833_END_H   0xFF

/*
  amg8833的像素寄存器起始于0x80结束于0xFF
  两个字节为一个数据点，将低八位和高八位结合
  在一起才是完整的一个数据点
*/
#define AMG8833_PIXEL_ARRAY_SIZE 64
#define AMG8833_PIXEL_TEMP_CONVERSION .25
#define AMG8833_THERMISTOR_CONVERSION .0625



class AMG8833 {
  public:
    //constructors
    AMG8833();
    //~AMG8833(void); //已弃用，没有必要
    unsigned int rawRect[AMG8833_PIXEL_ARRAY_SIZE];
    double realRect[AMG8833_PIXEL_ARRAY_SIZE];
    bool setProperty(uint16_t reg,uint8_t val);
    bool begin();
    double readThermistor();
    bool readAllPixels();
  private:
    
    bool write8(uint8_t data);
    uint8_t read8(uint16_t reg);
    uint16_t read16(uint16_t regL,uint16_t regH);
    //bool testConnected(); //已弃用，未低成本的实现
    

}; //必须要有这个分号
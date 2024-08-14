#include <AMG8833.h>
// void i2c_write(uint8_t dev_address ,uint8_t data){
//   Wire.beginTransmission(dev_address);
//   Wire.write(data);
//   Wire.endTransmission();
// }

// unsigned int i2c_read(uint8_t dev_address,uint8_t size){
//   Wire.requestFrom(dev_address,size);
//   while (Wire.available() == 0) {}
//   return Wire.read();
// }
AMG8833::AMG8833(void){
  memset(rawRect, 0, sizeof(unsigned int) * AMG8833_PIXEL_ARRAY_SIZE);
	memset(realRect, 0, sizeof(double) * AMG8833_PIXEL_ARRAY_SIZE);
  //防止矩阵干扰
}

bool AMG8833::write8(uint8_t val){
  Wire.beginTransmission(AMG8833_ADDRESS);
  Wire.write(val);
  Wire.endTransmission();
  return 1;
}
uint8_t AMG8833::read8(uint16_t reg){
  // Wire.beginTransmission(AMG8833_ADDRESS);
  // Wire.write(reg);
  // Wire.endTransmission();
  write8(reg);
  Wire.requestFrom(AMG8833_ADDRESS,1);
  while (Wire.available() == 0){}
  return Wire.read();
}


uint16_t AMG8833::read16(uint16_t regL,uint16_t regH){
  uint8_t Low8 = read8(regL);
  uint8_t High8 = read8(regH);
  uint16_t result = uint16_t(High8 << 8) | Low8;
  return result;

}
bool AMG8833::setProperty(uint16_t reg,uint8_t val){
  Wire.beginTransmission(AMG8833_ADDRESS);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
  return 1;
}
bool AMG8833::begin(){
  setProperty(AMG8833_PCTL,AMG8833_NORMAL_MODE);
  setProperty(AMG8833_RST,AMG8833_INITIAL_RST);
  setProperty(AMG8833_FPSC,AMG8833_FPS_10);
  setProperty(AMG8833_INTC,AMG8833_INT_DISABLE);
  //delay(2000);
  return 1;
}
double AMG8833::readThermistor(){
  return double(read16(AMG8833_REGISTER_TTHL,AMG8833_REGISTER_TTHH)) 
                * AMG8833_THERMISTOR_CONVERSION;
}
bool AMG8833::readAllPixels(){
  for (uint8_t i = 0;i < 128;i+=2){
    rawRect[i/2] = read16(AMG8833_BEGIN_L+i,AMG8833_BEGIN_L+i+1);
    realRect[i/2]= rawRect[i/2] * AMG8833_PIXEL_TEMP_CONVERSION;
  }
  return 1;
}

// bool AMG8833::testConnected(uint16_t addr){
//     write8(addr);
//     Wire.requestFrom(AMG8833_ADDRESS,1);
//     uint16_t count = 0;
//     bool stat = 1;
//     while (Wire.available() == 0){
//       delay(1);
//       count++;
//       if (count >= 2000){
//         stat=0;
//         break;
//       }
//     }
//     return stat;
// }

// AMG8833::~AMG8833(){
//   memset(rawRect, 0, sizeof(unsigned int) * AMG8833_PIXEL_ARRAY_SIZE);
// 	memset(realRect, 0, sizeof(double) * AMG8833_PIXEL_ARRAY_SIZE);
// }
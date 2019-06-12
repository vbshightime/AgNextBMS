#include<Wire.h>
#define ADDR 0x44
#define SDA
#define SCL

unsigned int data[6];

void i2Cinit(){
  Wire.requestFrom(ADDR,6);
  if(Wire.available() == 6){
      for(int i=0; i<=5; i++){
         data[i] = Wire.read();
        }
    }     
}

float readHumidity(){
  int humid = (data[3]*256) + data[4];
  float humidData = 100*(humid/65535);
  return humidData;     
}

float readTempC(){
  int temp = (data[0] * 256)+ data[1];
  float tempC = -45.0 + (175*temp/65535.0);
  return tempC; 
}

float readtempF(){
   int temp = (data[0] * 256)+ data[1];
   float tempF = -49.0 + (315*temp/65535.0);
   return tempF;
 }
 
void oneShotLow(){
  writeI2C(ADDR,0x2c,0x10);  
}

void oneShotMedium(){
  writeI2C(ADDR,0x2c,0x0d);
}

void oneShotHigh(){
  writeI2C(ADDR,0x2c,0x06);
} 

void writeI2C(int addr, int msb, int lsb){
  Wire.begin(SDA,SCL);  
  Wire.beginTransmission(addr);
  Wire.write(msb);
  Wire.write(lsb);
  Wire.endTransmission();  
}


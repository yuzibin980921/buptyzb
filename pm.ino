#include <Adafruit_Sensor.h>
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);//定义OLED连接方式
#include <SoftwareSerial.h>
SoftwareSerial mySerial(8, 9);
uint16_t pm25;
uint16_t pm10;
long  time;

void setup() {
  // put your setup code here, to run once:
mySerial.begin(9600);
  pmOn();
  delay(1000);
  pmOn();
}
void pmRead(void){
  uint8_t data[] = {0xAA,0x02,0x00,0x00,0x00,0x00,0x01,0x67,0xBB};
  //while(mySerial.available());
  mySerial.write(data,9);
  delay(100);
  for(int i=0;i<9;i++){
    if (mySerial.available()) {
      data[i] = mySerial.read();
    }
  }
  if(data[0]==0xAA && data[8]== 0xBB){
    pm25 = data[4]*256 + data[5];
    pm10 = data[2]*256 + data[3];
  
  }
}
void loop() {

  pmRead();  
    
   time=millis();
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
}

void pmOn(){

  uint8_t data[] = {0xAA,0x01,0x00,0x00,0x00,0x00,0x01,0x66,0xBB};
  mySerial.write(data,9);


}

void pmOff(){
  uint8_t data[] = {0xAA,0x03,0x00,0x00,0x00,0x00,0x01,0x68,0xBB};
  mySerial.write(data,9);
}
void draw(void) {
  u8g.setFont(u8g_font_unifont);//字体1
  //u8g.setPrintPos(0, 16);//字体坐标（x轴，y轴）
  //u8g.print("*_*Microduino*_*");//显示指定字符
  u8g.drawStr( 0, 16, "pm25");
  u8g.setFont(u8g_font_7x13);//字体2
  u8g.setPrintPos(0, 32);
  u8g.print(pm25);
  u8g.setPrintPos(0, 48);//换行显示须再定义
  u8g.print("pm10");//显示指定字符
  u8g.setPrintPos(0, 64);//换行显示须再定义
  u8g.print(pm10);//秒数计算
   u8g.setPrintPos(50, 16);//换行显示须再定义
  u8g.print("made");//秒数计算
  u8g.setPrintPos(50, 32);
  u8g.print("by");
  u8g.setPrintPos(50, 48);
  u8g.print("Team");
  u8g.setPrintPos(50, 64);
   u8g.print("Rocket");
}


#include <Arduino.h>
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
char A = 'c';

void ting()
{
  digitalWrite(12, 0); // 1
  digitalWrite(14, 0);

  digitalWrite(27, 0); // 2
  digitalWrite(26, 0);

  digitalWrite(17, 0); // 4
  digitalWrite(16, 0);

  digitalWrite(19, 0); // 3
  digitalWrite(18, 0);

  digitalWrite(25, 0);
  digitalWrite(15, 0); // 3
  digitalWrite(33, 0);
  digitalWrite(23, 0); // 3
}
void qianjing()
{
  digitalWrite(12, 0); // 1
  digitalWrite(14, 1);

  digitalWrite(27, 1); // 2
  digitalWrite(26, 0);

  digitalWrite(17, 1); // 4
  digitalWrite(16, 0);

  digitalWrite(19, 1); // 3
  digitalWrite(18, 0);

  digitalWrite(33, 1);
  digitalWrite(23, 1); // 3
}
void houtui()
{
  digitalWrite(12, 1); // 1
  digitalWrite(14, 0);

  digitalWrite(27, 0); // 2
  digitalWrite(26, 1);

  digitalWrite(17, 0); // 3
  digitalWrite(16, 1);

  digitalWrite(19, 0); // 4
  digitalWrite(18, 1);

  digitalWrite(25, 1);
  digitalWrite(15, 1); // 3
}
void youyi()
{
  digitalWrite(12, 1); // 1
  digitalWrite(14, 0);

  digitalWrite(27, 1); // 2
  digitalWrite(26, 0);

  digitalWrite(17, 0); // 4
  digitalWrite(16, 1);

  digitalWrite(19, 1); // 3
  digitalWrite(18, 0);

  digitalWrite(15, 1); // 3
  digitalWrite(23, 1); // 3
}
void zhuoyi()
{
  digitalWrite(12, 0); // 1
  digitalWrite(14, 1);

  digitalWrite(27, 0); // 2
  digitalWrite(26, 1);

  digitalWrite(17, 1); // 4
  digitalWrite(16, 0);

  digitalWrite(19, 0); // 3
  digitalWrite(18, 1);

  digitalWrite(25, 1);
  digitalWrite(33, 1);
}
void zhuoxuan()
{
  digitalWrite(12, 1); // 1
  digitalWrite(14, 0);

  digitalWrite(27, 1); // 2
  digitalWrite(26, 0);

  digitalWrite(17, 1); // 4
  digitalWrite(16, 0);

  digitalWrite(19, 0);
  digitalWrite(18, 1); // 3

  digitalWrite(23, 1); // 3
  digitalWrite(25, 1);
}
void youxuan()                             
{
  digitalWrite(12, 0); // 1
  digitalWrite(14, 1);

  digitalWrite(27, 0); // 2
  digitalWrite(26, 1);

  digitalWrite(17, 0); // 4
  digitalWrite(16, 1);

  digitalWrite(19, 1);
  digitalWrite(18, 0); // 3

  digitalWrite(15, 1);
  digitalWrite(33, 1);
}

void deng(int i)                             
{
  digitalWrite(23, i); 
  digitalWrite(25, i);
  digitalWrite(15, i);
  digitalWrite(33, i);
}

void setup()
{
  pinMode(2, OUTPUT);

  pinMode(33, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  digitalWrite(15, 1);
  digitalWrite(33, 1);
  delay(200);
  digitalWrite(15, 0);
  digitalWrite(33, 0);
  delay(400);
  digitalWrite(23, 1);
  digitalWrite(25, 1);
  delay(200);
  digitalWrite(23, 0);
  digitalWrite(25, 0);
  delay(200);
  digitalWrite(15, 1);
  digitalWrite(33, 1);
  digitalWrite(23, 1);
  digitalWrite(25, 1);
  delay(500);
  digitalWrite(15, 0);
  digitalWrite(33, 0);
  digitalWrite(23, 0);
  digitalWrite(25, 0);
  SerialBT.begin("ESP32小车");
}

void loop()
{
  if (SerialBT.available())
    A = SerialBT.read();
  switch (A)
  {
  case 'a':qianjing(); break;  //前
  case 'b':houtui();break;    //后
  case 'c':ting();break;        //停  
  case 'd':youyi(); break;     //右移
  case 'e':zhuoyi();break;    //左移
  case 'f':zhuoxuan();break;    //左旋
  case 'g':youxuan(); break;    //右旋
  case 'h':deng(1); break;     //开灯
  case 'j':deng(0); break;     //关灯
  }
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);
}
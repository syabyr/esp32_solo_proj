#include <Arduino.h>
#include "BluetoothSerial.h"
#include <esp_now.h>
#include <WiFi.h>

#define PWMC_TIMER_13_BIT  13
#define PWMC_BASE_FRE  2000
#define PWMC_CHANNEL_12 0
#define PWMC_CHANNEL_17 2
#define PWMC_CHANNEL_19 3
#define PWMC_CHANNEL_27 1
#define PWM_PIN12 12
#define PWM_PIN17 17
#define PWM_PIN19 19
#define PWM_PIN27 27

hw_timer_t * timer0 =NULL;
BluetoothSerial SerialBT;
char BleData;
int M1_PWM,M2_PWM,M3_PWM,M4_PWM;
int L_X,L_Y,R_X,R_Y;

void PWM_Write(uint8_t channel, uint32_t value, uint32_t valueMax = 255) 
{
uint32_t duty = (8191 / valueMax) * min(value, valueMax);
ledcWrite(channel, duty);
}

// 创建一个结构体接收数据
typedef struct struct_message {
  int LX;
  int LY;
  int RX;
  int RY;
} struct_message;

// 创建一个结构体变量
struct_message myData;

void M_Init()
{
  //PWM初始化
  ledcSetup(PWMC_CHANNEL_12, PWMC_BASE_FRE, PWMC_TIMER_13_BIT);
  ledcAttachPin(PWM_PIN12, PWMC_CHANNEL_12);
  ledcSetup(PWMC_CHANNEL_27, PWMC_BASE_FRE, PWMC_TIMER_13_BIT);
  ledcAttachPin(PWM_PIN27, PWMC_CHANNEL_27);
  ledcSetup(PWMC_CHANNEL_17, PWMC_BASE_FRE, PWMC_TIMER_13_BIT);
  ledcAttachPin(PWM_PIN17, PWMC_CHANNEL_17);
  ledcSetup(PWMC_CHANNEL_19, PWMC_BASE_FRE, PWMC_TIMER_13_BIT);
  ledcAttachPin(PWM_PIN19, PWMC_CHANNEL_19);
  //电机引脚初始
  pinMode(14, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(18, OUTPUT);
  //LED引脚初始
  pinMode(33, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(23, OUTPUT);
  //开机自检
  digitalWrite(14,LOW);
  digitalWrite(26,LOW);
  digitalWrite(16,LOW);
  digitalWrite(18,LOW);
  PWM_Write(PWMC_CHANNEL_12,25);
  PWM_Write(PWMC_CHANNEL_27,25);
  PWM_Write(PWMC_CHANNEL_17,25);
  PWM_Write(PWMC_CHANNEL_19,25);
  digitalWrite(15, 1);
  digitalWrite(33, 1);
  delay(200);
  PWM_Write(PWMC_CHANNEL_12,0);
  PWM_Write(PWMC_CHANNEL_27,0);
  PWM_Write(PWMC_CHANNEL_17,0);
  PWM_Write(PWMC_CHANNEL_19,0);
  digitalWrite(15, 0);
  digitalWrite(33, 0);
  delay(400);
  PWM_Write(PWMC_CHANNEL_12,25);
  PWM_Write(PWMC_CHANNEL_27,25);
  PWM_Write(PWMC_CHANNEL_17,25);
  PWM_Write(PWMC_CHANNEL_19,25);
  digitalWrite(23, 1);
  digitalWrite(25, 1);
  delay(200);
  PWM_Write(PWMC_CHANNEL_12,0);
  PWM_Write(PWMC_CHANNEL_27,0);
  PWM_Write(PWMC_CHANNEL_17,0);
  PWM_Write(PWMC_CHANNEL_19,0);
  digitalWrite(23, 0);
  digitalWrite(25, 0);
  delay(200);
  PWM_Write(PWMC_CHANNEL_12,25);
  PWM_Write(PWMC_CHANNEL_27,25);
  PWM_Write(PWMC_CHANNEL_17,25);
  PWM_Write(PWMC_CHANNEL_19,25);
  digitalWrite(15, 1);
  digitalWrite(33, 1);
  digitalWrite(23, 1);
  digitalWrite(25, 1);
  delay(500);
  PWM_Write(PWMC_CHANNEL_12,0);
  PWM_Write(PWMC_CHANNEL_27,0);
  PWM_Write(PWMC_CHANNEL_17,0);
  PWM_Write(PWMC_CHANNEL_19,0);
  digitalWrite(15, 0);
  digitalWrite(33, 0);
  digitalWrite(23, 0);
  digitalWrite(25, 0);
}

 void jianshou()
{
   if(SerialBT.available()) 
  {
    BleData = SerialBT.read();
    if(BleData=='L')
    {
      while (BleData!='*')
      {
        if(SerialBT.available())
        {
          BleData=SerialBT.read();  
          if(BleData=='X') myData.LX = SerialBT.parseInt();
          if(BleData=='Y') myData.LY = SerialBT.parseInt();
        }
      }
    }

    if(BleData=='R')
    {
      while (BleData!='*')
      {
        if(SerialBT.available())
        {
          BleData=SerialBT.read();   
          if(BleData=='X') myData.RX = SerialBT.parseInt();
          if(BleData=='Y') myData.RY = SerialBT.parseInt();
        }
      }
    }
  }
          BleData='0';
          SerialBT.flush();
}

void M1(int i)//M1
{
  if(i<-2)
  {
    PWM_Write(PWMC_CHANNEL_27,255-abs(i));
    digitalWrite(26, 1);
  }
  if(i>2)
  {
    PWM_Write(PWMC_CHANNEL_27,i);
    digitalWrite(26, 0);
  }
}

void M2(int i)//M2
{
  if(i<-2)
  {
    PWM_Write(PWMC_CHANNEL_12,255-abs(i));
    digitalWrite(14, 1);
  }  
  if(i>2)
  {
    PWM_Write(PWMC_CHANNEL_12,i);
    digitalWrite(14, 0);
  }
}

void M3(int i)//M3
{
  if(i<-2)
  {
    PWM_Write(PWMC_CHANNEL_17,255-abs(i));
    digitalWrite(16, 1);
  }  
  if(i>2)
  {
    PWM_Write(PWMC_CHANNEL_17,i);
    digitalWrite(16, 0);
  }
}

void M4(int i)//M4
{
  if(i<-2)
  {
    PWM_Write(PWMC_CHANNEL_19,255-abs(i));
    digitalWrite(18, 1);
  }  
  if(i>2)
  {
    PWM_Write(PWMC_CHANNEL_19,i);
    digitalWrite(18, 0);
  }
}

void M1234()//停车
{
    PWM_Write(PWMC_CHANNEL_19,0);
    digitalWrite(18, 0);
    PWM_Write(PWMC_CHANNEL_17,0);
    digitalWrite(16, 0);
    PWM_Write(PWMC_CHANNEL_12,0);
    digitalWrite(14, 0);
    PWM_Write(PWMC_CHANNEL_27,0);
    digitalWrite(26, 0);
} 

void IRAM_ATTR Timer0() 
{
//数据映射
   L_X = map( myData.LX, 0, 4096, -255, 255);
   L_Y = map( myData.LY, 0, 4096, -255, 255);
   R_X = map( myData.RX, 0, 4096, -255, 255);
   R_Y = map( myData.RY, 0, 4096, -255, 255);
//PWM计算
   M1_PWM = - R_Y - R_X + L_X;
   M2_PWM = - R_Y + R_X - L_X;
   M3_PWM = - R_Y + R_X + L_X;
   M4_PWM = - R_Y - R_X - L_X;
   if(M1_PWM>255)  M1_PWM=255;
   if(M1_PWM<-255) M1_PWM=-255;
   if(M2_PWM>255)  M2_PWM=255; 
   if(M2_PWM<-255) M2_PWM=-255;
   if(M3_PWM>255)  M3_PWM=255;
   if(M3_PWM<-255) M3_PWM=-255;
   if(M4_PWM>255)  M4_PWM=255;
   if(M4_PWM<-255) M4_PWM=-255;

//PWM输出到电机
     if(myData.LX+myData.LY==4096&&myData.RX+myData.RY==4096)
     {
        M1234();
        digitalWrite(15, 0);
        digitalWrite(33, 0);
        digitalWrite(23, 0);
        digitalWrite(25, 0);
     }else{
        M1(M1_PWM);
        M2(M2_PWM);
        M3(M3_PWM);
        M4(M4_PWM);
        digitalWrite(15, 1);
        digitalWrite(33, 1);
        digitalWrite(23, 1);
        digitalWrite(25, 1);
     }
}

// 回调函数,当收到消息时会调佣该函数
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  // Serial.println(myData.LX);
  // Serial.println(myData.LY);
  // Serial.println(myData.RX);
  // Serial.println(myData.RY);
  // Serial.println();
}

void setup()
{
  M_Init();
  //开启蓝牙
  SerialBT.begin("ESP32_小车"); 
  // 初始化串口波特率
  Serial.begin(115200);
  // 设置wifi模式
  WiFi.mode(WIFI_STA);
  // 初始化esp-now
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //注册接收信息的回调函数
  esp_now_register_recv_cb(OnDataRecv);
  //初始化定时器
  timer0=timerBegin(0, 80, true);
  timerAttachInterrupt(timer0, &Timer0, true);
  timerAlarmWrite(timer0, 10000, true);
  timerAlarmEnable(timer0);
}

void loop()
{
  jianshou();
}
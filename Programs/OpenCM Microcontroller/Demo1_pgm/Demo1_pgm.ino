#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 2  //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 3  //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#define ID1 2
#define ID2 1
#define S1  16
#define S2  17
#define S3  18
#define M1  21
#define M2  22

int sen[3];

Dynamixel Dxl(DXL_BUS_SERIAL1);
void setup()
{
SerialUSB.begin();

Dxl.begin(3);
Dxl.wheelMode(ID1);
Dxl.wheelMode(ID2);
pinMode(S1, INPUT);
pinMode(S2, INPUT);
pinMode(S3, INPUT);
pinMode(M1, OUTPUT);
pinMode(M2, OUTPUT);
SerialUSB.attachInterrupt(MOTOR_VALUES);
pinMode(BOARD_LED_PIN, OUTPUT);
}


void loop() 
{
  if(digitalRead(S1)==LOW)
    sen[0]=2;
  else
    sen[0]=1;
  if(digitalRead(S2)==LOW)
    sen[1]=2;
  else
    sen[1]=1;
  if(digitalRead(S3)==LOW)
    sen[2]=2;
  else
    sen[2]=1;
  int Sen_val= ((sen[0]*100)+(sen[1]*10)+(sen[2]));
  SerialUSB.println(Sen_val);
  delay(100);
}
 
void MOTOR_VALUES( byte* buffer, byte n)
{
//To convert the value to ASCII
int Mod_val_M1 = ((buffer[0]-48)*1000)+((buffer[1]-48)*100)+((buffer[2]-48)*10)+(buffer[3]-48);
int Mod_val_M2 = ((buffer[5]-48)*1000)+((buffer[6]-48)*100)+((buffer[7]-48)*10)+(buffer[8]-48);

//Setting Motor Speeds
Dxl.goalSpeed(ID1, Mod_val_M1);
Dxl.goalSpeed(ID2, Mod_val_M2);
delay(100);
}


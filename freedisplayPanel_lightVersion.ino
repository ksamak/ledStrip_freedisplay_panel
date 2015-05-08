
/*
  code by Ksamak, not yet licenced
  
  Blue = 5V
  Red = SDI
  Green = CKI
  Black = GND
*/
 
 
#define COMMAND_LENGTH 512
#define STRIP_LENGTH 32  // usually 32 LEDs on one strip, tested with 128.
#define STRIP_NUMBER 7  // number of ledStrips

/////////TODO Do better!!! when object oriented, and in REAL CPP!!!!
////////////////////////////////////////////////////////////////////

char payload[COMMAND_LENGTH];

const int  carwidth = 5;
byte font[][5] = {
		{0x00,0x00,0x00,0x00,0x00},   //   0x20 32
		{0x00,0x00,0x6f,0x00,0x00},   // ! 0x21 33
		{0x00,0x07,0x00,0x07,0x00},   // " 0x22 34
		{0x14,0x7f,0x14,0x7f,0x14},   // # 0x23 35
		{0x00,0x07,0x04,0x1e,0x00},   // $ 0x24 36
		{0x23,0x13,0x08,0x64,0x62},   // % 0x25 37
		{0x36,0x49,0x56,0x20,0x50},   // & 0x26 38
		{0x00,0x00,0x07,0x00,0x00},   // ' 0x27 39
		{0x00,0x1c,0x22,0x41,0x00},   // ( 0x28 40
		{0x00,0x41,0x22,0x1c,0x00},   // ) 0x29 41
		{0x14,0x08,0x3e,0x08,0x14},   // * 0x2a 42
		{0x08,0x08,0x3e,0x08,0x08},   // + 0x2b 43
		{0x00,0x50,0x30,0x00,0x00},   // , 0x2c 44
		{0x08,0x08,0x08,0x08,0x08},   // - 0x2d 45
		{0x00,0x60,0x60,0x00,0x00},   // . 0x2e 46
		{0x20,0x10,0x08,0x04,0x02},   // / 0x2f 47
		{0x3e,0x51,0x49,0x45,0x3e},   // 0 0x30 48
		{0x00,0x42,0x7f,0x40,0x00},   // 1 0x31 49
		{0x42,0x61,0x51,0x49,0x46},   // 2 0x32 50
		{0x21,0x41,0x45,0x4b,0x31},   // 3 0x33 51
		{0x18,0x14,0x12,0x7f,0x10},   // 4 0x34 52
		{0x27,0x45,0x45,0x45,0x39},   // 5 0x35 53
		{0x3c,0x4a,0x49,0x49,0x30},   // 6 0x36 54
		{0x01,0x71,0x09,0x05,0x03},   // 7 0x37 55
		{0x36,0x49,0x49,0x49,0x36},   // 8 0x38 56
		{0x06,0x49,0x49,0x29,0x1e},   // 9 0x39 57
		{0x00,0x36,0x36,0x00,0x00},   // : 0x3a 58
		{0x00,0x56,0x36,0x00,0x00},   // ; 0x3b 59
		{0x08,0x14,0x22,0x41,0x00},   // < 0x3c 60
		{0x14,0x14,0x14,0x14,0x14},   // = 0x3d 61
		{0x00,0x41,0x22,0x14,0x08},   // > 0x3e 62
		{0x02,0x01,0x51,0x09,0x06},   // ? 0x3f 63
		{0x3e,0x41,0x5d,0x49,0x4e},   // @ 0x40 64
		{0x7e,0x09,0x09,0x09,0x7e},   // A 0x41 65
		{0x7f,0x49,0x49,0x49,0x36},   // B 0x42 66
		{0x3e,0x41,0x41,0x41,0x22},   // C 0x43 67
		{0x7f,0x41,0x41,0x41,0x3e},   // D 0x44 68
		{0x7f,0x49,0x49,0x49,0x41},   // E 0x45 69
		{0x7f,0x09,0x09,0x09,0x01},   // F 0x46 70
		{0x3e,0x41,0x49,0x49,0x7a},   // G 0x47 71
		{0x7f,0x08,0x08,0x08,0x7f},   // H 0x48 72
		{0x00,0x41,0x7f,0x41,0x00},   // I 0x49 73
		{0x20,0x40,0x41,0x3f,0x01},   // J 0x4a 74
		{0x7f,0x08,0x14,0x22,0x41},   // K 0x4b 75
		{0x7f,0x40,0x40,0x40,0x40},   // L 0x4c 76
		{0x7f,0x02,0x0c,0x02,0x7f},   // M 0x4d 77
		{0x7f,0x04,0x08,0x10,0x7f},   // N 0x4e 78
		{0x3e,0x41,0x41,0x41,0x3e},   // O 0x4f 79
		{0x7f,0x09,0x09,0x09,0x06},   // P 0x50 80
		{0x3e,0x41,0x51,0x21,0x5e},   // Q 0x51 81
		{0x7f,0x09,0x19,0x29,0x46},   // R 0x52 82
		{0x46,0x49,0x49,0x49,0x31},   // S 0x53 83
		{0x01,0x01,0x7f,0x01,0x01},   // T 0x54 84
		{0x3f,0x40,0x40,0x40,0x3f},   // U 0x55 85
		{0x0f,0x30,0x40,0x30,0x0f},   // V 0x56 86
		{0x3f,0x40,0x30,0x40,0x3f},   // W 0x57 87
		{0x63,0x14,0x08,0x14,0x63},   // X 0x58 88
		{0x07,0x08,0x70,0x08,0x07},   // Y 0x59 89
		{0x61,0x51,0x49,0x45,0x43},   // Z 0x5a 90
		{0x3c,0x4a,0x49,0x29,0x1e},   // [ 0x5b 91
		{0x02,0x04,0x08,0x10,0x20},   // \ 0x5c 92
		{0x00,0x41,0x7f,0x00,0x00},   // ] 0x5d 93
		{0x04,0x02,0x01,0x02,0x04},   // ^ 0x5e 94
		{0x40,0x40,0x40,0x40,0x40},   // _ 0x5f 95
		{0x00,0x00,0x03,0x04,0x00},   // ` 0x60 96
		{0x20,0x54,0x54,0x54,0x78},   // a 0x61 97
		{0x7f,0x48,0x44,0x44,0x38},   // b 0x62 98
		{0x38,0x44,0x44,0x44,0x20},   // c 0x63 99
		{0x38,0x44,0x44,0x48,0x7f},   // d 0x64 100
		{0x38,0x54,0x54,0x54,0x18},   // e 0x65 101
		{0x08,0x7e,0x09,0x01,0x02},   // f 0x66 102
		{0x0c,0x52,0x52,0x52,0x3e},   // g 0x67 103
		{0x7f,0x08,0x04,0x04,0x78},   // h 0x68 104
		{0x00,0x44,0x7d,0x40,0x00},   // i 0x69 105
		{0x20,0x40,0x44,0x3d,0x00},   // j 0x6a 106
		{0x00,0x7f,0x10,0x28,0x44},   // k 0x6b 107
		{0x00,0x41,0x7f,0x40,0x00},   // l 0x6c 108
		{0x7c,0x04,0x18,0x04,0x78},   // m 0x6d 109
		{0x7c,0x08,0x04,0x04,0x78},   // n 0x6e 110
		{0x38,0x44,0x44,0x44,0x38},   // o 0x6f 111
		{0x7c,0x14,0x14,0x14,0x08},   // p 0x70 112
		{0x08,0x14,0x14,0x18,0x7c},   // q 0x71 113
		{0x7c,0x08,0x04,0x04,0x08},   // r 0x72 114
		{0x48,0x54,0x54,0x54,0x20},   // s 0x73 115
		{0x04,0x3f,0x44,0x40,0x20},   // t 0x74 116
		{0x3c,0x40,0x40,0x20,0x7c},   // u 0x75 117
		{0x1c,0x20,0x40,0x20,0x1c},   // v 0x76 118
		{0x3c,0x40,0x30,0x40,0x3c},   // w 0x77 119
		{0x44,0x28,0x10,0x28,0x44},   // x 0x78 120
		{0x0c,0x50,0x50,0x50,0x3c},   // y 0x79 121
		{0x44,0x64,0x54,0x4c,0x44},   // z 0x7a 122
		{0x00,0x08,0x36,0x41,0x41},   // { 0x7b 123
		{0x00,0x00,0x7f,0x00,0x00},   // | 0x7c 124
		{0x41,0x41,0x36,0x08,0x00},   // } 0x7d 125
		{0x04,0x02,0x04,0x08,0x04},   // ~ 0x7e 126
	};

///////////// END OF TODO BETTER /////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// ledStrip part


//short int pin_config[STRIP_NUMBER];
unsigned  pin_config[STRIP_NUMBER];
//TODO : change to use only HEX. when higher functions are done
unsigned short strip_rgb_colors[STRIP_NUMBER][STRIP_LENGTH];

int SDI = 4; //Red wire (not the red 5V wire!)
int CKI = 5; //Green wire - Clock
int ledPin = 13; //On board LED
int cpt; //hBeatCpt;
//char serialIn;

//char comm[4], arg1[3], arg2[3], arg3[3], arg4[3], arg5[3], arg6[3];

int mainDelay = 1;  //min = 1
boolean messageRunning = true;

String messageString = "    Marche de Noel de l'elaboratoire. du 15 au 25 decembre.   ";
/*
String messageList[4];
messageList[0]  = "L'Elaboratoire a 15ans!    place du parlement ";
messageList[1] = "vendredi a 18h" // Apero, Fanfare, Spectacles.
messageList[2] = "samedi a 14h"   // spectacles de rue, Balucadas, dance, cirque, films, Cabaret. 
messageList[3] = "Dimanche a 15h"   // musique, theatre, magie, Projections.     ";
*/

short int currentColor = 0b000000000000;
short int currentColor2 = 0b111111111111;

void setup() {
  // outputs are from 2 to 9, skipping clock pin 5. 
  pin_config[0]=2;
  pin_config[1]=3;
  pin_config[2]=4;
  pin_config[3]=6;
  pin_config[4]=7;
  pin_config[5]=8;
  pin_config[6]=9;

  Serial.begin(9600);
  for (int i=0; i<7; i++){
  pinMode(pin_config[i], OUTPUT);
  }
  pinMode(CKI, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
/*  for(short int x = 0; x < COMMAND_LENGTH ; x++){
    payload[x]='\0';
    //payload_orig[x]='\0';
  }
  */
  
  for(byte x = 0 ; x < STRIP_NUMBER ; x++){
    for(byte y = 0 ; y < STRIP_LENGTH ; y++){
      strip_rgb_colors[x][y] = 0;
    }
  }
  
  //post_frame(); //Push the current color frame to the strip
  randomSeed(analogRead(0));
  delay(1000);
  Serial.println("setup passed");  
}

void loop() {     // Whito 255, 255, 160
    if(Serial.available()){
      char length;
      char type = checkIncomingSerial(&length, payload);  //TODO => checkIncomingXBee()
      treatIncoming(type, length, payload);
    }
    if (messageRunning){
      displayNextRow();
    }
    delay(mainDelay);
}
/*
  if (parseXPLMessage(payload, xPLMess)){
    //xPLCmd(xPLMess);
    //sendTrigger()
  }*/  


#define MESSAGE 1
#define COLOR 2
#define ANIMATE 3
#define DELAY 4


// TLV type lenth value
char checkIncomingSerial(char* length, char value[]){
  if ( !Serial.available()) {
    return -1;
  }
  // Get type
  char typeVal = Serial.read();
  char lengthVal = Serial.read();
  length = &lengthVal;
  if (lengthVal <= COMMAND_LENGTH) {
    Serial.readBytes(payload, lengthVal);
  } else {
    Serial.flush();
  }

  Serial.print("type: ");
  Serial.println(typeVal, DEC);
  Serial.print("len:  ");
  Serial.println(lengthVal, DEC);
  Serial.println(payload);
  return typeVal;
}

void treatIncoming(char type, char length, char value[]){
  if (type == MESSAGE) {
    messageString = "   ";
    messageString.concat(payload);
    messageString.concat("   ");
  } else if (type == COLOR){
    if (length != 6) {
      Serial.println("E2");
    }
  }
}


unsigned short matrixShift = 0;
char messageShift = 0;
char caracterShift = 0;
boolean temp;

void displayNextRow(){  
  
  for (byte i = 0; i < STRIP_NUMBER; i++){
    temp = font[messageString[messageShift]-32][caracterShift] & 1 << (STRIP_NUMBER-i-1);
    if(temp && caracterShift != 5){strip_rgb_colors[i][matrixShift] = currentColor;}
    else{strip_rgb_colors[i][matrixShift] = 0b0;}
  }

  post_frame(matrixShift+1);

  matrixShift = (matrixShift + 1) % STRIP_LENGTH;
  caracterShift = (caracterShift + 1) % (5+1);

  if(caracterShift == 0){
    currentColor = currentColor2 - random(5)*(0b1 + 0b10000 +0b100000000);
//    Serial.println(currentColor, BIN);
    messageShift = (messageShift + 1) % messageString.length();
    if(messageShift == 0){
        messageShift = (messageShift + 1) % messageString.length();
        currentColor2 = (0 + random(16))*0b1 + (0 + random(16))*0b10000 + (0 + random(16))*0b100000000;
        //Serial.println(currentColor2, BIN);
    }
    //reset next line blank.
/*    for (byte i = 0; i < STRIP_NUMBER; i++){
      strip_rgb_colors[i][matrixShift] = 0b0;
    }
    matrixShift = (matrixShift + 1) % STRIP_LENGTH;
*/
  }
}

/*
void simpleCmd(char *payload){
  
  for (int i=0; i<3; i++){
    comm[i]='\0';
    arg1[i]='\0';
    arg2[i]='\0';
    arg3[i]='\0';
    arg4[i]='\0';
    arg5[i]='\0';
    arg6[i]='\0';
  }

  
  cpt=0;
  while(payload[cpt]!='@' && cpt < COMMAND_LENGTH){
    cpt++;
  }
  cpt++;
  
  comm[0]=payload[cpt];
  comm[1]=payload[cpt+1];
  comm[2]=payload[cpt+2];
  comm[3]='\0';
  
  if (strcmp("ONN", comm) == 0){
    on();
  }
  if (strcmp(comm, "WHI") == 0){
    setColor("WHITE");
  }
  else if (strcmp(comm, "OFF") == 0){
    off();
  }
  else if (strcmp(comm, "SET") == 0){
    simpleCmd_evalArgs();
    setVar(arg1, atoi(arg2));
  }
  else if(strcmp(comm, "COL") == 0){
    simpleCmd_evalArgs();
    setMainColor(atoi(arg1), atoi(arg2), atoi(arg3));
  }
  else if (strcmp(comm, "CHR") == 0){
    christmastime();
  }
  else if (strcmp(comm, "PUL") == 0){
    simpleCmd_evalArgs();
    pulse_rgb(atoi(arg1),atoi(arg2),atoi(arg3),atoi(arg4),atoi(arg5),atoi(arg6));
  }
//  else if (strcmp(comm, "DIM") == 0){
//    fade(1);
//  }
//  else if (strcmp(comm, "FAD") == 0){
//    simpleCmd_evalArgs();
//    fade_to_time(atoi(arg1),atoi(arg2),atoi(arg3),atoi(arg4),atoi(arg5));
//  }
  else if (strcmp(comm, "ALL") == 0){
    simpleCmd_evalArgs();
    set_all(atoi(arg1),atoi(arg2),atoi(arg3));
  }
  else if (strcmp(comm, "MSG") == 0){
    messageString = payloadGetMessage();
    Serial.println(messageString);
  }
  
  else {
    //Serial.println(comm);
    comm[0] = 'E';
    comm[1] = 'R';
    comm[2] = 'R';
    comm[3] = '\0';
  }
  
  Serial.println(comm);  
 

  for(byte x = 0; x < COMMAND_LENGTH ; x++){
//    Serial.println(payload);
    payload[x] ='/0';
    //delay(2000);
  }
//  sendTrigger("Ksa", "FreePanel", "controller", "lighting", "basic", comm);

}
  
  
void simpleCmd_evalArgs(){
  arg1[0]=payload[cpt+3];
  arg1[1]=payload[cpt+4];
  arg1[2]=payload[cpt+5];
  arg2[0]=payload[cpt+6];
  arg2[1]=payload[cpt+7];
  arg2[2]=payload[cpt+8];
  arg3[0]=payload[cpt+9];
  arg3[1]=payload[cpt+10];
  arg3[2]=payload[cpt+11];
  arg4[0]=payload[cpt+12];
  arg4[1]=payload[cpt+13];
  arg4[2]=payload[cpt+14];
  arg5[0]=payload[cpt+15];
  arg5[1]=payload[cpt+16];
  arg5[2]=payload[cpt+17];
}
*/


/*
MAP of varaibles
MSG = set messageRunning
DEL = mainDelay
*/
void setVar(char* key, int value){
  Serial.println(key);
  Serial.println(value);
  if (strcmp(key, "MSG") == 0 && value == 0){
    messageRunning = false;
  } else if (strcmp(key, "MSG") == 0 && value == 1){
    messageRunning = true;
  }
  else if(strcmp(key, "DEL") == 0){
    mainDelay = value;
  }
}


void setMainColor(int R, int G, int B){
  currentColor = R*0b100000000 + G*0b10000 +B*0b1;
}

/*
void setColor(char* color){
  if(strcmp(color, "WHITE") == 0){
    currentColor = 0b101011111010;
  }
  else if(strcmp(col@Oor, "WHITE") == 0){
    mainDelay = value;
  }
}*/

String payloadGetMessage(){
  String res = "";
//  int length = 0;
  for (int i = cpt+3; i < COMMAND_LENGTH; i++){
    if(payload[i] != 40){
      res = res + payload[i];
//      Serial.print('@', HEX);
//      length += 1;
    }
    else{break;}
//    res = res + ""
  }
  /*
  char res[length];
  for (int i = 0; i < length; i++){
    res[i] = payload[i];
  }
  //Serial.println(length,DEC);
  //String res2 = atoi(res);
  res = res.substr(4);
  */
//  Serial.println(res);
//  res = res.substring(length);
//  Serial.println(res);
  return res;
}

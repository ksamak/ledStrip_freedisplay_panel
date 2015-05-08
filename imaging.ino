


unsigned short toHex(byte R, byte G, byte B){
  //if (R == 0 && G > 125){R=1;}  // Weird check that correct a bug when going 0xXXFFXX

// Checks to ensure rigthness of values. optional.
/*  if(R>255){R=255;} else if (R<0){R=0;}
  if(G>255){G=255;} else if (G<0){G=0;}
  if(B>255){B=255;} else if (B<0){B=0;}*/
  unsigned short res;
  res = 0x010000 * R + 0x0100 * G + 0x01 * B;
  return res;
  
  //Serial.println("");
}


void post_frame(){
  post_frame(0);
}

//Takes the current strip color array and pushes it out
void post_frame (int shift) {
  //Each LED requires 24 bits of data
  //MSB: R7, R6, R5..., G7, G6..., B7, B6... B0 
  //Once the 24 bits have been delivered, the IC immediately relays these bits to its neighbor
  //Pulling the clock low for 500us or more causes the IC to post the data.
  
  for(int LED_number = 0 ; LED_number < STRIP_LENGTH ; LED_number++) {
    
    /*for(int STRIP_number = 0 ; STRIP_number < STRIP_NUMBER ; STRIP_number++) {
      row[STRIP_number] = toHex(strip_rgb_colors[STRIP_number][3*LED_number], strip_rgb_colors[STRIP_number][3*LED_number+1], strip_rgb_colors[STRIP_number][3*LED_number+2]); //24 bits of color data
      
    }*/
    
    for(byte color_bit = 11 ; color_bit != 255 ; color_bit = color_bit - 1) {//11? was 23
      //Feed color bit 23 first (red data MSB)               
      //for (int color_reduction = 0; color_reduction < 2 ; color_reduction++) //since we reduced color precision, do it twice.
        //{
        short int mask = 1 << color_bit;  //The 1'L' forces the 1 to start as a 32 bit number, otherwise it defaults to 16-bit.
        for (int reduc = 0 ; reduc < 2 ; reduc++) {
        digitalWrite(CKI, LOW); //Only change data when clock is low
        
        for(int STRIP_number = 0 ; STRIP_number < STRIP_NUMBER ; STRIP_number++) {
          if( (strip_rgb_colors[STRIP_number][(LED_number + shift) % STRIP_LENGTH]) & mask) //
          {
            digitalWrite(pin_config[STRIP_number], HIGH);
          }
          else
          {
            digitalWrite(pin_config[STRIP_number], LOW);    
          }
        }
          
      digitalWrite(CKI, HIGH); //Data is latched when clock goes high
//      delayMicroseconds(100);
      }
    }
  }

  //Pull clock low to put strip into reset/post mode
  digitalWrite(CKI, LOW);
  delayMicroseconds(500); //wait to go into reset
        //long test;
        //test = strip_rgb_colors[0][0];
        //Serial.print(test , BIN);
        //Serial.println("\0");
}

void on(){
//  set_all(180,255,200);
  set_all(15, 15, 15);
  /*
  for(int LED_number = 0 ; LED_number < STRIP_LENGTH ; LED_number++) {
    for(int STRIP_number = 0 ; STRIP_number < STRIP_NUMBER ; STRIP_number++) {
      Serial.print(strip_rgb_colors[STRIP_number][3*LED_number]);
      Serial.print(strip_rgb_colors[STRIP_number][3*LED_number+1]);
      Serial.print(strip_rgb_colors[STRIP_number][3*LED_number+2]);
      Serial.print('\n');
    }
  }
  */
}

void off(){
  set_all(0,0,0);
}

//TODO: use live conversion func.
void set_all(byte R, byte G, byte B){
  for (int i = 0; i<STRIP_NUMBER; i++){
    for (int j = 0; j<STRIP_LENGTH; j++){
      strip_rgb_colors[i][j] = 0b100000000 * R + 0b10000 * G + 0b1 * B;
    }
  }
  post_frame();
}

/*
void fade(byte Step){
  set_all(strip_rgb_colors[0]-Step, strip_rgb_colors[1]-Step, strip_rgb_colors[2]-Step);
}


//TODO: CHANGE!
void fade_to(byte R, byte G, byte B){
  fade_to_time(R, G, B, 10, 1);
}
*/

/*
void fade_to_time(byte R, byte G, byte B, unsigned int Speed, unsigned int Step){
  char proportions[STRIP_LENGTH*6];
  for (int i = 0; i<STRIP_LENGTH; i++){
    proportions[3*i] = strip_rgb_colors[3*i];
    proportions[3*i+1] = strip_rgb_colors[3*i+1];
    proportions[3*i+2] = strip_rgb_colors[3*i+2];
    proportions[3*i+3] = (R - strip_rgb_colors[3*i]) / 255 * Step;
    proportions[3*i+4] = (G - strip_rgb_colors[3*i+1]) / 255 * Step;
    proportions[3*i+5] = (B - strip_rgb_colors[3*i+2]) / 255 * Step;
    //Serial.println(proportions[3*i]);
    //delay(1000);
  }
  for (int j = 0; j<255; j+=Step){
    for (int i = 0; i<STRIP_LENGTH; i++){
      strip_rgb_colors[3*i] = proportions[3*i]+proportions[3*i+3]*Step;
      strip_rgb_colors[3*i+1] = proportions[3*i+1]+proportions[3*i+4]*Step;
      strip_rgb_colors[3*i+2] = proportions[3*i+2]+proportions[3*i+5]*Step;
    }
    post_frame();
  }
}
*/

/*
void fade_out(void){ // TODO make a better, weighted fadeout.
  for (int i = 0; i<STRIP_NUMBER; i++){
    for (int j = 0; j<STRIP_LENGTH; j++){
      if (strip_rgb_colors[i][j] > 0x000000){strip_rgb_colors[i][j] = strip_rgb_colors[i][j]-1;}
    }
  }
  post_frame();
}
*/

void add_color(int R, int G, int B) {
  for (int i = 0; i<STRIP_NUMBER; i++){
    strip_rgb_colors[i][0] = 0b100000000 * R + 0b10000 * G + 0b1 * B;
    for(int x = STRIP_LENGTH ; x > 0 ; x--){
      strip_rgb_colors[i][x] = strip_rgb_colors[i][x - 1];
    }      
  }
  post_frame();
}

//TODO: make pulse better, tweak the post function!

void pulse(int Speed, int number, int Step){
  pulse_rgb(Speed, number, Step, 15, 15, 15);
}

void pulse_rgb(int Speed, int number, int Step, float R, float G, float B){ // Speed to wait between, number of pulses, Step to take each inc.
  boolean way = true;
  int j = 0;
  while (number != 0){
    if (way){j+=Step;}
    else{j-=Step;}
    if (j>=15){way = false;}
    if (j==0){way = true;number--;}
    set_all(j*R/15, j*G/15, j*B/15);
    post_frame();
    delay(Speed);
  }
}

void christmastime(){
  int x;
  for(int y = 3; y < STRIP_LENGTH/2; y++){
    for(x = 0; x<3 ; x++){
      add_color(15, 0, 0);
      delay(y*2);
    }
    for(x = 0; x<3 ; x++){
      add_color(0, 15, 0);
      delay(y*2);
    }
    for(x = 0; x<3 ; x++){
      add_color(0, 0, 15);
      delay(y*2);
    }
    for(x = 0; x<3 ; x++){
      add_color(15, 7, 0);
      delay(y*2);
    }
    for(x = 0; x<3 ; x++){
      add_color(15, 15, 15);
      delay(y*2);
    }
  }
}



/*
//Throws random colors down the strip array
void addRandom(void) {
  int x;
  
  //First, shuffle all the current colors down one spot on the strip
  for(x = (STRIP_LENGTH - 1) ; x > 0 ; x--)
    strip_colors[x] = strip_colors[x - 1];
    
  //Now form a new RGB color
  long new_color = 0;
  for(x = 0 ; x < 3 ; x++){
    new_color <<= 8;
    new_color |= random(255); //Give me a number from 0 to 0xFF
    //new_color &= 0xFFFFF0; //Force the random number to just the upper brightness levels. It sort of works.
  }
  
  strip_colors[0] = new_color; //Add the new random color to the strip
}
*/

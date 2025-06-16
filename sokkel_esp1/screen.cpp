#include "screen.h"

Adafruit_DotStarMatrix matrix = Adafruit_DotStarMatrix(
  32, 8, SPI_LN, SPI_CLK,
  DS_MATRIX_BOTTOM     + DS_MATRIX_RIGHT +
  DS_MATRIX_COLUMNS + DS_MATRIX_ZIGZAG,
  DOTSTAR_BRG);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

void Screen::setup(){
    matrix.begin();
    matrix.setTextWrap(false);
    matrix.setBrightness(40);
    matrix.setTextColor(colors[1]);
    Serial.println("Setup screen!");
}

void Screen::print(String msg){
  if(msg_buffer != msg){
    Serial.println(msg);
    x = 0;
    lastUpdate = millis();
    msg_buffer = msg;
    msg_pixel_size = msg_buffer.length() * 6; //(5+1) pixels for each letter
  }
}

void Screen::tick(){
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  matrix.print(msg_buffer);
  matrix.show();
  if (millis()-lastUpdate < readTime){

    Serial.println("READ return");
    return;
  }
  x = x - 1;
  if(x <= min(-1*(msg_pixel_size - 32), 0)){
    if (!freeze){
      freezeTime = millis();
      freeze = true;
    }
    if (millis()-freezeTime > readTime){
      nextMsg();
      freeze = false;
    }
  }

}

void Screen::nextMsg(){
  Serial.println("NEXTMSG_TRIGGER");
  Serial.println(msg_count);
  Serial.println(msg_index);
  if (msg_count == 1){
     x = 0;
    lastUpdate = millis();
  }
  else{
    msg_index = (msg_index+1) % (msg_count); 
    print(multi_msg_buffer[msg_index]);
  }
  Serial.println(msg_count);
  Serial.println(msg_index);
}

void Screen::setBuffer(String msg_arr[], uint8_t size){
  
  for (int i = 0; i < size; i++) {
        multi_msg_buffer[i] = msg_arr[i];
    }
  msg_count = size;
  msg_index = 0;
  print(multi_msg_buffer[msg_index]);
}


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
    setColor(255, 255, 255);
    Serial.println("Setup screen!");
}

void Screen::setColor(uint8_t r, uint8_t g, uint8_t b){
  matrix.setTextColor(matrix.Color(g, r, b));
}

void Screen::print(String msg){
  if(msg_buffer != msg){
    x = 0;
    lastUpdate = millis();
    msg_buffer = msg;
    msg_pixel_size = msg_buffer.length() * 6; //(5+1) pixels for each letter
    freeze = false;
  }
}

void Screen::tick(){
  if(!freeze){
    matrix.fillScreen(0);
    matrix.setCursor(x, 0);
    matrix.print(msg_buffer);
    matrix.show();
  }
  if (millis()-lastUpdate < (readTime - 1000)){
    return; // Freeze the text for a second before jumping to the next msg
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
  if (msg_count == 1){
     x = 0;
    lastUpdate = millis();
  }
  else{
    msg_index = (msg_index+1) % msg_count; 
    print(multi_msg_buffer[msg_index]);
  }
}

void Screen::setBuffer(String msg_arr[], uint8_t size){
  if(!(multi_msg_buffer[0] == msg_arr[0])){

    for (int i = 0; i < size; i++) {
      multi_msg_buffer[i] = msg_arr[i];
    }
    msg_count = size;
    msg_index = 0;
    print(multi_msg_buffer[msg_index]);
  }
}

void Screen::screenWipe(){
  for(int x = 31; x >= -2; x--){
    
    matrix.writeLine(x, 0, x, 7, matrix.Color(0, 255, 0));
    matrix.writeLine(x+1, 0, x+1, 7, matrix.Color(0, 128, 0));
    matrix.writeLine(x+2, 0, x+2, 7, matrix.Color(0, 0, 0));
    matrix.show();
    delay(10);
  }
}

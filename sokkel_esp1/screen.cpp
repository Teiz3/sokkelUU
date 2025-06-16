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
    // x = matrix.width();
    x = 0;
  }
  msg_buffer = msg;
}

void Screen::tick(){
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  x--;
  int str_len = msg_buffer.length() * 6;
  if (x<(-str_len)){
    x = matrix.width();
  }
  matrix.print(msg_buffer);
  matrix.show();
}


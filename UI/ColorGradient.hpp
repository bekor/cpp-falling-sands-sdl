//
// Created by Joe Bekor on 13/03/2024.
//

#pragma once

struct ColorGradient {
  ColorGradient(){
    red = 121;
    green = 9;
    blue = 9;
  }
int red;
int green;
int blue;
void shift(){
  if(green == 121 && blue == 9 && red > 9)
    red-=2;
  else if (red == 121 && blue == 9 && green < 121)
    green+=2;
  else if (red == 9 && green == 121 && blue < 121)
    blue+=2;
  else if (red == 9 && blue == 121 && green > 9)
    green-=2;
}
};

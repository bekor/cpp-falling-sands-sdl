//
// Created by Joe Bekor on 2024. 01. 30..
//

#pragma once
#include <SDL.h>
class UIElement {
 public:
  UIElement(SDL_Rect rect);
 private:
  SDL_Rect rect_;
};

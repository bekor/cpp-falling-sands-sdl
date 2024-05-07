//
// Created by Joe Bekor on 2024. 01. 30..
//

#include "UIElement.h"
UIElement::UIElement(Coordinate coordinate, SDL_Rect rect) : coords(coordinate), rect_(rect){
}
bool UIElement::pointInElement(SDL_Point point) {
  return SDL_PointInRect(&point, &rect_) == SDL_TRUE;
}
Coordinate UIElement::getCoordinate() const{
  return coords;
}
const SDL_Rect *UIElement::get() {
  return &rect_;
}


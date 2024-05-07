//
// Created by Joe Bekor on 2024. 01. 30..
//

#pragma once
#include <SDL.h>
#include <utility>
#include "../util/Coordinate.h"
class UIElement {
 public:
  explicit UIElement(Coordinate coordinate, SDL_Rect rect);
  bool pointInElement(SDL_Point point);
  [[nodiscard]] Coordinate getCoordinate() const;
  bool marked();
  const SDL_Rect *get();
 private:
  const Coordinate coords;
  SDL_Rect rect_;
};

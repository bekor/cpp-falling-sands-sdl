//
// Created by Joe Bekor on 13/03/2024.
//
#pragma once
#include "UI/UIRenderer.h"
#include <SDL2/SDL.h>
class Application {
  bool handleEvents(UIRenderer& renderer);
  void update(UIRenderer& renderer, std::shared_ptr<Matrix> matrix);
 public:
  void run();
};

//
// Created by Joe Bekor on 2024. 01. 30..
//

#pragma once
#include <memory>
#include <SDL.h>
#include "../logic/Matrix.h"

struct sdl_deleter {
  void operator()(SDL_Window* p) const { SDL_DestroyWindow(p); }
  void operator()(SDL_Renderer* p) const { SDL_DestroyRenderer(p); }
  void operator()(SDL_Texture* p) const { SDL_DestroyTexture(p); }
};

class UIRenderer {
 public:
  UIRenderer(int width, int height, std::shared_ptr<Matrix> matrix);
  void render();

  void handleClick(const SDL_MouseButtonEvent &event);
 private:
  std::unique_ptr<SDL_Window, sdl_deleter> window_;
  std::unique_ptr<SDL_Renderer, sdl_deleter> renderer_;
  std::unique_ptr<SDL_Texture, sdl_deleter> texture_;
  std::vector<SDL_Rect> rects;
  const std::shared_ptr<Matrix> matrix;
  void initWindow(int width, int height);
  void initRenderer();
  void initTexture();
  void generateRects();
};

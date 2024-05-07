//
// Created by Joe Bekor on 2024. 01. 30..
//
#include <iostream>
#include <map>
#include "UIRenderer.h"
#include "UIElement.h"
#include "ColorGradient.hpp"

UIRenderer::UIRenderer(int width, int height, const std::shared_ptr<Matrix> matrix) : matrix(matrix) {
  initWindow(width, height);
  initRenderer();
  initTexture();
  generateRects();
}

void UIRenderer::initWindow(int width, int height) {
  std::unique_ptr<SDL_Window, sdl_deleter> win(SDL_CreateWindow("FallingSands",
                                                                     SDL_WINDOWPOS_CENTERED,
                                                                     SDL_WINDOWPOS_CENTERED,
                                                                     width,
                                                                     height,
                                                                     SDL_WINDOW_SHOWN | SDL_WINDOW_METAL));
  if (!win) {
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    throw std::exception();
  }
  win.swap(window_);
}
void UIRenderer::initRenderer() {
  std::unique_ptr<SDL_Renderer, sdl_deleter> ren(SDL_CreateRenderer(window_.get(), -1,
                                                                    SDL_RENDERER_ACCELERATED
                                                                        | SDL_RENDERER_PRESENTVSYNC));
  if (!ren) {
    std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    throw std::exception();
  }
  ren.swap(renderer_);
}
void UIRenderer::initTexture() {
  std::unique_ptr<SDL_Texture, sdl_deleter> text(SDL_CreateTexture(renderer_.get(),
                                                                   SDL_PIXELFORMAT_RGBA8888,
                                                                   SDL_TEXTUREACCESS_TARGET,
                                                                   10,
                                                                   10));
  if (!text) {
    std::cout << "SDL_CreateTexture Error: " << SDL_GetError() << std::endl;
    throw std::exception();
  }
  text.swap(texture_);
}

void UIRenderer::render() {
  //First clear the renderer
  SDL_RenderClear(renderer_.get());
  SDL_CreateTexture(renderer_.get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 0,0 );
  int width, height;
  SDL_GetWindowSize(window_.get(), &width, &height);
  SDL_SetRenderDrawColor(renderer_.get(), 255, 255, 255, 255);
  renderMatrix();
  SDL_SetRenderDrawColor(renderer_.get(), 0, 0, 0, 255);
  //Update the screen
  SDL_RenderPresent(renderer_.get());
}


void UIRenderer::generateRects() {
  int renderWidth = 0;
  int renderHeight = 0;
  SDL_GetRendererOutputSize(renderer_.get(), &renderWidth, &renderHeight);
  int rectWidth = (renderWidth) / matrix->getSize();
  int rectHeight = (renderHeight) / matrix->getSize();
  auto data = matrix->getRepresentation();
  int fromX = 0;
  int fromY = 0;

  for (int row = 0; row < data.size(); ++row) {
    for (int column = 0; column < data.at(row).size(); ++column) {
      UIElement current{{row, column}, {fromX, fromY, rectWidth, rectHeight}};
      rects.push_back(current);
      fromX += rectWidth;
    }
    fromY += rectHeight;
    fromX = 0;
  }
}
void UIRenderer::handleClick(const SDL_MouseButtonEvent &event) {
  SDL_Point point{event.x, event.y};
  for (auto &element : rects) {
    if (element.pointInElement(point)) {
      matrix->mark(element.getCoordinate());
    }
  }
}
void UIRenderer::renderMatrix() {
  auto matrixSize = matrix->getSize();
  std::map<TimeStamp, std::pair<int,int>> markedPoints;

  for (int row = 0; row < matrixSize; ++row) {
    for (int column = 0; column < matrixSize; ++column) {
      int position = matrixSize * row + column;
      auto rect = rects.at(position);
      if (matrix->marked({row, column})){
        markedPoints[matrix->getTimeStamp({row, column})] = std::make_pair(row, column);
      }
      SDL_RenderDrawRect(renderer_.get(), rect.get());
    }
  }
  ColorGradient gradient;
  for(const auto & points: markedPoints){
    auto [row, column] = points.second;
    int position = matrixSize * row + column;
    auto rect = rects.at(position);
    gradient.shift();
    const auto [r,g,b] = gradient;
    SDL_SetRenderDrawColor(renderer_.get(), r, g, b, 255);
    SDL_RenderFillRect(renderer_.get(), rect.get());
    SDL_SetRenderDrawColor(renderer_.get(), 255, 255, 255, 255);
  }
}

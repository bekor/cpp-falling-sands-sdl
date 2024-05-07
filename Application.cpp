//
// Created by Joe Bekor on 13/03/2024.
//

#include "Application.h"

bool Application::handleEvents(UIRenderer &renderer) {
  bool quit = false;
  //Event handler
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0) // poll for events received from user or operating system
  {
    //User requests quit
    if (e.type == SDL_QUIT)
    {
      quit = true;
    }
    if (e.key.type == SDL_KEYDOWN){
      if (e.key.keysym.sym == SDLK_q){
        quit = true;
      }
    }
    if (e.button.type == SDL_MOUSEBUTTONDOWN){
      renderer.handleClick(e.button);
    }
  }
  return quit;
}

void Application::update(UIRenderer& renderer, std::shared_ptr<Matrix> matrix){
  renderer.render();
  matrix->update();
}

void Application::run() {
  auto sys = SDL_Init(SDL_INIT_EVERYTHING);
  // wait a little so the animation won't start before the window appears
  SDL_Delay(100);

  bool quit = false;
  Uint32 timePassed = 0;
  Uint32 timestamp = 16; // we want 60fps what is 1000 ms / 60 = 16.6 frame per seconds so timestamp is 16
  std::shared_ptr<Matrix> matrix = std::make_shared<Matrix>(20);
  UIRenderer renderer{500, 500, matrix};
  // main loop, drawing happens here
  while (!quit) {
    timePassed = SDL_GetTicks();
    quit = handleEvents(renderer);
    update(renderer, matrix);
    // wait until the time declared in timestamp passes
    while (timePassed + timestamp > SDL_GetTicks()) {
      SDL_Delay(0);
    }
  }

  SDL_Quit();
}

#include <iostream>
#include "UI/UIRenderer.h"
#include <SDL2/SDL.h>

bool handleEvents(UIRenderer& renderer)
{
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
        std::cout << "Quit";
        quit = true;
      }
    }
    if (e.button.type == SDL_MOUSEBUTTONDOWN){
      renderer.handleClick(e.button);
    }
  }
  return quit;
}

void update(UIRenderer& renderer){
  renderer.render();
}




int main() {
  auto sys = SDL_Init(SDL_INIT_EVERYTHING);

  // wait a little so the animation won't start before the window appears
  SDL_Delay(100);

  bool quit = false;
  Uint32 timePassed = 0;
  Uint32 timestep = 16; // we want 60fps what is 1000 ms / 60 = 16.6 frame per seconds so timestep is 16
  std::shared_ptr<Matrix> matrix = std::make_shared<Matrix>(10);
  UIRenderer renderer{500, 500, matrix};
  // main loop, drawing happens here
  while (!quit) {
    timePassed = SDL_GetTicks();
    quit = handleEvents(renderer);
    update(renderer);
    // wait until the time declared in timestep passes
    while (timePassed + timestep > SDL_GetTicks()) {
      SDL_Delay(0);
    }
  }

  SDL_Quit();


  return 0;
}

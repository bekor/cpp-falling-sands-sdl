#include <exception>
#include "Application.h"
#include <iostream>
int main() {
  Application application;
  try {
    application.run();
  }
  catch (const std::exception &e) {
    std::cout << "An error happened: " << e.what() << std::endl;
  }
  return 0;
}

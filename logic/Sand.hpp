//
// Created by Joe Bekor on 07/03/2024.
//

#pragma once
#include <chrono>
#include "../util/Coordinate.h"

using TimeStamp = std::chrono::time_point<std::chrono::system_clock>;
class Sand {
  bool occupied = false;
  TimeStamp timeStamp;
 public:
  void mark(){
    occupied = true;
    timeStamp = std::chrono::system_clock::now();
  }

  [[nodiscard]] TimeStamp getTimeStamp() const{
    return timeStamp;
  }

  [[nodiscard]] bool isOccupied() const{
    return occupied;
  };

  void swap(Sand &sand) {
    auto tmpTime = this->timeStamp;
    this->timeStamp = sand.timeStamp;
    sand.timeStamp = tmpTime;

    auto tmpOcc = this->occupied;
    this->occupied = sand.occupied;
    sand.occupied = tmpOcc;
  }
};

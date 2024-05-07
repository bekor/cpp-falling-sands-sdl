//
// Created by Joe Bekor on 08/03/2024.
//

#pragma once
#include <random>

namespace Random {
std::random_device dev;
typedef std::mt19937 Mt_Rng;

static Mt_Rng rng(dev());

int between(int from, int to){
  std::uniform_int_distribution<std::mt19937::result_type> uint_dist(from, to);
  return (int)uint_dist(rng);
}

};

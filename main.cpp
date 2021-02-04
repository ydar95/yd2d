#include "yd2d/yd2d_game_engine.hpp"

int main() {
  yd2d::GameEngine engine;
  engine.init({ 10,10 }, { 64,64 }, true);
  return engine.start();
}
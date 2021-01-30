#include "yd2d/yd2d_game_engine.hpp"


int main() {
  yd2d::GameEngine engine;
  engine.init({ 16,9 }, { 80,80 }, true);
  return engine.start();
}

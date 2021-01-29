#include "yd2d/yd2d_game_engine.hpp"

int main() {
  //auto win = yd2d::PlatformWindows();
  //win.createWindow(yd2d::Vec2d(100,100),yd2d::Size(1280,720));
  //win.setWindowTitle("6666");

  //auto renderer = yd2d::RendererOGL10Windows();
  //renderer.createDevice({win.handle()},true);
  //renderer.prepareDevice();
  //renderer.updateViewport({0,0},win.size());
  //renderer.updateOrtho2d(0,1,0,1);

  //renderer.prepareDevice();
  //renderer.clearFrame({255,0,0},true);

  //glColor3ubv(yd2d::GREEN.data());
  //glRectf(0.2,0.2,0.8,0.8);


  //renderer.displayFrame();
  //win.handleWindowEvent();

  yd2d::GameEngine engine;
  engine.init({ 10,10 }, { 100,100 }, false);
  return engine.start();
}

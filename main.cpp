#include <yd2d/yd2d_typedef.hpp>
#include <yd2d/platforms/platform_windows.hpp>
int main() {
  auto win = yd2d::PlatformWindows();
  win.createWindow(yd2d::Vec2d(100,100),yd2d::Size(1280,720));
  win.setWindowTitle("6666");
  win.handleWindowEvent();
  return 0;
}

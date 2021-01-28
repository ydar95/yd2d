//
// Created by ydar on 2021/1/28.
//

#ifndef YD2D_YD2D_PLATFORMS_PLATFORM_WINDOWS_HPP_
#define YD2D_YD2D_PLATFORMS_PLATFORM_WINDOWS_HPP_
#if defined(_WIN32)

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "Shlwapi.lib")
#include <windows.h>
#include <gdiplus.h>
#include <Shlwapi.h>

#include <string>

#include "base_platform.hpp"
namespace yd2d {

// utf8->gbk
inline std::wstring ConvertS2W(std::string s)
{
  int count = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, NULL, 0);
  std::wstring buffer;
  buffer.resize(count);
  MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, buffer.data(), count);
  return buffer;
}

// at construction, by initialising the GDI subsystem
static class GDIPlusStartup
{
 public:
  GDIPlusStartup()
  {
    Gdiplus::GdiplusStartupInput startupInput;
    ULONG_PTR	token;
    Gdiplus::GdiplusStartup(&token, &startupInput, NULL);
  };
} gdistartup;


class PlatformWindows
    : public yd2d::Platform
{
 public:
  [[nodiscard]] HWND hwnd() const;
  virtual yd2d::rcode createWindow(yd2d::Vec2d win_pos, yd2d::Size win_size) override;
  virtual yd2d::rcode quitWindow() override;
  virtual yd2d::rcode setWindowTitle(const std::string& title) override;
  virtual yd2d::rcode handleWindowEvent() override;
  virtual yd2d::Size size() override;
};

}//namespace yd2d




#endif //defined(_WIN32)
#endif //YD2D_YD2D_PLATFORMS_PLATFORM_WINDOWS_HPP_

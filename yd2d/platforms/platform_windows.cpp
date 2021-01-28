//
// Created by ydar on 2021/1/28.
//

#include "platform_windows.hpp"

#include <functional>
#include <algorithm>


//define
static LRESULT CALLBACK yd2d_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

[[maybe_unused]] HWND yd2d::PlatformWindows::hwnd() const {
  return std::any_cast<HWND>(this->m_handle);
}

yd2d::rcode yd2d::PlatformWindows::createWindow(yd2d::Vec2d win_pos, yd2d::Size win_size) {
  WNDCLASS wc;
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.hInstance = GetModuleHandle(nullptr);
  wc.lpfnWndProc = yd2d_WindowProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = sizeof(yd2d::PlatformWindows*);
  wc.lpszMenuName = nullptr;
  wc.hbrBackground = nullptr;
  wc.lpszClassName = "yd2d";
  RegisterClass(&wc);

  // Define window furniture
  DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
  DWORD dwStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_THICKFRAME;

  RECT rWndRect = { 0, 0, win_size.width(), win_size.height() };
  AdjustWindowRectEx(&rWndRect, dwStyle, FALSE, dwExStyle);
  int width = rWndRect.right - rWndRect.left;
  int height = rWndRect.bottom - rWndRect.top;

#ifdef UNICODE
  this->m_handle = CreateWindowEx(dwExStyle,
                                  L"yd2d",L"",
                                  dwStyle,
                                  win_pos.x(), win_pos.y(),
                                  width, height,
                                  nullptr, nullptr, GetModuleHandle(nullptr), this);
#else
  this->m_handle = CreateWindowEx(dwExStyle,
                                  "yd2d","",
                                  dwStyle,
                                  win_pos.x(), win_pos.y(),
                                  width, height,
                                  nullptr, nullptr, GetModuleHandle(nullptr), this);
#endif

  SetWindowLongPtrW(hwnd(), 0, reinterpret_cast<LONG_PTR>(this)); // CreateWindowEx 才创建 hwnd

  return yd2d::rcode::OK;
}
yd2d::rcode yd2d::PlatformWindows::quitWindow() {
  PostMessage(hwnd(), WM_DESTROY, 0, 0);
  return yd2d::rcode::OK;
}
yd2d::rcode yd2d::PlatformWindows::setWindowTitle(const std::string &title) {
#ifdef UNICODE
  SetWindowText(hwnd(), ConvertS2W(title).c_str());
#else
  SetWindowText(hwnd(), title.c_str());
#endif
  return yd2d::rcode::OK;
}
yd2d::rcode yd2d::PlatformWindows::handleWindowEvent() {
  MSG msg;
  while (GetMessage(&msg, nullptr, 0, 0) > 0)
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return yd2d::rcode::OK;
}
yd2d::Size yd2d::PlatformWindows::size() {
  RECT rect;
  GetClientRect(hwnd(), &rect);
  return yd2d::Size(rect.right- rect.left, rect.bottom-rect.top);
}


LRESULT CALLBACK yd2d_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  auto platform = reinterpret_cast<yd2d::PlatformWindows*>(GetWindowLongPtrW(hwnd, 0));

  if (platform != nullptr) {
    switch (uMsg)
    {
      case WM_MOUSEMOVE:
      {
        // Thanks @ForAbby (Discord)
        if (platform->getFnUpdateMouse() != nullptr) {
          uint16_t x = lParam & 0xFFFF; uint16_t y = (lParam >> 16) & 0xFFFF;
          int16_t ix = *(int16_t*)&x;   int16_t iy = *(int16_t*)&y;
          platform->getFnUpdateMouse()(ix, iy);
          return 0;
        }
        break;
      }
      case WM_SIZE:
      {
        if (platform->getFnUpdateWindowSize() != nullptr) {
          platform->getFnUpdateWindowSize()(lParam & 0xFFFF, (lParam >> 16) & 0xFFFF);
          return 0;
        }
        break;
      }
      case WM_MOUSEWHEEL:
      {
        if (platform->getFnUpdateMouseWheel() != nullptr) {
          platform->getFnUpdateMouseWheel()(GET_WHEEL_DELTA_WPARAM(wParam));
          return 0;
        }
        break;
      }
        //case WM_MOUSELEAVE: {} ptrPGE->olc_UpdateMouseFocus(false);                                    return 0;
        //case WM_SETFOCUS:	ptrPGE->olc_UpdateKeyFocus(true);                                       return 0;
        //case WM_KILLFOCUS:	ptrPGE->olc_UpdateKeyFocus(false);                                      return 0;
      case WM_KEYDOWN:
      {
        if (platform->getFnUpdateKeyState() != nullptr) {
          platform->getFnUpdateKeyState()(wParam, true);
          return 0;
        }
        break;
      }
      case WM_KEYUP:
      {
        if (platform->getFnUpdateKeyState() != nullptr) {
          platform->getFnUpdateKeyState()(wParam, false);
          return 0;
        }
        break;
      }
      case WM_LBUTTONDOWN:
      {
        if (platform->getFnUpdateMouseState() != nullptr) {
          platform->getFnUpdateMouseState()(0, true);
          return 0;
        }
        break;
      }
      case WM_LBUTTONUP:
      {
        if (platform->getFnUpdateMouseState() != nullptr) {
          platform->getFnUpdateMouseState()(0, false);
          return 0;
        }
        break;
      }
      case WM_RBUTTONDOWN:
      {
        if (platform->getFnUpdateMouseState() != nullptr) {
          platform->getFnUpdateMouseState()(1, true);
          return 0;
        }
        break;
      }
      case WM_RBUTTONUP:
      {
        if (platform->getFnUpdateMouseState() != nullptr) {
          platform->getFnUpdateMouseState()(1, false);
          return 0;
        }
        break;
      }
      case WM_MBUTTONDOWN:
      {
        if (platform->getFnUpdateMouseState() != nullptr) {
          platform->getFnUpdateMouseState()(2, true);
          return 0;
        }
        break;
      }
      case WM_MBUTTONUP:
      {
        if (platform->getFnUpdateMouseState() != nullptr) {
          platform->getFnUpdateMouseState()(2, false);
          return 0;
        }
        break;
      }
      case WM_CLOSE:
      {
        if (platform->getFnTerminate() != nullptr) {
          platform->getFnTerminate()();
          return 0;
        }
        break;
      }
      case WM_DESTROY:
      {
        PostQuitMessage(0);
        return 0;
      }

    }// switch end
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
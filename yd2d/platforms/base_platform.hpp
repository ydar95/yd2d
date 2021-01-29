//
// Created by ydar on 2021/1/26.
//

#ifndef YD2D_INCLUDE_YD2D_PLATFORMS_BASE_PLATFORM_HPP_
#define YD2D_INCLUDE_YD2D_PLATFORMS_BASE_PLATFORM_HPP_

#include "../base/rcode.hpp"
#include "../math/vector2d.hpp"
#include "../math/size.hpp"

#include <any>
#include <cstdint>
#include <functional>
namespace yd2d {
class Platform
{
 public: // virtual function
  virtual yd2d::rcode createWindow(yd2d::Vec2d win_pos, yd2d::Size win_size) = 0;
  virtual yd2d::rcode quitWindow()=0;
  virtual yd2d::rcode setWindowTitle(const std::string& title) = 0;
  virtual yd2d::rcode handleWindowEvent()=0;
  virtual yd2d::Size size() = 0;
 public:
  [[nodiscard]] inline const std::any& handle() const noexcept { return m_handle; };

 protected:
  std::function<void(int32_t, int32_t)> m_update_mouse_fn=nullptr;
  std::function<void(int32_t)> m_update_mouse_wheel_fn = nullptr;
  std::function<void(int32_t, int32_t)> m_update_window_size = nullptr;
  std::function<void(int32_t, bool)> m_update_mouse_state_fn = nullptr;
  std::function<void(void)> m_terminate_fn = nullptr;
  std::function<void(int32_t, bool)> m_update_key_state_fn = nullptr;


 public:
  inline std::function<void(int32_t, int32_t)> getFnUpdateMouse() { return m_update_mouse_fn; }
  inline std::function<void(int32_t)> getFnUpdateMouseWheel() { return m_update_mouse_wheel_fn; }
  inline std::function<void(int32_t, int32_t)> getFnUpdateWindowSize() { return m_update_window_size; }
  inline std::function<void(int32_t, bool)> getFnUpdateMouseState() { return m_update_mouse_state_fn; }
  inline std::function<void(void)> getFnTerminate() { return m_terminate_fn; }
  inline std::function<void(int32_t, bool)> getFnUpdateKeyState() { return m_update_key_state_fn; }

  inline void setFnUpdateMouse(std::function<void(int32_t, int32_t)> update_mouse_fn) { m_update_mouse_fn = update_mouse_fn; }
  inline void setFnUpdateMouseWheel(std::function<void(int32_t)> update_mouse_wheel_fn) { m_update_mouse_wheel_fn = update_mouse_wheel_fn; }
  inline void setFnUpdateWindowSize(std::function<void(int32_t, int32_t)> update_window_size) { m_update_window_size = update_window_size; }
  inline void setFnUpdateMouseState(std::function<void(int32_t, bool)> update_mouse_state_fn) { m_update_mouse_state_fn = update_mouse_state_fn; }
  inline void setFnTerminate(std::function<void(void)> terminate_fn) { m_terminate_fn = terminate_fn; }
  inline void setFnUpdateKeyState(std::function<void(int32_t, bool)> update_key_state_fn) { m_update_key_state_fn = update_key_state_fn; }

 protected:
  std::any m_handle{};
};

}



#endif //YD2D_INCLUDE_YD2D_PLATFORMS_BASE_PLATFORM_HPP_

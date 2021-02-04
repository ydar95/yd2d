//
// Created by ydar on 2021/1/29.
//
#pragma once
#ifndef YD2D_YD2D_YD2D_GAME_ENGINE_HPP_
#define YD2D_YD2D_YD2D_GAME_ENGINE_HPP_

#include "yd2d_typedef.hpp"

#include "platforms/base_platform.hpp"
#include "renderers/base_renderder.hpp"
#include "texture/texture2d.hpp"
#include "tools/game_time.hpp"

#include <mutex>
#include <atomic>
#include <array>
#include <cstdint>
#include <map>
#include <memory>
namespace yd2d {

class GameEngine{
 public:
  explicit GameEngine();
  yd2d::rcode init(const yd2d::Size& grid_num,const yd2d::Size& grid_size ,bool vsync);
  yd2d::rcode start();
  yd2d::Platform* platform();
  yd2d::Renderer* renderer();
  yd2d::rcode terminate();
  yd2d::HWButton getKey(yd2d::Key key) const noexcept;
  yd2d::HWButton getMouse(yd2d::Mouse mouse) const noexcept;
  yd2d::HWButton getLeftMouse() const noexcept;
  yd2d::HWButton getMiddleMouse() const noexcept;
  yd2d::HWButton getRightMouse() const noexcept;
 protected:
  //virtual bool onInit();
  virtual bool onUpdateOneFrame(double delte_time);
  virtual bool onRenderThreadStarted();
  //virtual bool onDestroy();
 protected:
  //根据windows form 事件进行更新属性和状态
  void onSlotUpdateMouse(int32_t x, int32_t y);
  void onSlotUpdateMouseWheel(int32_t delta);
  void onSlotUpdateWindowSize(int32_t width, int32_t height);
  void onSlotUpdateMouseState(int32_t button, bool state);
  void onSlotTerminate();
  void onSlotUpdateKeyState(int32_t key, bool state);
  //void onSlotUpdateMouseFocus(bool state);
  //void onSlotUpdateKeyFocus(bool state);
 protected:
  // 在renderer中更新 m_keyboard_state, m_mouse_state
  void updateHWButtonInRendererThread();

 private:
  void coreRenderThread();

 private:
  yd2d::Platform *mp_platform=nullptr;
  yd2d::Renderer *mp_renderer=nullptr;
 private:
  yd2d::Size m_grid_num;
  yd2d::Size m_grid_size;
  yd2d::Size m_win_size;
  bool m_vsync;
  std::map<std::string,std::shared_ptr<yd2d::Texture2d>> m_texture2d_map;
  std::map<std::string,yd2d::Texture2dFrame> m_texture2d_frame_map;
 private:
  yd2d::Vec2d m_mouse_platform_pos; // 左下角为 原点 的 鼠标坐标系, 单位是 像素
  yd2d::VecF2d m_mouse_viewport_pos; // 左下角为 原点 的 renderer 的 可视范围坐标系(Ortho2d.left_bottom), 单位是 renderer 单位
  yd2d::VecF2d m_mouse_renderer_pos; // 基于 renderer的坐标系 , == Ortho2d.left_bottom + m_mouse_viewport_pos
  int32_t m_mouse_wheel_delta;

  std::array<yd2d::HWButton, yd2d::KeyBoardNumbers> m_keyboard_state;
  std::array<yd2d::HWButton, yd2d::MouseNumbers> m_mouse_state;

  yd2d::GameTime m_game_time;
 private:
  //用于在 Frame 之间更新 鼠标按键的信息， m_keyboard_state 和 m_mouse_state 的更新依靠下面变量来更新
  std::array<yd2d::HWBtnState, yd2d::KeyBoardNumbers> m_new_keyboard_state;
  std::array<yd2d::HWBtnState, yd2d::KeyBoardNumbers> m_old_keyboard_state;

  std::array<yd2d::HWBtnState, yd2d::MouseNumbers> m_new_mouse_state;
  std::array<yd2d::HWBtnState, yd2d::MouseNumbers> m_old_mouse_state;
 private:
  std::atomic_bool m_platform_resized = false; //设备是否修改尺寸
  std::atomic_bool m_atomic_status = false;
  std::mutex m_mutex_render_thread;
  std::array<yd2d::Key, 256> m_vk2key;
};

}
#endif //YD2D_YD2D_YD2D_GAME_ENGINE_HPP_

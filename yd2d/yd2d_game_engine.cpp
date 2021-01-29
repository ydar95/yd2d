//
// Created by ydar on 2021/1/29.
//

#include "yd2d_game_engine.hpp"

#include <thread>
#include <functional>
#include "platforms/platform_windows.hpp"
#include "renderers/renderer_gl10_windows.hpp"
#include <gl/gl.h>

using namespace yd2d;
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

yd2d::GameEngine::GameEngine()
{
  m_new_keyboard_state.fill(yd2d::HWBtnState::Released);
  m_old_keyboard_state.fill(yd2d::HWBtnState::Released);
  m_new_mouse_state.fill(yd2d::HWBtnState::Released);
  m_old_mouse_state.fill(yd2d::HWBtnState::Released);
  {// Create Keyboard Mapping
    m_vk2key[0x00] = Key::NONE;
    m_vk2key[0x41] = Key::A; m_vk2key[0x42] = Key::B; m_vk2key[0x43] = Key::C; m_vk2key[0x44] = Key::D; m_vk2key[0x45] = Key::E;
    m_vk2key[0x46] = Key::F; m_vk2key[0x47] = Key::G; m_vk2key[0x48] = Key::H; m_vk2key[0x49] = Key::I; m_vk2key[0x4A] = Key::J;
    m_vk2key[0x4B] = Key::K; m_vk2key[0x4C] = Key::L; m_vk2key[0x4D] = Key::M; m_vk2key[0x4E] = Key::N; m_vk2key[0x4F] = Key::O;
    m_vk2key[0x50] = Key::P; m_vk2key[0x51] = Key::Q; m_vk2key[0x52] = Key::R; m_vk2key[0x53] = Key::S; m_vk2key[0x54] = Key::T;
    m_vk2key[0x55] = Key::U; m_vk2key[0x56] = Key::V; m_vk2key[0x57] = Key::W; m_vk2key[0x58] = Key::X; m_vk2key[0x59] = Key::Y;
    m_vk2key[0x5A] = Key::Z;

    m_vk2key[VK_F1] = Key::F1; m_vk2key[VK_F2] = Key::F2; m_vk2key[VK_F3] = Key::F3; m_vk2key[VK_F4] = Key::F4;
    m_vk2key[VK_F5] = Key::F5; m_vk2key[VK_F6] = Key::F6; m_vk2key[VK_F7] = Key::F7; m_vk2key[VK_F8] = Key::F8;
    m_vk2key[VK_F9] = Key::F9; m_vk2key[VK_F10] = Key::F10; m_vk2key[VK_F11] = Key::F11; m_vk2key[VK_F12] = Key::F12;

    m_vk2key[VK_DOWN] = Key::DOWN; m_vk2key[VK_LEFT] = Key::LEFT; m_vk2key[VK_RIGHT] = Key::RIGHT; m_vk2key[VK_UP] = Key::UP;
    m_vk2key[VK_RETURN] = Key::ENTER; //m_vk2key[VK_RETURN] = Key::RETURN;

    m_vk2key[VK_BACK] = Key::BACK; m_vk2key[VK_ESCAPE] = Key::ESCAPE; m_vk2key[VK_RETURN] = Key::ENTER; m_vk2key[VK_PAUSE] = Key::PAUSE;
    m_vk2key[VK_SCROLL] = Key::SCROLL; m_vk2key[VK_TAB] = Key::TAB; m_vk2key[VK_DELETE] = Key::DEL; m_vk2key[VK_HOME] = Key::HOME;
    m_vk2key[VK_END] = Key::END; m_vk2key[VK_PRIOR] = Key::PGUP; m_vk2key[VK_NEXT] = Key::PGDN; m_vk2key[VK_INSERT] = Key::INS;
    m_vk2key[VK_SHIFT] = Key::SHIFT; m_vk2key[VK_CONTROL] = Key::CTRL;
    m_vk2key[VK_SPACE] = Key::SPACE;

    m_vk2key[0x30] = Key::K0; m_vk2key[0x31] = Key::K1; m_vk2key[0x32] = Key::K2; m_vk2key[0x33] = Key::K3; m_vk2key[0x34] = Key::K4;
    m_vk2key[0x35] = Key::K5; m_vk2key[0x36] = Key::K6; m_vk2key[0x37] = Key::K7; m_vk2key[0x38] = Key::K8; m_vk2key[0x39] = Key::K9;

    m_vk2key[VK_NUMPAD0] = Key::NP0; m_vk2key[VK_NUMPAD1] = Key::NP1; m_vk2key[VK_NUMPAD2] = Key::NP2; m_vk2key[VK_NUMPAD3] = Key::NP3; m_vk2key[VK_NUMPAD4] = Key::NP4;
    m_vk2key[VK_NUMPAD5] = Key::NP5; m_vk2key[VK_NUMPAD6] = Key::NP6; m_vk2key[VK_NUMPAD7] = Key::NP7; m_vk2key[VK_NUMPAD8] = Key::NP8; m_vk2key[VK_NUMPAD9] = Key::NP9;
    m_vk2key[VK_MULTIPLY] = Key::NP_MUL; m_vk2key[VK_ADD] = Key::NP_ADD; m_vk2key[VK_DIVIDE] = Key::NP_DIV; m_vk2key[VK_SUBTRACT] = Key::NP_SUB; m_vk2key[VK_DECIMAL] = Key::NP_DECIMAL;
  }
}

yd2d::rcode yd2d::GameEngine::init(const yd2d::Size &grid_num, const yd2d::Size &grid_size,bool vsync)
{
  this->m_vsync = vsync;
  this->m_grid_num = grid_num;
  this->m_grid_size = grid_size;
  this->m_win_size = Size(grid_num.width()*grid_size.width(),grid_num.height()*grid_size.height());

  this->mp_platform = new yd2d::PlatformWindows();

  this->mp_platform->setFnUpdateMouse(std::bind(&yd2d::GameEngine::onSlotUpdateMouse,this, _1, _2));
  this->mp_platform->setFnUpdateMouseState(std::bind(&yd2d::GameEngine::onSlotUpdateMouseState, this, _1, _2));
  this->mp_platform->setFnUpdateMouseWheel(std::bind(&yd2d::GameEngine::onSlotUpdateMouseWheel, this, _1));
  this->mp_platform->setFnUpdateWindowSize(std::bind(&yd2d::GameEngine::onSlotUpdateWindowSize, this, _1, _2));
  this->mp_platform->setFnTerminate(std::bind(&yd2d::GameEngine::onSlotTerminate, this));
  this->mp_platform->setFnUpdateKeyState(std::bind(&yd2d::GameEngine::onSlotUpdateKeyState, this, _1, _2));

  return this->mp_platform->createWindow({ 0,0 }, m_win_size);;
}

yd2d::rcode yd2d::GameEngine::start()
{
  m_atomic_status = true;
  std::thread th = std::thread(&yd2d::GameEngine::coreRenderThread,this);
  th.detach();

  this->mp_platform->handleWindowEvent();
  return yd2d::rcode::OK;
}

yd2d::Platform *yd2d::GameEngine::platform()
{
  return this->mp_platform;
}

yd2d::Renderer *yd2d::GameEngine::renderer()
{
  return this->mp_renderer;
}

yd2d::rcode yd2d::GameEngine::terminate()
{
  m_atomic_status = false;
  { //等待 获得 lock， 然后释放
    std::unique_lock lock(this->m_mutex_render_thread);
  }
  this->mp_platform->quitWindow();
  return yd2d::rcode::OK;
}

void yd2d::GameEngine::onSlotUpdateMouse(int32_t x, int32_t y)
{
  //printf("%s,%d,%d\n", __func__, x, y);

  /*
   * windows mouse pos
   * o---------x (w-1)
   * |
   * |
   * |
   * y (h-1)
   *
   * 需要变换到
   *
   * y (unit_num_height)
   * |
   * |
   * |
   * o--------x (unit_num_width)
   */

  // [1] 单位化[0,1]
  float _x = x / static_cast<float>(this->m_win_size.width());
  float _y = y / static_cast<float>(this->m_win_size.height());

  // [2] 对 _y 轴 ，反转 + 平移
  _y = 1 - _y;

  // [3]
  this->m_mouse_platform_pos = { static_cast<int32_t>(_x * this->m_win_size.width()),static_cast<int32_t>(_y * this->m_win_size.height()) };
  this->m_mouse_viewport_pos = { _x* this->m_grid_num.width(), _y*this->m_grid_num.height() };
  this->m_mouse_renderer_pos = m_mouse_viewport_pos; //TODO 未实现
}

void yd2d::GameEngine::onSlotUpdateMouseWheel(int32_t delta)
{
  m_mouse_wheel_delta = delta;
}

void yd2d::GameEngine::onSlotUpdateWindowSize(int32_t width, int32_t height)
{
  m_win_size = { width, height };
  m_platform_resized = true;
}

void yd2d::GameEngine::onSlotUpdateMouseState(int32_t button, bool state)
{
  this->m_new_mouse_state[static_cast<int>(button)]= state ? yd2d::HWBtnState::Pressed: yd2d::HWBtnState::Released ;
}

void yd2d::GameEngine::onSlotTerminate()
{
  this->terminate();
}

void yd2d::GameEngine::onSlotUpdateKeyState(int32_t key, bool state)
{
  this->m_new_keyboard_state[static_cast<int>(this->m_vk2key[key])] = state ?  yd2d::HWBtnState::Pressed: yd2d::HWBtnState::Released;
}

void yd2d::GameEngine::updateHWButtonInRendererThread()
{
  auto ScanHardware = [&](yd2d::HWButton* pKeys, yd2d::HWBtnState* pStateOld, yd2d::HWBtnState* pStateNew, uint32_t nKeyCount)
  {
    for (uint32_t i = 0; i < nKeyCount; i++)
    {
      pKeys[i].setHold(pStateNew[i] == pStateOld[i]);
      pKeys[i].setState(pStateNew[i]);
      pStateOld[i] = pStateNew[i];
      if (pStateNew[i] == HWBtnState::Pressed) {
        int x;
        x = 1;
      }
    }
  };

  ScanHardware(this->m_keyboard_state.data(), this->m_old_keyboard_state.data(), this->m_new_keyboard_state.data(), yd2d::KeyBoardNumbers);
  ScanHardware(this->m_mouse_state.data(), this->m_old_mouse_state.data(), this->m_new_mouse_state.data(), yd2d::MouseNumbers);

}

void yd2d::GameEngine::coreRenderThread()
{
  std::unique_lock lock(this->m_mutex_render_thread);
  // TODO 这样放不太合理
  this->mp_renderer = new yd2d::RendererOGL10Windows();
  this->mp_renderer->createDevice({ this->mp_platform->handle()}, m_vsync);
  this->mp_renderer->prepareDevice();
  this->mp_renderer->updateViewport({0,0 }, m_win_size);
  this->mp_renderer->updateOrtho2d(0, static_cast<float>(this->m_grid_num.width()), 0, static_cast<float>(this->m_grid_num.height()));

  m_game_time.start();
  auto start_time =  this->m_game_time.time();
  auto end_time =  this->m_game_time.time();
  while (m_atomic_status) {
    updateHWButtonInRendererThread(); //在 帧之间更新一些属性

    this->mp_renderer->prepareDevice();

    if (this->m_platform_resized) {
      this->mp_renderer->updateViewport({0,0}, m_win_size);
      this->mp_renderer->updateOrtho2d(0, static_cast<float>(this->m_grid_num.width()), 0, static_cast<float>(this->m_grid_num.height()));
      m_platform_resized = false;
    }

    this->mp_renderer->clearFrame(yd2d::BLACK, true);

    end_time =  this->m_game_time.time();
    auto delte_time = end_time - start_time;
    //printf("%f,%f,%f\n", start_time, end_time, eps);
    start_time = end_time;

    this->onUpdateOneFrame(GameTime::toSec(delte_time));
    this->mp_renderer->displayFrame();

  }

  // TODO 这样放不太合理
  this->mp_renderer->destroyDevice();
  delete this->mp_renderer;
  this->mp_renderer = nullptr;
}

yd2d::HWButton GameEngine::getKey(yd2d::Key key) const noexcept
{
  return m_keyboard_state[key];
}

yd2d::HWButton GameEngine::getMouse(yd2d::Mouse mouse) const noexcept {
  return m_mouse_state[mouse];
}

yd2d::HWButton GameEngine::getLeftMouse() const noexcept {
  return getMouse(Mouse::LeftMouse);
}

yd2d::HWButton GameEngine::getMiddleMouse() const noexcept {
  return getMouse(Mouse::MiddleMouse);
}

yd2d::HWButton GameEngine::getRightMouse() const noexcept {
  return getMouse(Mouse::RightMouse);
}

bool yd2d::GameEngine::onUpdateOneFrame(double delte_time)
{
  printf("%f\n",delte_time);
  static float x = 0;
  static float y = 0;

  auto lm = getLeftMouse();
  auto key_a = getKey(A);
  auto key_d = getKey(D);
  auto key_s = getKey(S);
  auto key_w = getKey(W);

  if(key_a.isPreessed() )
  {
    x-= delte_time;
  }

  if(key_s.isPreessed() )
  {
    y-= delte_time;
  }

  if(key_d.isPreessed())
  {
    x+= delte_time;
  }

  if(key_w.isPreessed())
  {
    y+= delte_time;
  }

  glRectf( x- 1,  y- 1,  x+ 1,  y+ 1);
  return true;
}
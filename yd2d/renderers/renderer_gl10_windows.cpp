//
// Created by ydar on 2021/1/28.
//

#include "renderer_gl10_windows.hpp"
#include <assert.h>
typedef BOOL(WINAPI wglSwapInterval_t) (int interval);
static wglSwapInterval_t* wglSwapInterval = nullptr;

yd2d::rcode yd2d::RendererOGL10Windows::createDevice(std::vector<std::any> params, bool vsync) {
  this->m_gl_thread_id = std::this_thread::get_id();
  this->m_gl_device_context = GetDC(std::any_cast<HWND>(params[0]));
  PIXELFORMATDESCRIPTOR pfd =
      {
          sizeof(PIXELFORMATDESCRIPTOR), 1,
          PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
          PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          PFD_MAIN_PLANE, 0, 0, 0, 0
      };

  int pf = 0;
  if (!(pf = ChoosePixelFormat(this->m_gl_device_context, &pfd))) return yd2d::rcode::FAIL;
  SetPixelFormat(this->m_gl_device_context, pf, &pfd);

  if (!(this->m_gl_render_context = wglCreateContext(this->m_gl_device_context))) return yd2d::rcode::FAIL;
  wglMakeCurrent(this->m_gl_device_context, this->m_gl_render_context);

  // Remove Frame cap
  wglSwapInterval = (wglSwapInterval_t*)wglGetProcAddress("wglSwapIntervalEXT");
  if (wglSwapInterval && !vsync) wglSwapInterval(0);

  glEnable(GL_TEXTURE_2D); // Turn on texturing
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  return yd2d::rcode::OK;
}

yd2d::rcode yd2d::RendererOGL10Windows::destroyDevice() {
  wglDeleteContext(this->m_gl_render_context);
  return yd2d::rcode::OK;
}
void yd2d::RendererOGL10Windows::displayFrame() {
  SwapBuffers(this->m_gl_device_context);
}
void yd2d::RendererOGL10Windows::prepareDevice() {
  assert(std::this_thread::get_id() == this->m_gl_thread_id); //必须运行在创建的线程
  if (wglGetCurrentDC() != m_gl_device_context && wglGetCurrentContext() != m_gl_render_context) {
    wglMakeCurrent(m_gl_device_context, m_gl_render_context);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }
}
void yd2d::RendererOGL10Windows::clearFrame(yd2d::Pixel color, bool clear_depth) {
  glClearColor(float(color.r) / 255.0f, float(color.g) / 255.0f, float(color.b) / 255.0f, float(color.a) / 255.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  if (clear_depth) glClear(GL_DEPTH_BUFFER_BIT);
}
uint32_t yd2d::RendererOGL10Windows::createTexture(uint32_t width, uint32_t height) {
  uint32_t id = 0;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  return id;
}
uint32_t yd2d::RendererOGL10Windows::deleteTexture(uint32_t id) {
  glDeleteTextures(1, &id);
  return id;
}
void yd2d::RendererOGL10Windows::applyTexture(uint32_t id) {
  glBindTexture(GL_TEXTURE_2D, id);
}
void yd2d::RendererOGL10Windows::updateViewport(const yd2d::Vec2d &pos, const yd2d::Size &size) {
  glViewport(pos.x(), pos.y(), size.width(), size.height());
}
void yd2d::RendererOGL10Windows::updateOrtho2d(float left, float right, float bottom, float top) {
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glOrtho(left, right, bottom, top,-100,100);
}

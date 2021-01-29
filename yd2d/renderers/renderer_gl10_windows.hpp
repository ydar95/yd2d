//
// Created by ydar on 2021/1/28.
//

#ifndef YD2D_YD2D_RENDERERS_RENDERER_GL10_WINDOWS_HPP_
#define YD2D_YD2D_RENDERERS_RENDERER_GL10_WINDOWS_HPP_

#include "base_renderder.hpp"

#include <vector>
#include <thread>

#if defined(_WIN32)
#include <windows.h>
#include <gl/GL.h>
namespace yd2d {

class RendererOGL10Windows
  : public yd2d::Renderer
{
 public:
  virtual yd2d::rcode createDevice(std::vector<std::any> params, bool vsync) override;
  virtual yd2d::rcode destroyDevice() override;

  virtual void       displayFrame() override;
  virtual void       prepareDevice() override;
  virtual void       clearFrame(yd2d::Pixel color, bool clear_depth) override;

  virtual uint32_t   createTexture(uint32_t  width, uint32_t height) override;
  virtual uint32_t   deleteTexture(uint32_t id) override;
  virtual void       applyTexture(uint32_t id) override;

  virtual void       updateViewport(const yd2d::Vec2d & pos, const yd2d::Size& size) override;
  virtual void       updateOrtho2d(float left, float right, float bottom, float top) override;
 protected:
  HDC m_gl_device_context = nullptr;
  HGLRC m_gl_render_context = nullptr;
  std::thread::id m_gl_thread_id;// defualt = id(0)
};

}

#endif
#endif //YD2D_YD2D_RENDERERS_RENDERER_GL10_WINDOWS_HPP_

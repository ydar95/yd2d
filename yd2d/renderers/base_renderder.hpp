//
// Created by ydar on 2021/1/28.
//

#ifndef YD2D_YD2D_RENDERERS_BASE_RENDERDER_HPP_
#define YD2D_YD2D_RENDERERS_BASE_RENDERDER_HPP_



#include "../base/rcode.hpp"
#include "../base/pixel.hpp"
#include "../math/vector2d.hpp"
#include "../math/size.hpp"

#include <vector>
#include <any>
namespace yd2d {
class Renderer
{
  public:
    virtual yd2d::rcode createDevice(std::vector<std::any> params, bool vsync) = 0;
    virtual yd2d::rcode destroyDevice() = 0;

    virtual void       displayFrame() = 0;
    virtual void       prepareDevice() = 0;
    virtual void       clearFrame(yd2d::Pixel color, bool clear_depth) = 0;

    virtual uint32_t   createTexture(uint32_t  width, uint32_t height) = 0;
    virtual uint32_t   deleteTexture(uint32_t id) = 0;
    virtual void       applyTexture(uint32_t id) = 0;

    virtual void       updateViewport(const yd2d::Vec2d & pos, const yd2d::Size& size) = 0;
    virtual void       updateOrtho2d(float left, float right, float bottom, float top) = 0;
};

}


#endif //YD2D_YD2D_RENDERERS_BASE_RENDERDER_HPP_

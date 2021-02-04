//
// Created by yd on 2021/2/2.
//

#ifndef YD2D_YD2D_TEXTURE_TEXTURE_HPP_
#define YD2D_YD2D_TEXTURE_TEXTURE_HPP_

#include "../yd2d_typedef.hpp"
#include "../renderers/base_renderder.hpp"
#include <string>
namespace yd2d {

enum class TextureFormat{
  Gray=1, //灰色
  GrayA=2,//灰色带透明
  RGB=3,  //红绿蓝
  RGBA=4  //红绿蓝带透明
};

class Texture2d {
 private:
  Size m_size;
  int32_t m_texture_id;
  TextureFormat m_texture_format = TextureFormat::RGBA; // 现在只用 RGBA
  Renderer  *mp_renderer;
 public:
  Texture2d(const std::string &filename,yd2d::Renderer *renderer);
  ~Texture2d();
  int32_t textureId() const noexcept;
  Size size() const noexcept;
  bool state() const noexcept; //判断是否加载成功
};
}

#endif //YD2D_YD2D_TEXTURE_TEXTURE_HPP_

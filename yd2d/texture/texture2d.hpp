//
// Created by yd on 2021/2/2.
//

#ifndef YD2D_YD2D_TEXTURE_TEXTURE2D_HPP_
#define YD2D_YD2D_TEXTURE_TEXTURE2D_HPP_

#include "../yd2d_typedef.hpp"
#include <string>
namespace yd2d {

enum class TextureFormat{
  Gray=1, //灰色
  GrayA=2,//灰色带透明
  RGB=3,  //红绿蓝
  RGBA=4  //红绿蓝带透明
};

class Renderer;
class Texture2dFrame;
class Texture2d {
 private:
  Size m_size;
  int32_t m_texture_id;
  TextureFormat m_texture_format = TextureFormat::RGBA; // 现在只用 RGBA
  Renderer  *mp_renderer;
 public:
  Texture2d(){}
  Texture2d(const std::string &filename,yd2d::Renderer *renderer);
  ~Texture2d();
  [[nodiscard]] int32_t texture_id() const noexcept;
  [[nodiscard]] Size size() const noexcept;
  [[nodiscard]] bool state() const noexcept; //判断是否加载成功

  Texture2dFrame createFrame(Rect image_rect);
};

class Texture2dFrame
{
 private:
  int32_t m_texture_id;
  RectF m_texture_rect;
 public:
  Texture2dFrame(int32_t texture_id=0,RectF texture_rect=RectF());
  [[nodiscard]] int32_t texture_id() const noexcept;
  [[nodiscard]] RectF texture_rect() const noexcept;
};


}

#endif //YD2D_YD2D_TEXTURE_TEXTURE2D_HPP_

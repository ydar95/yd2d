//
// Created by yd on 2021/2/2.
//

#include "texture2d.hpp"
#include "../tools/image_utils.hpp"
#include "../thirdparty/stb/stb_image.h"
#include "../renderers/base_renderder.hpp"
yd2d::Texture2d::Texture2d(const std::string &filename,yd2d::Renderer *renderer)
  :mp_renderer(renderer)
{
  int w,h,ch;
  unsigned char *data = stbi_load(filename.c_str(), &w, &h, &ch, STBI_rgb_alpha);
  if(data!= nullptr) {
    yd2d::tools::image_utils::flip_vertical(data,w,h,4);
    this->m_texture_id = this->mp_renderer->createTexture(data, w, h);
    this->mp_renderer->applyTexture(this->m_texture_id);
    this->m_size = yd2d::Size(w,h);
    //printf("texture id:%d,%d,%d,%d\n",m_texture_id,w,h,ch);
    stbi_image_free(data);
  }
}

yd2d::Texture2d::~Texture2d()
{
  if(this->state()){
    this->mp_renderer->deleteTexture(this->m_texture_id);
  }
}

int32_t yd2d::Texture2d::texture_id() const noexcept
{
  return this->m_texture_id;
}

yd2d::Size yd2d::Texture2d::size() const noexcept
{
  return this->m_size;
}

bool yd2d::Texture2d::state() const noexcept
{
  if(this->size().height()>0 && this->size().width()>0 && this->texture_id()>0){
    return true;
  }
  return false;
}
yd2d::Texture2dFrame yd2d::Texture2d::createFrame(yd2d::Rect image_rect) {
  RectF texture_rect;
  texture_rect.setLeft(static_cast<float >(image_rect.left())/this->size().width());
  texture_rect.setRight(static_cast<float >(image_rect.right())/this->size().width());
  texture_rect.setTop(static_cast<float >(1-image_rect.bottom())/this->size().height());
  texture_rect.setBottom(static_cast<float >(1-image_rect.top())/this->size().height());

  return yd2d::Texture2dFrame(this->texture_id(),texture_rect);
}

yd2d::Texture2dFrame::Texture2dFrame(int32_t texture_id, yd2d::RectF texture_rect)
{
  m_texture_id=texture_id;
  m_texture_rect=texture_rect;
}
int32_t yd2d::Texture2dFrame::texture_id() const noexcept {
  return this->m_texture_id;
}
yd2d::RectF yd2d::Texture2dFrame::texture_rect() const noexcept {
  return this->m_texture_rect;
}

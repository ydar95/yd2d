//
// Created by yd on 2021/2/2.
//

#include "texture.hpp"
#include "../thirdparty/stb/stb_image.h"

yd2d::Texture2d::Texture2d(const std::string &filename,yd2d::Renderer *renderer)
  :mp_renderer(renderer)
{
  int w,h,ch;
  unsigned char *data = stbi_load(filename.c_str(), &w, &h, &ch, STBI_rgb_alpha);
  if(data!= nullptr) {
    this->m_texture_id = this->mp_renderer->createTexture(data, w, h);
    this->mp_renderer->applyTexture(this->m_texture_id);
    this->m_size = yd2d::Size(w,h);
    stbi_image_free(data);
  }
}
yd2d::Texture2d::~Texture2d() {
  if(this->state()){
    this->mp_renderer->deleteTexture(this->m_texture_id);
  }
}
int32_t yd2d::Texture2d::textureId() const noexcept {
  return this->m_texture_id;
}
yd2d::Size yd2d::Texture2d::size() const noexcept {
  return this->m_size;
}
bool yd2d::Texture2d::state() const noexcept {
  if(this->size().height()>0 && this->size().width()>0 && this->textureId()>0){
    return true;
  }
  return false;
}

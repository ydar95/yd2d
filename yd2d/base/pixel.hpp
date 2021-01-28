//
// Created by ydar on 2021/1/28.
//

#ifndef YD2D_INCLUDE_YD2D_BASE_PIXEL_HPP_
#define YD2D_INCLUDE_YD2D_BASE_PIXEL_HPP_

#include<cstdint>
namespace yd2d {
class Pixel {
public:
  inline static constexpr uint8_t  kDefaultAlpha = 0xFF;
  inline static constexpr uint32_t kDefaultPixel = (kDefaultAlpha << 24); //0xFF000000
public:
  union
  {
    uint32_t color = kDefaultPixel;
    struct { uint8_t r; uint8_t g; uint8_t b; uint8_t a; };
  };

  explicit Pixel(uint32_t p) { color = p; };
  constexpr Pixel() { r = 0; g = 0; b = 0; a = kDefaultAlpha; }
  constexpr Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = kDefaultAlpha) { color = red | (green << 8) | (blue << 16) | (alpha << 24); };
//    Pixel(float red, float green, float blue, float alpha = 1.0f)
//      :Pixel(uint8_t(red * 255.0f), uint8_t(green * 255.0f), uint8_t(blue * 255.0f), uint8_t(alpha * 255.0f))
//    {}
  inline bool operator==(const Pixel& p) const { return color == p.color; }
  inline bool operator!=(const Pixel& p) const { return color != p.color; }
  inline uint8_t* data() {
    return reinterpret_cast<uint8_t*>(&color);
  }
};

[[maybe_unused]] static constexpr Pixel
  GREY(192, 192, 192),
  DARK_GREY(128, 128, 128),
  VERY_DARK_GREY(64, 64, 64),
  RED(255, 0, 0),
  DARK_RED(128, 0, 0),
  VERY_DARK_RED(64, 0, 0),
  YELLOW(255, 255, 0),
  DARK_YELLOW(128, 128, 0),
  VERY_DARK_YELLOW(64, 64, 0),
  GREEN(0, 255, 0),
  DARK_GREEN(0, 128, 0),
  VERY_DARK_GREEN(0, 64, 0),
  CYAN(0, 255, 255),
  DARK_CYAN(0, 128, 128),
  VERY_DARK_CYAN(0, 64, 64),
  BLUE(0, 0, 255),
  DARK_BLUE(0, 0, 128),
  VERY_DARK_BLUE(0, 0, 64),
  MAGENTA(255, 0, 255),
  DARK_MAGENTA(128, 0, 128),
  VERY_DARK_MAGENTA(64, 0, 64),
  WHITE(255, 255, 255),
  BLACK(0, 0, 0),
  BLANK(0, 0, 0, 0);
}



#endif //YD2D_INCLUDE_YD2D_BASE_PIXEL_HPP_

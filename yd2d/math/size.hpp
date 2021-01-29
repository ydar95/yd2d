//
// Created by ydar on 2021/1/27.
//

#ifndef YD2D_INCLUDE_YD2D_MATH_SIZE_HPP_
#define YD2D_INCLUDE_YD2D_MATH_SIZE_HPP_

#include <cstdint>
namespace yd2d{

template<typename T>
class Size_{
 protected:
  T m_width;
  T m_height;

 public:
  inline constexpr Size_() :  m_width(0),m_height(0){}
  inline constexpr Size_(T _width, T _height) : m_width(_width),m_height(_height) {   }
  inline constexpr Size_(const Size_ &sz) : m_width(sz.m_width), m_height(sz.m_height) {  }

  [[nodiscard]] inline constexpr T width() const noexcept {return m_width;}
  [[nodiscard]] inline constexpr T height() const noexcept {return m_height;}
  inline T& rwidth() noexcept {return m_width;}
  inline T& rheight() noexcept {return m_height;}

  inline Size_  operator +  (const Size_& rhs) const { return Size_(this->width() + rhs.width(), this->height() + rhs.height()); }
  inline Size_  operator -  (const Size_& rhs) const { return Size_(this->width() - rhs.width(), this->height() - rhs.height()); }
  inline Size_  operator *  (const T& rhs)           const { return Size_(this->width() * rhs, this->height() * rhs); }
  inline Size_  operator /  (const T& rhs)           const { return Size_(this->width() / rhs, this->height() / rhs); }
  inline Size_& operator += (const Size_& rhs) { this->m_width += rhs.width(); this->m_height += rhs.height(); return *this; }
  inline Size_& operator -= (const Size_& rhs) { this->m_width -= rhs.width(); this->m_height -= rhs.height(); return *this; }
  inline Size_& operator *= (const T& rhs) { this->m_width *= rhs; this->m_height *= rhs; return *this; }
  inline Size_& operator /= (const T& rhs) { this->m_width /= rhs; this->m_height /= rhs; return *this; }
  inline explicit operator Size_<int32_t>() const { return { static_cast<int32_t>(this->width()), static_cast<int32_t>(this->height()) }; }
  inline explicit operator Size_<float>() const { return { static_cast<float>(this->width()), static_cast<float>(this->height()) }; }

};

typedef Size_<int32_t> Size;
typedef Size_<float> SizeF;
}


#endif //YD2D_INCLUDE_YD2D_MATH_SIZE_HPP_

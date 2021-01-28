//
// Created by ydar on 2021/1/27.
//

#ifndef YD2D_INCLUDE_YD2D_MATH_RECT_HPP_
#define YD2D_INCLUDE_YD2D_MATH_RECT_HPP_

#include "vector2d.hpp"
#include "size.hpp"
#include <cstdint>
namespace yd2d{

  template<typename T>
  class Rect_{
   protected:
    T m_x1; //left
    T m_y1; //bottom
    T m_x2; //right
    T m_y2; //top

   public:
    inline constexpr Rect_() noexcept : m_x1(0), m_y1(0), m_x2(-1), m_y2(-1) {};
    inline constexpr Rect_(T left,T right,T bottom,T top) noexcept : m_x1(left), m_y1(bottom), m_x2(right), m_y2(top) {};
    inline constexpr Rect_(const Vec2_<T> &bottomleft, const Vec2_<T>& topright) noexcept
      :m_x1(bottomleft.x()), m_y1(bottomleft.y()), m_x2(topright.x()), m_y2(topright.y()){};
    inline constexpr Rect_(const Vec2_<T> &centre, const Size_<T> &size) noexcept{
      T half_width = size.width() / 2;
      T half_height = size.height() / 2;

      m_x1 = centre.x() - half_width;
      m_x2 = centre.x() + (size.width()-half_width);

      m_y1 = centre.y() - half_height;
      m_y2 = centre.y() + (size.height() - half_height);
    };

    constexpr T left() const noexcept {return m_x1;}
    constexpr T right() const noexcept { return m_x2; }
    constexpr T bottom() const noexcept { return m_y1; }
    constexpr T top() const noexcept { return m_y2; }

    constexpr T width()const noexcept { return m_x2 - m_x1; }
    constexpr T height()const noexcept { return m_y2 - m_y1; }
    constexpr Size_<T> size()const noexcept { return Size_<T>(this->width(),this->height()); }

    constexpr inline T cx() const noexcept { return (m_x1 + m_x2) / 2; }
    constexpr inline T cy() const noexcept { return (m_y1 + m_y2) / 2; }
    constexpr inline void setLeft(int left) noexcept { m_x1 = left; }
    constexpr inline void setTop(int top) noexcept { m_y2 = top; }
    constexpr inline void setRight(int right) noexcept { m_x2 = right; }
    constexpr inline void setBottom(int bottom) noexcept { m_y2 = bottom; }
    constexpr inline void setCenterX(int x) noexcept
    {
      auto width = this->width();
      auto half_width = width / 2;

      m_x1 = x - half_width;
      m_x2 = x + (width - half_width);
    }
    constexpr inline void setCenterY(int y) noexcept
    {
      auto height = this->height();
      auto half_height = height / 2;

      m_y1 = y - half_height;
      m_y2 = y + (height - half_height);
    }

    constexpr inline void setTopLeft(const Vec2_<T>& p) noexcept 
    {
      setLeft(p.x());
      setTop(p.y());
    }
    constexpr inline void setBottomRight(const Vec2_<T>& p) noexcept
    {
      setRight(p.x());
      setBottom(p.y());
    }
    constexpr inline void setTopRight(const Vec2_<T>& p) noexcept
    {
      setRight(p.x());
      setTop(p.y());
    }
    constexpr inline void setBottomLeft(const Vec2_<T>& p) noexcept
    {
      setLeft(p.x());
      setBottom(p.y());
    }

    constexpr inline Vec2_<T> topLeft() const noexcept
    {
      return { left() ,top() };
    }
    constexpr inline Vec2_<T> bottomRight() const noexcept
    {
      return { right() ,bottom() };
    }
    constexpr inline Vec2_<T> topRight() const noexcept
    {
      return { right() ,top() };
    }
    constexpr inline Vec2_<T> bottomLeft() const noexcept
    {
      return { left() ,bottom() };
    }
    constexpr inline Vec2_<T> center() const noexcept
    {
      return { cx(),cy() };
    }


  };

  typedef Rect_<int32_t> Rect;
  typedef Rect_<float> RectF;
}


#endif //YD2D_INCLUDE_YD2D_MATH_RECT_HPP_

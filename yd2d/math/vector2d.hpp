//
// Created by ydar on 2021/1/26.
//

#ifndef YD2D_INCLUDE_YD2D_MATH_Vec2__HPP_
#define YD2D_INCLUDE_YD2D_MATH_Vec2__HPP_

#include<cstdint>
#include<cmath>
namespace yd2d {

template<typename T>
class Vec2_ {
 protected:
  T m_x;
  T m_y;

 public:
  inline Vec2_() : m_x(0), m_y(0) {}
  inline Vec2_(T _x, T _y) : m_x(_x), m_y(_y) {   }
  inline Vec2_(const Vec2_& v) : m_x(v.m_x), m_y(v.m_y) {  }

  [[nodiscard]] inline constexpr T x() const noexcept {return m_x;}
  [[nodiscard]] inline constexpr T y() const noexcept {return m_y;}
  inline T& rx() noexcept {return m_x;}
  inline T& ry() noexcept {return m_y;}

  inline T mag() { return std::sqrt(x() * x() + y() * y()); }
  inline T mag2() { return x() * x() + y() * y(); }
  inline Vec2_  norm() { T r = 1 / mag(); return Vec2_(x() * r, y() * r); }
  inline Vec2_  perp() { return Vec2_(-y(), x()); }
  inline T dot(const Vec2_& rhs) { return this->x() * rhs.x() + this->y() * rhs.y(); }
  inline T cross(const Vec2_& rhs) { return this->x() * rhs.y() - this->y() * rhs.x(); }
  inline Vec2_  operator +  (const Vec2_& rhs) const { return Vec2_(this->x() + rhs.x(), this->y() + rhs.y()); }
  inline Vec2_  operator -  (const Vec2_& rhs) const { return Vec2_(this->x() - rhs.x(), this->y() - rhs.y()); }
  inline Vec2_  operator *  (const T& rhs)           const { return Vec2_(this->x() * rhs, this->y() * rhs); }
  inline Vec2_  operator *  (const Vec2_& rhs) const { return Vec2_(this->x() * rhs.x(), this->y() * rhs.y()); }
  inline Vec2_  operator /  (const T& rhs)           const { return Vec2_(this->x() / rhs, this->y() / rhs); }
  inline Vec2_  operator /  (const Vec2_& rhs) const { return Vec2_(this->x() / rhs.x(), this->y() / rhs.y()); }
  inline Vec2_& operator += (const Vec2_& rhs) { this->m_x += rhs.x(); this->m_y += rhs.y(); return *this; }
  inline Vec2_& operator -= (const Vec2_& rhs) { this->m_x -= rhs.x(); this->m_y -= rhs.y(); return *this; }
  inline Vec2_& operator *= (const T& rhs) { this->m_x *= rhs; this->m_y *= rhs; return *this; }
  inline Vec2_& operator /= (const T& rhs) { this->m_x /= rhs; this->m_y /= rhs; return *this; }
  inline explicit operator Vec2_<int32_t>() const { return { static_cast<int32_t>(this->x()), static_cast<int32_t>(this->y()) }; }
  inline explicit operator Vec2_<float>() const { return { static_cast<float>(this->x()), static_cast<float>(this->y()) }; }
  inline explicit operator Vec2_<double>() const { return { static_cast<double>(this->x()), static_cast<double>(this->y()) }; }

  
};

template<class T> inline Vec2_<T> operator * (const float& lhs, const Vec2_<T>& rhs)
{
  return Vec2_<T>((T)(lhs * (float)rhs.x()), (T)(lhs * (float)rhs.y()));
}
template<class T> inline Vec2_<T> operator * (const double& lhs, const Vec2_<T>& rhs)
{
  return Vec2_<T>((T)(lhs * (double)rhs.x()), (T)(lhs * (double)rhs.y()));
}
template<class T> inline Vec2_<T> operator * (const int& lhs, const Vec2_<T>& rhs)
{
  return Vec2_<T>((T)(lhs * (int)rhs.x()), (T)(lhs * (int)rhs.y()));
}
template<class T> inline Vec2_<T> operator / (const float& lhs, const Vec2_<T>& rhs)
{
  return Vec2_<T>((T)(lhs / (float)rhs.x()), (T)(lhs / (float)rhs.y()));
}
template<class T> inline Vec2_<T> operator / (const double& lhs, const Vec2_<T>& rhs)
{
  return Vec2_<T>((T)(lhs / (double)rhs.x()), (T)(lhs / (double)rhs.y()));
}
template<class T> inline Vec2_<T> operator / (const int& lhs, const Vec2_<T>& rhs)
{
  return Vec2_<T>((T)(lhs / (int)rhs.x()), (T)(lhs / (int)rhs.y()));
}

typedef Vec2_<int32_t>	Vec2d;
typedef Vec2_<float>	VecF2d;

}
#endif //YD2D_INCLUDE_YD2D_MATH_Vec2__HPP_

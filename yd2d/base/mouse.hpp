//
// Created by ydar on 2021/1/28.
//
#pragma once
#ifndef YD2D_INCLUDE_YD2D_BASE_MOUSE_HPP_
#define YD2D_INCLUDE_YD2D_BASE_MOUSE_HPP_

#include <cstdint>

namespace yd2d{

enum Mouse:int32_t
{
  LeftMouse,
  RightMouse,
  MiddleMouse
};//注意 这个必须放在末尾，表示定义的鼠标按键数量
static constexpr int32_t MouseNumbers=3;

};

#endif //YD2D_INCLUDE_YD2D_BASE_MOUSE_HPP_

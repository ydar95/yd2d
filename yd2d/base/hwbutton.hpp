//
// Created by ydar on 2021/1/28.
//

#ifndef YD2D_INCLUDE_YD2D_BASE_HWBUTTON_HPP_
#define YD2D_INCLUDE_YD2D_BASE_HWBUTTON_HPP_

#include<cstdint>
namespace yd2d {

enum class HWBtnState :int8_t {
    Released,  //放开
    Pressed    //按下
};

class HWButton
{
private:
    //当前状态是放下 按下还是放开
    HWBtnState state = HWBtnState::Released;
    bool is_hold = false;
public:
    inline constexpr bool isPreessed() const noexcept { return state == HWBtnState::Pressed; }
    inline constexpr bool isReleased() const noexcept { return state == HWBtnState::Released; }
    inline constexpr bool isHold() const noexcept { return is_hold; }
    inline void setState(HWBtnState state) { state = state; }
    inline void setHold(bool hold) { is_hold = hold; }
};

}

#endif //YD2D_INCLUDE_YD2D_BASE_HWBUTTON_HPP_

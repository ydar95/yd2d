//
// Created by yd on 2021/2/3.
//

#ifndef YD2D_YD2D_TOOLS_IMAGE_UTILS_HPP_
#define YD2D_YD2D_TOOLS_IMAGE_UTILS_HPP_

#include <cstdint>
#include <algorithm>
namespace yd2d::tools::image_utils
{
  inline void flip_vertical(uint8_t *rbga,int32_t w,int32_t h,int32_t ch)
  {
    const int32_t line_length = w*ch;
    for(int32_t row=0;row<h/2;row++)
    {
      for(int32_t col=0;col<w*ch;col++)
      {
        std::swap(rbga[row*line_length+col],rbga[(h-row-1)*line_length+col]);
      }
    }
  }
}


#endif //YD2D_YD2D_TOOLS_IMAGE_UTILS_HPP_

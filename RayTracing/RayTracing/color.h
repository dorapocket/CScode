#ifndef COLOR_H
#define COLOR_H
/*
2020.5.19
颜色类
*/
#include "vec3.h"
#include <iostream>

//输出颜色信息到标准流
void write_color(std::ostream& out, color pixel_color, int samples_per_pixel) {
    //获取颜色分量
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    //平均化采样 防止锯齿
    auto scale = 1.0 / samples_per_pixel;
    /*
    r *= scale;
    g *= scale;
    b *= scale;
    */
    //简单的伽马矫正， gamma=2.0 即开二次根号 
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // 限幅输出
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif
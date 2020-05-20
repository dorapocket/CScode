#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <cstdlib>
/*常用函数和头文件汇总文件*/
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

//常数
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//实用换算函数
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180;
}
//随机数生成器
inline double random_double() {
    //[0,1)
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    //[min,max)
    return min + (max - min) * random_double();
}
//裁剪函数 限制幅度
inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

//头文件
#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"
#include "camara.h"
#include "aarect.h"


#endif
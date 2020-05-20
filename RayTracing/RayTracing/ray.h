#ifndef RAY_H
#define RAY_H
#include "vec3.h"
/*
2020.5.19
光线类
齐次坐标表示为P(t)=A+tb  A为起始点，b为方向，t为参数，负数代表向后走
*/
class ray {
public:
    //构造函数，光线的信息：方向、颜色
    ray() {}
    ray(const point3& origin, const vec3& direction)
        : orig(origin), dir(direction)
    {}
    //返回颜色和方向
    point3 origin() const { return orig; }
    vec3 direction() const { return dir; }

    //齐次坐标形式的光线
    point3 at(double t) const {
        return orig + t * dir;
    }

public:
    point3 orig;
    vec3 dir;
};
#endif
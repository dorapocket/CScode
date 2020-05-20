#pragma once
#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
class material;

/*光线击中判定类*/
struct hit_record {
    point3 p;
    vec3 normal;
    double t;
    shared_ptr<material> mat_ptr;//材质
    bool front_face;//判断法线方向内外

    inline void set_face_normal(const ray& r, const vec3& outward_normal) { 
        front_face = dot(r.direction(), outward_normal) < 0;//点积判断是从物体内还是从外入射 并存储进结构体
        normal = front_face ? outward_normal : -outward_normal;//根据点积设定法线方向
    }
};

class hittable {
public:
    //虚函数 tmax 和min是敏感阈值
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif
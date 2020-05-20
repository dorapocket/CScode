#pragma once
#ifndef CAMERA_H
#define CAMERA_H

/*
摄像机类
设置宽高比、视口大小、方向（扫描关键点等）
*/
class camera {
public:
    camera(
        point3 lookfrom,//相机位置
        point3 lookat,//目标点位置
        vec3   vup,//向上矢量投影到视口平面的标准方向
        double vfov, //垂直方向的 角度表示的视口
        double aspect_ratio,
        double aperture,
        double focus_dist//焦距
    ) {
        //计算y坐标h
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta / 2);
        
        //真正的视口长宽
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        //相机坐标
        auto w = unit_vector(lookfrom - lookat);
        auto u = unit_vector(cross(vup, w));
        auto v = cross(w, u);

        //赋值相机位置
        origin = lookfrom;
        /*
        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;*/
        //带景深的渲染
        horizontal = focus_dist * viewport_width * u;//聚焦平面内的物体扫描
        vertical = focus_dist * viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

        lens_radius = aperture / 2;
    }

    //获取直接照射到像素的光线（起始点、方向）
    ray get_ray(double s, double t) const {
       // return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
        //带景深版本
        vec3 rd = lens_radius * random_in_unit_disk();//随机视口光线
        vec3 offset = u * rd.x() + v * rd.y();//相机坐标偏移
        return ray(
            origin + offset,
            lower_left_corner + s * horizontal + t * vertical - origin - offset
        );
    }

private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;
};
#endif
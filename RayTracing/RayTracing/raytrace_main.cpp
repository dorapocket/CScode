#include "common.h"
#include <iostream>
/*主程序
设视口y高度为-1~1
*/
/*
判断光线是否击中生成的球
传入：球心 半径 光线
原理：计算公式见文档
*/
bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return -1.0;
    }
    else {
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
}

/*
光线颜色计算
传入：光线 世界物体列表 最大递归深度
*/
color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;
    //超出递归深度，返回黑色
    if (depth <= 0)
        return color(0, 0, 0);

    if (world.hit(r, 0.001, infinity, rec)) {//如果有击中物体 且防止t为很小的时候的光交点，防止暗疮
        //point3 target = rec.p + rec.normal + random_in_unit_sphere();//获取法线方向单位圆内的点作为漫反射随机端点
       /* point3 target = rec.p + random_in_hemisphere(rec.normal);//升级版
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world,depth-1);//递归查询漫反射光线与其他物体作用,每次反射削减一半能量
        */
        ray scattered;//反射光
        color attenuation;//反射颜色
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))//获取反射光线信息存储到上面的变量
            return attenuation * ray_color(scattered, world, depth - 1);//递归计算
        return color(0, 0, 0);
    }
    //否则返回背景色（融合蓝色和白色）
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);//y范围是-1~1 这里t缩放为0~1方便插值
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}


/*
随机场景生成
*/
hittable_list random_scene() {
    hittable_list world;//场景列表
    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));//地面
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();//随机材质
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());//随机位置
            //向场景中添加随机球
            if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;
                if (choose_mat < 0.8) {
                    //漫反射材质
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // 金属材质
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else {
                    // 玻璃材质
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}


int main() {
    //16：9视口宽度设置
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 1920;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;//附近随机采样数
    const int max_depth = 50;//最大递归深度

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    /*
    //场景物体
    hittable_list world;//记录物体的列表
    //world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    //world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
    //空心玻璃气泡
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5, make_shared<lambertian>(color(.1, .2, .5))));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, make_shared<lambertian>(color(.8, .8, 0.))));
    world.add(make_shared<sphere>(point3(1, 0, -1), 0.5, make_shared<metal>(color(.8, .6, .2), 0.3)));
    world.add(make_shared<sphere>(point3(-1, 0, -1), 0.5, make_shared<dielectric>(1.5)));
    world.add(make_shared<sphere>(point3(-1, 0, -1), -0.45, make_shared<dielectric>(1.5)));

    //相机参数
    point3 lookfrom(3, 3, 2);
    point3 lookat(0, 0, -1);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = (lookfrom - lookat).length();
    auto aperture = 2.0;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
    */
    //场景生成
    auto world = random_scene();
    //相机参数
    point3 lookfrom(13, 2, 3);
    point3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;
    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {//遍历像素
            color pixel_color(0, 0, 0);//初始像素0
            for (int s = 0; s < samples_per_pixel; ++s) {//遍历附近采样像素累加pooling防止锯齿
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world,max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}
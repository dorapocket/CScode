#ifndef VEC3_H
#define VEC3_H
#include <cmath>
#include <iostream>

using std::sqrt;
/*
2020.5.19
vec3向量类 存储四组数据
*/
class vec3
{
public:
    //构造函数
    vec3() : e{ 0, 0, 0 } {}
    vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}
    //三维
    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }
    //重载运算符（矢量运算）
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    vec3& operator+=(const vec3& v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=(const double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(const double t)
    {
        return *this *= 1 / t;
    }
    //模长
    double length() const
    {
        return sqrt(length_squared());
    }
    double length_squared() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }
    inline static vec3 random() {//生成随机数（vec3）
        return vec3(random_double(), random_double(), random_double());
    }

    inline static vec3 random(double min, double max) {//范围内生成随机数（vec3）
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }
public:
    double e[3];
};
//别名 point和color都要这种数据类型
using point3 = vec3; // 三维坐标
using color = vec3;  // RGB颜色分量

inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}
//矢量运算
inline vec3 operator+(const vec3& u, const vec3& v)
{
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v)
{
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v)
{
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t)
{
    return t * v;
}

inline vec3 operator/(vec3 v, double t)
{
    return (1 / t) * v;
}
//点积
inline double dot(const vec3& u, const vec3& v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}
//叉积
inline vec3 cross(const vec3& u, const vec3& v)
{
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}
//归一化
inline vec3 unit_vector(vec3 v)
{
    return v / v.length();
}

//在单位圆内生成随机点（用于漫反射端点等）
vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1, 1);
        if (p.length_squared() >= 1) continue;//模长大于1就不是，重新生成
        return p;
    }
}
//产生球面单位向量
vec3 random_unit_vector() {
    auto a = random_double(0, 2 * pi);
    auto z = random_double(-1, 1);
    auto r = sqrt(1 - z * z);
    return vec3(r * cos(a), r * sin(a), z);
}

vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) //和法线同方向半圆
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}
/*
反射计算函数 v为入射光，n为面法向
令b为法线方向的向量
反射光方向=v+2b，n为单位向量，v不是，所以b的长度应该是v与n点积
在这里我们令v为穿过目标点到达反射点后的区域内的向量，故加负号
v-2v·n*n
*/
vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v, n) * n;
}
//折射计算函数，详见文档
vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = dot(-uv, n);
    vec3 r_out_parallel = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_perp = -sqrt(1.0 - r_out_parallel.length_squared()) * n;
    return r_out_parallel + r_out_perp;
}
//生成单位视口内的随机光以模拟景深
vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

#endif


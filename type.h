#ifndef __TYPE_H__
#define __TYPE_H__

#include<array>
#include<cmath>

#define M_PI 3.14159265358979323846

using vec2f = std::array<float, 2>;
using vec3f = std::array<float, 3>;
using vec4f = std::array<float, 4>;

using mat3f = std::array<std::array<float, 3>, 3>;
using mat4f = std::array<std::array<float, 4>, 4>;


float norm(const vec3f &v);
vec3f normalized(const vec3f &v);
vec3f crossProduct(const vec3f &a, const vec3f &b);
float dotProduct(const vec3f &a, const vec3f &b);
vec3f cwiseProduct(const vec3f &a, const vec3f &b);

vec2f vecPlus(const vec2f &a, const vec2f &b);
vec3f vecPlus(const vec3f &a, const vec3f &b);
vec3f vecMinus(const vec3f &a, const vec3f &b);
vec2f vec_multi_num(const vec2f &v, float n);
vec3f vec_multi_num(const vec3f &v, float n);
vec4f vec_multi_num(const vec4f &v, float n);
vec2f vec_divi_num(const vec2f &v, float n);
vec3f vec_divi_num(const vec3f &v, float n);
vec4f vec_divi_num(const vec4f &v, float n);
vec4f mat4f_multi_vec4f(const mat4f& m, const vec4f& v);
mat4f mat4f_multi_mat4f(const mat4f& m1, const mat4f& m2);

mat3f transpose(const mat3f &m);
mat4f transpose(const mat4f &m);
mat3f adjoint(const mat3f &m);
float determinant(const mat3f &m);
mat3f inverse(const mat3f &m);
float minor(const mat4f &m, int r, int c);
float cofactor(const mat4f &m, int r, int c);
mat4f adjoint(const mat4f &m);
mat4f inverse(const mat4f &m);

// ½Ç¶È×ª»¡¶È
float angle2radians(const float a);

#endif // !__TYPE_H__


#ifndef __TYPE_H__
#define __TYPE_H__

#include<array>

#define M_PI 3.14159265358979323846

using vec2f = std::array<float, 2>;
using vec3f = std::array<float, 3>;
using vec4f = std::array<float, 4>;

using mat3f = std::array<std::array<float, 3>, 3>;
using mat4f = std::array<std::array<float, 4>, 4>;



vec3f crossProduct(const vec3f &a, const vec3f &b)
{
	return vec3f{ a[1] * b[2] - a[2] * b[1],a[2] * b[0] - a[0] * b[2],a[0] * b[1] - a[1] * b[0] };
}

float dotProduct(const vec3f &a, const vec3f &b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

vec4f mat4f_multi_vec4f(const mat4f& m,const vec4f& v)
{
	float tmp[4];
	for (int i = 0; i < 4; ++i) {
		tmp[i] = m[i][0] * v[0] + m[i][1] * v[1] + m[i][2] * v[2] + m[i][3] * v[3];
	}
	return vec4f{ tmp[0],tmp[1],tmp[2],tmp[3] };
}

mat4f mat4f_multi_mat4f(const mat4f& m1, const mat4f& m2)
{
	mat4f res;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			res[i][j] = m1[i][0] * m2[0][j] + m1[i][1] * m2[1][j] + m1[i][2] * m2[2][j] + m1[i][3] * m2[3][j];
		}
	}
	return res;
}

#endif // !__TYPE_H__


#include "type.h"

float norm(const vec3f &v)
{
	float tmp = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
	return std::sqrt(tmp);
}

vec3f normalized(const vec3f &v)
{
	float tmp = norm(v);
	return { v[0] / tmp,v[1] / tmp,v[2] / tmp };
}

vec3f crossProduct(const vec3f &a, const vec3f &b)
{
	return { a[1] * b[2] - a[2] * b[1],a[2] * b[0] - a[0] * b[2],a[0] * b[1] - a[1] * b[0] };
}

float dotProduct(const vec3f &a, const vec3f &b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

vec3f cwiseProduct(const vec3f &a, const vec3f &b)
{
	return { a[0] * b[0],a[1] * b[1],a[2] * b[2] };
}

vec2f vecPlus(const vec2f &a, const vec2f &b)
{
	return { a[0] + b[0],a[1] + b[1] };
}

vec3f vecPlus(const vec3f &a, const vec3f &b)
{
	return { a[0] + b[0],a[1] + b[1],a[2] + b[2] };
}

vec3f vecMinus(const vec3f &a, const vec3f &b)
{
	return { a[0] - b[0],a[1] - b[1],a[2] - b[2] };
}

vec2f vec_multi_num(const vec2f &v, float n)
{
	return { v[0] * n,v[1] * n };
}

vec3f vec_multi_num(const vec3f &v, float n)
{
	return { v[0] * n,v[1] * n,v[2] * n };
}

vec4f vec_multi_num(const vec4f &v, float n)
{
	return { v[0] * n,v[1] * n,v[2] * n,v[3] * n };
}

vec2f vec_divi_num(const vec2f &v, float n)
{
	return { v[0] / n,v[1] / n };
}

vec3f vec_divi_num(const vec3f &v, float n)
{
	return { v[0] / n,v[1] / n,v[2] / n };
}

vec4f vec_divi_num(const vec4f &v, float n)
{
	return { v[0] / n,v[1] / n,v[2] / n,v[3] / n };
}

vec4f mat4f_multi_vec4f(const mat4f& m, const vec4f& v)
{
	float tmp[4];
	for (int i = 0; i < 4; ++i) {
		tmp[i] = m[i][0] * v[0] + m[i][1] * v[1] + m[i][2] * v[2] + m[i][3] * v[3];
	}
	return { tmp[0],tmp[1],tmp[2],tmp[3] };
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

mat3f transpose(const mat3f &m)
{
	mat3f res;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			res[i][j] = m[j][i];
		}
	}
	return res;
}

mat4f transpose(const mat4f &m)
{
	mat4f res;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			res[i][j] = m[j][i];
		}
	}
	return res;
}

mat3f adjoint(const mat3f &m)
{
	mat3f adjoint;
	adjoint[0][0] = +(m[1][1] * m[2][2] - m[2][1] * m[1][2]);
	adjoint[0][1] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]);
	adjoint[0][2] = +(m[1][0] * m[2][1] - m[2][0] * m[1][1]);
	adjoint[1][0] = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]);
	adjoint[1][1] = +(m[0][0] * m[2][2] - m[2][0] * m[0][2]);
	adjoint[1][2] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]);
	adjoint[2][0] = +(m[0][1] * m[1][2] - m[1][1] * m[0][2]);
	adjoint[2][1] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]);
	adjoint[2][2] = +(m[0][0] * m[1][1] - m[1][0] * m[0][1]);
	return adjoint;
}

float determinant(const mat3f &m)
{
	float a = +m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]);
	float b = -m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]);
	float c = +m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
	return a + b + c;
}

mat3f inverse(const mat3f &m)
{
	int i, j;
	float dm, invd;
	mat3f adj, inverseTranspose;

	adj = adjoint(m);
	dm = determinant(m);
	invd = 1 / dm;

	for (i = 0; i < 3; ++i)
		for (j = 0; j < 3; ++j)
			inverseTranspose[i][j] = adj[i][j] * invd;

	return transpose(inverseTranspose);
}

float minor(const mat4f &m, int r, int c)
{
	mat3f cut_down;
	int i, j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			int row = i < r ? i : i + 1;
			int col = j < c ? j : j + 1;
			cut_down[i][j] = m[row][col];
		}
	}
	return determinant(cut_down);
}

float cofactor(const mat4f &m, int r, int c)
{
	float sign = (r + c) % 2 == 0 ? 1.0f : -1.0f;
	float mi = minor(m, r, c);
	return sign * mi;
}

mat4f adjoint(const mat4f &m)
{
	mat4f adjoint;
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			adjoint[i][j] = cofactor(m, i, j);
	return adjoint;
}

mat4f inverse(const mat4f &m)
{
	int i, j;
	float dm, invd;
	mat4f adj, inverseTranspose;

	adj = adjoint(m);
	dm = 0;
	for (i = 0; i < 4; i++)
	{
		dm += m[0][i] * adj[0][i];
	}
	invd = 1 / dm;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			inverseTranspose[i][j] = adj[i][j] * invd;

	return inverseTranspose;
}

float angle2radians(const float a)
{
	return a / 180.0 * M_PI;
}
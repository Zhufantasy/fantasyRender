#ifndef __TMP_H__
#define __TMP_H__

#include"tgaimage.h"
#include"mesh.h"
#include<array>
#include<algorithm>

vec3f calculateBarycentricCoordinates(const Triangle *t, const vec2f &p);

void draw_line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);
void draw_triangle(const Triangle &t, TGAImage &image, TGAColor color);
void draw_triangle_filled(const Triangle &t, TGAImage &image, TGAColor color);

#endif //__TMP_H__
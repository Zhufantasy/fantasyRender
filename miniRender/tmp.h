#ifndef __TMP_H__
#define __TMP_H__

#include"tgaimage.h"
#include<array>
#include<algorithm>

void draw_line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);

void draw_triangle(std::array<int, 2> p1, std::array<int, 2> p2, std::array<int, 2> p3, TGAImage &image, TGAColor color);

void draw_triangle_filled(std::array<int, 2> p1, std::array<int, 2> p2, std::array<int, 2> p3, TGAImage &image, TGAColor color);

bool insideTriangle(std::array<std::array<int, 2>, 3>);

#endif //__TMP_H__
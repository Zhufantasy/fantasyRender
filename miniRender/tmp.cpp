#include"tmp.h"

vec3f calculateBarycentricCoordinates(const Triangle *t, const vec2f &p)
{
	vec3f p1 = t->verticesP[0]->posi, p2 = t->verticesP[1]->posi, p3 = t->verticesP[2]->posi;
	float tmp1 = -(p[0] - p3[0])*(p1[1] - p3[1]) + (p[1] - p3[1])*(p1[0] - p3[0]);
	float tmp2 = -(p2[0] - p3[0])*(p1[1] - p3[1]) + (p1[1] - p2[1])*(p1[0] - p3[0]);
	float tmp3 = -(p[0] - p2[0])*(p3[1] - p2[1]) + (p[1] - p2[1])*(p3[0] - p2[0]);
	float tmp4 = -(p1[0] - p2[0])*(p3[1] - p2[1]) + (p1[1] - p2[1])*(p3[0] - p2[0]);
	return vec3f{ tmp1 / tmp2,tmp3 / tmp4,1 - tmp1 / tmp2 - tmp3 / tmp4 };
}

void draw_line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color)
{
	bool isSwap = false;
	if (abs(x1 - x0) < abs(y1 - y0)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		isSwap = true;
	}

	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	float slope = (y1 - y0) / (float)(x1 - x0);
	int count = x1 - x0;
	float y = y0;
	int x = x0;
	for (int i = 0; i <= count; ++i) {
		if (isSwap) {
			image.set((int)y, x, color);
		}
		else {
			image.set(x, (int)y, color);
		}
		x += 1;
		y += slope;
	}
}


void draw_triangle(const Triangle &t, TGAImage &image, TGAColor color)
{
	draw_line(t.verticesP[0]->posi[0], t.verticesP[0]->posi[1], t.verticesP[1]->posi[0], t.verticesP[1]->posi[1], image, color);
	draw_line(t.verticesP[1]->posi[0], t.verticesP[1]->posi[1], t.verticesP[2]->posi[0], t.verticesP[2]->posi[1], image, color);
	draw_line(t.verticesP[2]->posi[0], t.verticesP[2]->posi[1], t.verticesP[0]->posi[0], t.verticesP[0]->posi[1], image, color);
}

void draw_triangle_filled(const Triangle &t, TGAImage &image, TGAColor color)
{
	int maxX = std::max(t.verticesP[0]->posi[0], std::max(t.verticesP[1]->posi[0], t.verticesP[2]->posi[0]));
	int maxY = std::max(t.verticesP[0]->posi[1], std::max(t.verticesP[1]->posi[1], t.verticesP[2]->posi[1]));
	int minX = std::min(t.verticesP[0]->posi[0], std::min(t.verticesP[1]->posi[0], t.verticesP[2]->posi[0]));
	int minY = std::min(t.verticesP[0]->posi[1], std::min(t.verticesP[1]->posi[1], t.verticesP[2]->posi[1]));

	for (int x = minX; x <= maxX; ++x) {
		for (int y = minY; y <= maxY; ++y) {
			if (!t.insideTriangle(vec2f{ x, y })) {
				continue;
			}
			image.set(x, y, color);
		}
	}
}

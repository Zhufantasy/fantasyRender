#include"tmp.h"

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
	draw_line(t.vertices[0][0], t.vertices[0][1], t.vertices[1][0], t.vertices[1][1], image, color);
	draw_line(t.vertices[1][0], t.vertices[1][1], t.vertices[2][0], t.vertices[2][1], image, color);
	draw_line(t.vertices[2][0], t.vertices[2][1], t.vertices[0][0], t.vertices[0][1], image, color);
}

void draw_triangle_filled(const Triangle &t, TGAImage &image, TGAColor color)
{
	int maxX = std::max(t.vertices[0][0], std::max(t.vertices[1][0], t.vertices[2][0]));
	int maxY = std::max(t.vertices[0][1], std::max(t.vertices[1][1], t.vertices[2][1]));
	int minX = std::min(t.vertices[0][0], std::min(t.vertices[1][0], t.vertices[2][0]));
	int minY = std::min(t.vertices[0][1], std::min(t.vertices[1][1], t.vertices[2][1]));

	for (int x = minX; x <= maxX; ++x) {
		for (int y = minY; y <= maxY; ++y) {
			if (!t.insideTriangle(std::array<int, 2>{ x, y })) {
				continue;
			}
			image.set(x, y, color);
		}
	}
}

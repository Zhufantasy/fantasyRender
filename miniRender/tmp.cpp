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
	/*for (int x = x0; x <= x1; ++x) {
		float diff = (x - x0) / (float)(x1 - x0);
		int y = y0 + (y1 - y0)*diff;
		if (isSwap) {
			image.set(y, x, color);
		}
		else {
			image.set(x, y, color);
		}
	}*/
}


void draw_triangle(std::array<int, 2> p1, std::array<int, 2> p2, std::array<int, 2> p3, TGAImage &image, TGAColor color)
{
	draw_line(p1[0], p1[1], p2[0], p2[1], image, color);
	draw_line(p2[0], p2[1], p3[0], p3[1], image, color);
	draw_line(p3[0], p3[1], p1[0], p1[1], image, color);
}

bool insideTriangle(std::array<std::array<int,2>,3>)
{

}

void draw_triangle_filled(std::array<int, 2> p1, std::array<int, 2> p2, std::array<int, 2> p3, TGAImage &image, TGAColor color)
{
	int maxX = std::max(p1[0], std::max(p2[0], p3[0]));
	int maxY = std::max(p1[1], std::max(p2[1], p3[1]));
	int minX = std::min(p1[0], std::min(p2[0], p3[0]));
	int minY = std::min(p1[1], std::min(p2[1], p3[1]));
}

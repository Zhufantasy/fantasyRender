#include "tgaimage.h"
#include "tmp.h"

int main(int argc, char** argv) {
	const TGAColor white = TGAColor(255, 255, 255, 255);
	const TGAColor red = TGAColor(255, 0, 0, 255);
	TGAImage image(50, 30, TGAImage::RGB);

	std::array<int, 2> p1{ 2,3 };
	std::array<int, 2> p2{ 40,9 };
	std::array<int, 2> p3{ 21,25 };
	draw_triangle(p1, p2, p3, image, red);

	image.write_tga_file("output.tga");
	return 0;
}

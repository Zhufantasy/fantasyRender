#include "tgaimage.h"
#include "tmp.h"

int main(int argc, char** argv) {
	const TGAColor white = TGAColor(255, 255, 255, 255);
	const TGAColor red = TGAColor(255, 0, 0, 255);
	TGAImage image(50, 30, TGAImage::RGB);

	std::array<std::array<int, 3>, 3> points;
	points[0] = std::array<int, 3>{2, 3, 0};
	points[1] = std::array<int, 3>{40, 9, 0};
	points[2] = std::array<int, 3>{21, 25, 0};
	Triangle t{points};


	draw_triangle_filled(t, image, red);

	image.write_tga_file("output.tga");
	return 0;
}

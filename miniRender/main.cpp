#include "tgaimage.h"
#include "tmp.h"
#include "OBJ_Loader.h"
#include "type.h"
#include<string>
#include<vector>
#include<array>

int main(int argc, char** argv) {
	const TGAColor white = TGAColor(255, 255, 255, 255);
	const TGAColor red = TGAColor(255, 0, 0, 255);
	TGAImage image(500, 300, TGAImage::RGB);

	std::string objModelPath = "./models/boggie/head.obj";
	objl::Loader loader;
	bool loadout = loader.LoadFile(objModelPath);

	std::vector<Triangle*> triangles;

	for (auto mesh : loader.LoadedMeshes) {
		for (int i = 0; i < mesh.Vertices.size(); i += 3) {
			Triangle* t = new Triangle();
			for (int j = 0; j < 3; ++j) {
				t->vertices[j][0] = (mesh.Vertices[i + j].Position.X + 1) * 500 / 2;
				t->vertices[j][1] = (mesh.Vertices[i + j].Position.Y + 1) * 300 / 2;
				t->vertices[j][2] = mesh.Vertices[i + j].Position.Z;
				t->normal[j][0] = mesh.Vertices[i + j].Normal.X;
				t->normal[j][1] = mesh.Vertices[i + j].Normal.Y;
				t->normal[j][2] = mesh.Vertices[i + j].Normal.Z;
				t->texCoords[j][0] = mesh.Vertices[i + j].TextureCoordinate.X;
				t->texCoords[j][1] = mesh.Vertices[i + j].TextureCoordinate.Y;
			}
			triangles.push_back(t);
		}
	}

	for (auto t : triangles) {
		draw_triangle_filled(*t, image, red);
	}

	image.write_tga_file("output.tga");
	return 0;

}

#include "OBJ_Loader.h"
#include "type.h"
#include "scene.h"
#include "rasterization.h"
#include "window.h"
#include<string>
#include<vector>
#include<array>

int main(int argc, char** argv) {
	//准备各种数据结构和数据
	Camera camera;
	Scene scene;
	scene.setCamera(&camera);

	std::string objModelPath = "./models/cube/cube.obj";
	objl::Loader loader;
	bool loadout = loader.LoadFile(objModelPath);

	for (auto mesh : loader.LoadedMeshes) {
		Mesh *tmpMesh = new Mesh();
		for (int i = 0; i < mesh.Vertices.size(); i += 3) {
			Triangle* t = new Triangle();
			for (int j = 0; j < 3; ++j) {
				t->vertices[j].posi[0] = mesh.Vertices[i + j].Position.X;
				t->vertices[j].posi[1] = mesh.Vertices[i + j].Position.Y;
				t->vertices[j].posi[2] = mesh.Vertices[i + j].Position.Z;
				//t->normal[j][0] = mesh.Vertices[i + j].Normal.X;
				//t->normal[j][1] = mesh.Vertices[i + j].Normal.Y;
				//t->normal[j][2] = mesh.Vertices[i + j].Normal.Z;
				//t->texCoords[j][0] = mesh.Vertices[i + j].TextureCoordinate.X;
				//t->texCoords[j][1] = mesh.Vertices[i + j].TextureCoordinate.Y;
			}
			tmpMesh->trianglesP.push_back(t);
		}
		scene.add(tmpMesh);
	}

	Rasterization rasterization(1000,500);
	rasterization.setScene(&scene);

	//创建窗口
	Window window(&rasterization);
	window.windowInit();

	//渲染循环
	while (!window.isClose) {
		window.handleKeyboardAndMouseEvent();
		rasterization.scene->camera->updateView();
		rasterization.scene->camera->updateProjection();

		rasterization.clearFrameBuffer();
		rasterization.clearDepthBuffer();

		rasterization.render();
		window.windowDraw();
		window.handleMsg();
	}

	return 0;
}

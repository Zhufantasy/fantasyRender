#include "OBJ_Loader.h"
#include "type.h"
#include "scene.h"
#include "rasterization.h"
#include "window.h"
#include "texture.h"
#include "shader.h"
#include<cstring>
#include<vector>
#include<array>



std::string objModelPath = "../models/diablo3_pose/diablo3_pose.obj";
std::string texturePath = "../models/diablo3_pose/diablo3_pose_diffuse.tga";



int main(int argc, char** argv) {
	//׼���������ݽṹ������
	Texture texture(texturePath);

	Camera camera;
	Scene scene;
	scene.setTexture(&texture);
	scene.setCamera(&camera);

	Light light1{ {20,20,20},{500,500,500} };
	Light light2{ {-20,20,0},{500,500,500} };
	scene.add(&light1);
	scene.add(&light2);

	objl::Loader loader;
	bool loadout = loader.LoadFile(objModelPath);

	for (auto mesh : loader.LoadedMeshes) {
		Mesh *tmpMesh = new Mesh();
		for (int i = 0; i < mesh.Vertices.size(); i += 3) {
			Triangle* t = new Triangle();
			for (int j = 0; j < 3; ++j) {
				t->vertices[j].posi[0] = mesh.Vertices[i + j].Position.X;
				t->vertices[j].posi[1] = mesh.Vertices[i + j].Position.Y;
				t->vertices[j].posi[2] =  mesh.Vertices[i + j].Position.Z;
				t->vertices[j].normal[0] = mesh.Vertices[i + j].Normal.X;
				t->vertices[j].normal[1] = mesh.Vertices[i + j].Normal.Y;
				t->vertices[j].normal[2] = mesh.Vertices[i + j].Normal.Z;
				t->vertices[j].texCoord[0] = mesh.Vertices[i + j].TextureCoordinate.X;
				t->vertices[j].texCoord[1] = mesh.Vertices[i + j].TextureCoordinate.Y;
			}
			tmpMesh->trianglesP.push_back(t);
		}
		scene.add(tmpMesh);
	}

	Rasterization rasterization(1000,800);
	rasterization.setScene(&scene);

	ShaderProgram sp;
	sp.vertexShader = noChange;
	sp.fragmentShader = blinnPhong;
	rasterization.setShaderProgram(&sp);

	//��������
	RenderWindow renderWindow(&rasterization);
	renderWindow.windowInit();

	//��Ⱦѭ��
	while (!renderWindow.isClose) {
		renderWindow.handleKeyboardAndMouseEvent();
		rasterization.scene->camera->updateView();
		rasterization.scene->camera->updateProjection();

		rasterization.clearFrameBuffer();
		rasterization.clearDepthBuffer();

		rasterization.render();
		renderWindow.windowDraw();
		renderWindow.handleMsg();
	}

	return 0;
}

#include"rasterization.h"
#include"type.h"
#include<limits>

Rasterization::Rasterization(int width, int height)
{
	frameBuffer.resize(width*height);
	depthBuffer.resize(width*height, std::numeric_limits<float>::max());
}

void Rasterization::setScene(Scene* scene)
{
	this->scene = scene;
}

int Rasterization::getIndex(int w, int h)
{

}

bool Rasterization::render()
{
	for (auto mesh : scene->meshs) {
		for (auto triangle : mesh->trianglesP) {
			vec3f point[3] = { triangle->verticesP[0]->posi, triangle->verticesP[1]->posi, triangle->verticesP[2]->posi };
			//MVP±‰ªª
			for (auto& p : point) {
				vec4f pAfterModel = mat4f_multi_vec4f(mesh->model, vec4f{ p[0],p[1],p[2],1 });
				vec4f pAfterView = mat4f_multi_vec4f(scene->camera->view, pAfterModel);
				vec4f pAfterProjection = mat4f_multi_vec4f(scene->camera->projection, pAfterView);
				p = { pAfterProjection[0],pAfterProjection[1],pAfterProjection[2] };
			}
			// ”Õº±‰ªª










		}
	}
}
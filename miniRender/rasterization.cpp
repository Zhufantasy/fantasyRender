#include"rasterization.h"
#include"type.h"
#include<limits>

Rasterization::Rasterization(int width, int height)
{
	frameBuffer.resize(width*height);
	depthBuffer.resize(width*height, std::numeric_limits<float>::max());
	this->width = width;
	this->height = height;
}

void Rasterization::setScene(Scene* scene)
{
	this->scene = scene;
}

int Rasterization::getIndex(int r, int c)
{
	return r * width + c;
}

bool Rasterization::render()
{
	for (auto mesh : scene->meshs) {
		for (auto triangle : mesh->trianglesP) {
			Triangle newTri = *triangle;
			mat4f screen = {
							width*0.5,0,0,width*0.5,
							0,height*0.5,0,height*0.5,
							0,0,1,0,
							0,0,0,1
			};
			//MVP变换
			for (auto p : newTri.vertices) {
				vec4f pAfterModel = mat4f_multi_vec4f(mesh->model, vec4f{ p.posi[0],p.posi[1],p.posi[2],1 });
				vec4f pAfterView = mat4f_multi_vec4f(scene->camera->view, pAfterModel);
				vec4f pAfterProjection = mat4f_multi_vec4f(scene->camera->projection, pAfterView);
				p.posi = { pAfterProjection[0],pAfterProjection[1],pAfterProjection[2] };
			}
			//视图变换
			for (auto p : newTri.vertices) {
				vec4f pAfterScreen = mat4f_multi_vec4f(screen, vec4f{ p.posi[0],p.posi[1],p.posi[2],1 });
			}

			mat4f screenAndProjection = mat4f_multi_mat4f(screen, scene->camera->projection);
			drawTriangleFilled(newTri, screenAndProjection);
		}
	}

	return true;
}

void Rasterization::drawTriangleFilled(const Triangle &t, const mat4f &screenAndProjection)
{
	int maxX = std::max(t.vertices[0].posi[0], std::max(t.vertices[1].posi[0], t.vertices[2].posi[0]));
	int maxY = std::max(t.vertices[0].posi[1], std::max(t.vertices[1].posi[1], t.vertices[2].posi[1]));
	int minX = std::min(t.vertices[0].posi[0], std::min(t.vertices[1].posi[0], t.vertices[2].posi[0]));
	int minY = std::min(t.vertices[0].posi[1], std::min(t.vertices[1].posi[1], t.vertices[2].posi[1]));

	mat4f inverseSAP = inverse(screenAndProjection);
	Triangle triView;
	for (int i = 0; i < 3; ++i) {
		vec4f tmp = mat4f_multi_vec4f(inverseSAP, vec4f{ t.vertices[i].posi[0],t.vertices[i].posi[1],t.vertices[i].posi[2],1 });
		triView.vertices[i].posi = { tmp[0],tmp[1],tmp[2] };
	}

	for (int x = minX; x <= maxX; ++x) {
		for (int y = minY; y <= maxY; ++y) {
			if (!t.insideTriangle(vec2f{ x+0.5f, y+0.5f })) {
				continue;
			}

			int index = getIndex(x, y);

			//插值计算深度
			vec3f baryCoord = t.calculateBarycentricCoordinates(vec2f{ x + 0.5f, y + 0.5f });
			float depthView = 1.0 / (baryCoord[0] / triView.vertices[0].posi[2] + baryCoord[1] / triView.vertices[1].posi[2] + baryCoord[2] / triView.vertices[2].posi[2]);
			float depthScreen = baryCoord[0] * t.vertices[0].posi[2] / triView.vertices[0].posi[2] + 
								baryCoord[1] * t.vertices[1].posi[2] / triView.vertices[0].posi[2] + 
								baryCoord[2] * t.vertices[2].posi[2] / triView.vertices[0].posi[2];
			depthScreen *= depthView;
			if (depthScreen <= depthBuffer[index]) {
				continue;
			}

			depthBuffer[index] = depthScreen;
			frameBuffer[index] = { 0,255,0 };
		}
	}

}
#include"rasterization.h"
#include"type.h"
#include<limits>

Rasterization::Rasterization(int width, int height)
{
	frameBuffer.resize(width*height);
	depthBuffer.resize(width*height, -std::numeric_limits<float>::max());
	this->width = width;
	this->height = height;
}

void Rasterization::setScene(Scene* scene)
{
	this->scene = scene;
}

void Rasterization::setShaderProgram(ShaderProgram *s)
{
	this->shader = s;
}

int Rasterization::getIndex(int r, int c)
{
	return c * width + r;
}

void Rasterization::clearFrameBuffer()
{
	vec3f tmp = { 100,100,100 };
	for (vec3f &a : frameBuffer) {
		a = tmp;
	}
}

void Rasterization::clearDepthBuffer()
{
	for (float &a : depthBuffer) {
		a = -std::numeric_limits<float>::max();
	}
}

bool Rasterization::render()
{
	mat4f screen = {
			width*0.5,0,0,width*0.5,
			0,height*0.5,0,height*0.5,
			0,0,1,0,
			0,0,0,1
	};

	for (auto mesh : scene->meshs) {
		for (auto triangle : mesh->trianglesP) {
			// 做vertex shader
			for (auto &v : triangle->vertices) {
				v.posi = this->shader->vertexShader(v.posi);
			}

			Triangle triView = *triangle;
			for (auto &p : triView.vertices) {
				//MV变换
				vec4f pAfterModel = mat4f_multi_vec4f(mesh->model, vec4f{ p.posi[0],p.posi[1],p.posi[2],1 });
				vec4f pAfterView = mat4f_multi_vec4f(scene->camera->view, pAfterModel);
				p.posi = { pAfterView[0],pAfterView[1],pAfterView[2] };

				//法向量变换到view空间
				mat4f m = transpose(inverse(mat4f_multi_mat4f(scene->camera->view, mesh->model)));
				vec4f nAfterViewAndModel = mat4f_multi_vec4f(m, vec4f{ p.normal[0],p.normal[1],p.normal[2],0 });
				p.normal = { nAfterViewAndModel[0],nAfterViewAndModel[1],nAfterViewAndModel[2] };
			}

			Triangle triScreen = triView;
			for (auto &p : triScreen.vertices) {
				//P变换
				vec4f pAfterProjection = mat4f_multi_vec4f(scene->camera->projection, vec4f{ p.posi[0],p.posi[1],p.posi[2],1 });
				pAfterProjection = vec_divi_num(pAfterProjection, pAfterProjection[3]);
				p.posi = { pAfterProjection[0],pAfterProjection[1],pAfterProjection[2] };
			}

			for (auto &p : triScreen.vertices) {
				//屏幕变换
				vec4f pAfterScreen = mat4f_multi_vec4f(screen, vec4f{ p.posi[0],p.posi[1],p.posi[2],1 });
				p.posi = { pAfterScreen[0],pAfterScreen[1],pAfterScreen[2] };
			}

			drawTriangleFilled(triScreen, triView);
		}
	}

	return true;
}

void Rasterization::drawTriangleFilled(const Triangle &t, const Triangle &triView)
{
	int maxX = std::max(t.vertices[0].posi[0], std::max(t.vertices[1].posi[0], t.vertices[2].posi[0]));
	int maxY = std::max(t.vertices[0].posi[1], std::max(t.vertices[1].posi[1], t.vertices[2].posi[1]));
	int minX = std::min(t.vertices[0].posi[0], std::min(t.vertices[1].posi[0], t.vertices[2].posi[0]));
	int minY = std::min(t.vertices[0].posi[1], std::min(t.vertices[1].posi[1], t.vertices[2].posi[1]));
	if (maxX >= width) maxX = width - 1;
	if (maxY >= height) maxY = height - 1;
	if (minX < 0) minX = 0;
	if (minY < 0) minY = 0;

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
								baryCoord[1] * t.vertices[1].posi[2] / triView.vertices[1].posi[2] + 
								baryCoord[2] * t.vertices[2].posi[2] / triView.vertices[2].posi[2];
			depthScreen *= depthView;
			if (depthScreen < depthBuffer[index] || depthScreen > 1 || depthScreen < -1) {
				continue;
			}

			//插值计算属性
			vec3f normalView = vecPlus(vecPlus(vec_divi_num(vec_multi_num(triView.vertices[0].normal, baryCoord[0]), triView.vertices[0].posi[2]),
											   vec_divi_num(vec_multi_num(triView.vertices[1].normal, baryCoord[1]), triView.vertices[1].posi[2])),
											   vec_divi_num(vec_multi_num(triView.vertices[2].normal, baryCoord[2]), triView.vertices[2].posi[2]));
			normalView = vec_multi_num(normalView, depthView);
			vec2f texCoordView = vecPlus(vecPlus(vec_divi_num(vec_multi_num(triView.vertices[0].texCoord, baryCoord[0]), triView.vertices[0].posi[2]),
											     vec_divi_num(vec_multi_num(triView.vertices[1].texCoord, baryCoord[1]), triView.vertices[1].posi[2])),
												 vec_divi_num(vec_multi_num(triView.vertices[2].texCoord, baryCoord[2]), triView.vertices[2].posi[2]));
			texCoordView = vec_multi_num(texCoordView, depthView);
			vec3f posiView = vecPlus(vecPlus(vec_divi_num(vec_multi_num(triView.vertices[0].posi, baryCoord[0]), triView.vertices[0].posi[2]),
				                             vec_divi_num(vec_multi_num(triView.vertices[1].posi, baryCoord[1]), triView.vertices[1].posi[2])),
				                             vec_divi_num(vec_multi_num(triView.vertices[2].posi, baryCoord[2]), triView.vertices[2].posi[2]));
			posiView = vec_multi_num(posiView, depthView);

			depthBuffer[index] = depthScreen;
			frameBuffer[index] = this->shader->fragmentShader(scene, posiView, { -1,-1,-1 }, normalView, texCoordView);
		}
	}
}
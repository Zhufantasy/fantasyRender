#pragma once
#ifndef __RASTERIZATION_H__
#define __RASTERIZATION_H__

#include "type.h"
#include "scene.h"
#include "shader.h"
#include<vector>

class Rasterization {
public:
	std::vector<vec3f> frameBuffer;
	std::vector<float> depthBuffer;
	Scene* scene;
	ShaderProgram *shader;
	int width;
	int height;

	Rasterization(int width, int height);
	void setScene(Scene* scene);
	void setShaderProgram(ShaderProgram *s);
	int getIndex(int row, int column);
	void clearFrameBuffer();
	void clearDepthBuffer();
	bool render();

private:
	void drawTriangleFilled(const Triangle &t,const mat4f &screenAndProjection);
};



#endif // !__RASTERIZATION_H__


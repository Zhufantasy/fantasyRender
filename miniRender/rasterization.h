#pragma once
#ifndef __RASTERIZATION_H__
#define __RASTERIZATION_H__

#include "type.h"
#include "scene.h"
#include<vector>

class Rasterization {
public:
	std::vector<vec3f> frameBuffer;
	std::vector<float> depthBuffer;
	Scene* scene;
	int width;
	int height;

	Rasterization(int width, int height);
	void setScene(Scene* scene);
	int getIndex(int row, int column);
	bool render();

private:

};



#endif // !__RASTERIZATION_H__


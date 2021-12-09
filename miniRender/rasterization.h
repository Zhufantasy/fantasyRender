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

	Rasterization(int width, int height);
	void setScene(Scene* scene);
	int getIndex(int w, int h);
	bool render();

private:

};



#endif // !__RASTERIZATION_H__


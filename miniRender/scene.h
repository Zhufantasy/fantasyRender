#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

#include "light.h"
#include "camera.h"
#include "mesh.h"
#include <vector>

class Scene {
public:
	std::vector<Light*> lights;
	std::vector<Mesh*> meshs;
	Camera* camera;

private:
	void add(Light *l);
	void add(Mesh *m);
	void setCamera(Camera *cam);

};

#endif // __SCENE_H__

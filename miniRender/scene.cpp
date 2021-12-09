#include "scene.h"

void Scene::add(Light *l)
{
	lights.push_back(l);
}

void Scene::add(Mesh *m)
{
	meshs.push_back(m);
}

void Scene::setCamera(Camera *cam)
{
	this->camera = cam;
}
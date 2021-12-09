#pragma once

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "type.h"

class Camera {
public:
	vec3f posi;
	vec3f up;
	vec3f front;
	mat4f view;
	mat4f projection;
	float verticalAngle;
	float ratio;
	float zNear;
	float zFar;

	Camera();
	Camera(vec3f posi, vec3f up, vec3f front);
	void updateView();
	void updateProjection();
};


#endif // __CAMERA_H__

#include"camera.h"

Camera::Camera() :posi(vec3f{ 0,0,0 }), up(vec3f{ 0,1,0 }), front(vec3f{ 0,0,-1 }), verticalAngle(90), ratio(1), zNear(0.1), zFar(100), pitch(0), yaw(-90)
{
	this->view = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	float angle = verticalAngle / 180.0f * M_PI;
	mat4f m1 = {
		-zNear,0,0,0,
		0,-zNear,0,0,
		0,0,-zNear - zFar,-zNear * zFar,
		0,0,1,0
	};
	mat4f m2 = {
		1 / zNear / tan(angle / 2) / ratio,0,0,0,
		0,1 / zNear / tan(angle / 2),0,0,
		0,0,1 / (zFar - zNear),0.5*(zFar + zNear) / (zFar - zNear),
		0,0,0,1
	};
	this->projection = mat4f_multi_mat4f(m2, m1);
};

Camera::Camera(vec3f p, vec3f u, vec3f f) :posi(p), up(normalized(u)), front(normalized(f)), verticalAngle(90), ratio(1), zNear(0.1), zFar(100), pitch(0), yaw(-90)
{
	//需不需要单位向量？
	vec3f frontMultiUp = normalized(crossProduct(front, up));
	mat4f Rview = {
		frontMultiUp[0],frontMultiUp[1],frontMultiUp[2],0,
		up[0],up[1],up[2],0,
		-front[0],-front[1],-front[2],0,
		0,0,0,1
	};
	mat4f Tview = {
		1,0,0,-posi[0],
		0,1,0,-posi[1],
		0,0,1,-posi[2],
		0,0,0,1
	};
	this->view = mat4f_multi_mat4f(Rview, Tview);

	float angle = verticalAngle / 180.0f * M_PI;
	mat4f m1 = {
		-zNear,0,0,0,
		0,-zNear,0,0,
		0,0,-zNear - zFar,-zNear * zFar,
		0,0,1,0
	};
	mat4f m2 = {
		1 / zNear / tan(angle / 2) / ratio,0,0,0,
		0,1 / zNear / tan(angle / 2),0,0,
		0,0,1 / (zFar - zNear),0.5*(zFar + zNear) / (zFar - zNear),
		0,0,0,1
	};
	this->projection = mat4f_multi_mat4f(m2, m1);
};

void Camera::updateView()
{
	vec3f frontMultiUp = normalized(crossProduct(front, up));
	mat4f Rview = {
		frontMultiUp[0],frontMultiUp[1],frontMultiUp[2],0,
		up[0],up[1],up[2],0,
		-front[0],-front[1],-front[2],0,
		0,0,0,1
	};
	mat4f Tview = {
		1,0,0,-posi[0],
		0,1,0,-posi[1],
		0,0,1,-posi[2],
		0,0,0,1
	};
	this->view = mat4f_multi_mat4f(Rview, Tview);
}

void Camera::updateProjection()
{
	float angle = verticalAngle / 180.0f * M_PI;
	mat4f m1 = {
		-zNear,0,0,0,
		0,-zNear,0,0,
		0,0,- zNear - zFar,-zNear * zFar,
		0,0,1,0
	};
	mat4f m2 = {
		1 / zNear / tan(angle / 2) / ratio,0,0,0,
		0,1 / zNear / tan(angle / 2),0,0,
		0,0,1 / (zFar - zNear),0.5*(zFar + zNear) / (zFar - zNear),
		0,0,0,1
	};
	this->projection = mat4f_multi_mat4f(m2, m1);
}

void Camera::handlePitchAndYawChange()
{
	front[0] = cos(angle2radians(yaw))*cos(angle2radians(pitch));
	front[1] = sin(angle2radians(pitch));
	front[2] = sin(angle2radians(yaw))*cos(angle2radians(pitch));
	front = normalized(front);
	vec3f right = normalized(crossProduct(front, vec3f{ 0,1,0 }));
	up = normalized(crossProduct(right, front));
}

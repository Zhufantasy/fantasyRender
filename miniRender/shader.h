#pragma once
#ifndef __SHADER_H__
#define __SHADER_H__

#include "type.h"
#include "scene.h"

struct ShaderProgram {
	vec3f (*vertexShader)(vec3f &vertex);
	vec3f(*fragmentShader)(Scene *scene, const vec3f &viewPos, const vec3f &color, const vec3f &normal, const vec2f &texCoord);
};

//vertex shader
vec3f noChange(vec3f &vertex);

//fragment shader
vec3f blinnPhong(Scene *scene, const vec3f &viewPos, const vec3f &color, const vec3f &normal, const vec2f &texCoord);


#endif // !__SHADER_H__


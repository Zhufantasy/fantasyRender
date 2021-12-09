#pragma once
#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "type.h"

struct Light {
	vec3f position;
	vec3f intensity;
};

#endif // __LIGHT_H__

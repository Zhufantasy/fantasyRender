#pragma once
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "tgaimage.h"
#include "type.h"
#include<cstring>

class Texture {
public:
	TGAImage *image;

	Texture(const std::string &str);
	vec3f getColor(int u, int v); //输出的颜色顺序为RGB
	~Texture();
};



#endif // !__TEXTURE_H__

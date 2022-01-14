#include "texture.h"

Texture::Texture(const std::string &str)
{
	image = new TGAImage();
	image->read_tga_file(str);
	image->flip_vertically(); //��ͼ��ԭ����Ϊ���½�
}

vec3f Texture::getColor(int u, int v)
{
	int x = u * image->get_width();
	int y = v * image->get_height();
	TGAColor c = image->get(x, y); //TGAcolor˳��ΪBGRA
	return { c.bgra[2] * 255.0,c.bgra[1] * 255.0,c.bgra[0] * 255.0 };
}

Texture::~Texture()
{
	delete(image);
}
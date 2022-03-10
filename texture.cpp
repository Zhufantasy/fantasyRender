#include "texture.h"

Texture::Texture(const std::string &str)
{
	image = new TGAImage();
	image->read_tga_file(str);
	image->flip_vertically(); //��ͼ��ԭ����Ϊ���½�
}

vec3f Texture::getColor(float u, float v)
{
	int x = u * image->get_width();
	int y = v * image->get_height();
	TGAColor c = image->get(x, y); //TGAcolor˳��ΪBGRA
	return { (float)c.bgra[2],(float)c.bgra[1],(float)c.bgra[0] };
}

Texture::~Texture()
{
	delete(image);
}
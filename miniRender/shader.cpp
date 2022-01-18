#include "shader.h"

vec3f noChange(vec3f &vertex)
{
	return vertex;
}

vec3f blinnPhong(Scene *scene, const vec3f &viewPos, const vec3f &color, const vec3f &normal, const vec2f &texCoord)
{
	vec3f textureColor = scene->texture->getColor(texCoord[0], texCoord[1]);
	vec3f res = { 0,0,0 };

	vec3f ka = { 0.2, 0.2, 0.2 };
	vec3f kd = vec_divi_num(textureColor, 255.0);
	vec3f ks = { 0.7937, 0.7937, 0.7937 };

	for (auto light : scene->lights) {
		vec3f i = normalized(vecMinus(light->position, viewPos));
		vec3f n = normalized(normal);
		vec3f v = normalized(vecMinus(scene->camera->posi, viewPos));
		vec3f h = normalized(vecPlus(v, i));
		float r2 = dotProduct(vecMinus(light->position, viewPos), vecMinus(light->position, viewPos));
		float p = 150;

		vec3f diffuse = cwiseProduct(kd, light->intensity);
		diffuse = vec_divi_num(diffuse, r2);
		diffuse = vec_multi_num(diffuse, std::max(0.0f, dotProduct(n, i)));
		res = vecPlus(res, diffuse);

		vec3f specular = cwiseProduct(ks, light->intensity);
		specular = vec_divi_num(specular, r2);
		specular = vec_multi_num(specular, std::pow(std::max(0.0f, dotProduct(n, h)), p));
		res = vecPlus(res, specular);
	}

	vec3f ambient = cwiseProduct(ka, textureColor);
	res = vecPlus(res, ambient);

	return res;
}
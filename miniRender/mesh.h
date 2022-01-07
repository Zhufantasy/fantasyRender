#ifndef __MESH_H__
#define __MESH_H__

#include<array>
#include<algorithm>
#include<vector>
#include"type.h"

struct Vertex {
	vec3f posi;
	vec3f normal;
	vec2f texCoord;
};



class Triangle {
public:
	Vertex vertices[3];

	bool insideTriangle(const vec2f &p) const;
	//������������
	vec3f calculateBarycentricCoordinates(const vec2f &p) const;
	//��ֵ
	vec2f interpolate(const vec3f &baryCoord, const vec2f& vert1, const vec2f& vert2, const vec2f& vert3);
	vec3f interpolate(const vec3f &baryCoord, const vec3f& vert1, const vec3f& vert2, const vec3f& vert3);

private:
	//�����������������޸�Ϊ��ʱ�뷽��
	void counterClockWise();
};



class Mesh {
public:
	std::vector<Triangle*> trianglesP;
	mat4f model;

	Mesh();
	void setModel(const mat4f& m);
};

#endif // __MESH_H__


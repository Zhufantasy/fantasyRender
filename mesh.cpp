#include "mesh.h"
#include "math.h"

//²Î¿¼:https://leetcode-cn.com/circle/discuss/7OldE4/
bool Triangle::insideTriangle(const vec2f &p) const
{
	vec3f beryCoord = calculateBarycentricCoordinates(p);
	if (beryCoord[0] > 0.0f && beryCoord[1] > 0.0f && beryCoord[2] > 0.0f) {
		return true;
	}
	else {
		return false;
	}
}

//²Î¿¼:https://leetcode-cn.com/circle/discuss/7OldE4/
void Triangle::counterClockWise()
{
	if (((vertices[2].posi[0] - vertices[0].posi[0])*(vertices[1].posi[1] - vertices[0].posi[1]) - (vertices[2].posi[1] - vertices[0].posi[1])*(vertices[1].posi[0] - vertices[0].posi[0])) > 0) {
		return;
	}
	else {
		std::swap(vertices[1], vertices[2]);
	}
	return;
}

vec3f Triangle::calculateBarycentricCoordinates(const vec2f &p) const
{
	vec3f p1 = this->vertices[0].posi, p2 = this->vertices[1].posi, p3 = this->vertices[2].posi;
	float tmp1 = (p1[1] - p3[1])*p[0] + (p3[0] - p1[0])*p[1] + p1[0] * p3[1] - p3[0] * p1[1];
	float tmp2 = (p1[1] - p3[1])*p2[0] + (p3[0] - p1[0])*p2[1] + p1[0] * p3[1] - p3[0] * p1[1];
	float tmp3 = (p1[1] - p2[1])*p[0] + (p2[0] - p1[0])*p[1] + p1[0] * p2[1] - p2[0] * p1[1];
	float tmp4 = (p1[1] - p2[1])*p3[0] + (p2[0] - p1[0])*p3[1] + p1[0] * p2[1] - p2[0] * p1[1];
	return vec3f{ 1 - tmp1 / tmp2 - tmp3 / tmp4,tmp1 / tmp2,tmp3 / tmp4 };
}

void Triangle::calculateNormal()
{
	
}

vec2f Triangle::interpolate(const vec3f &baryCoord, const vec2f& vert1, const vec2f& vert2, const vec2f& vert3)
{
	float u = baryCoord[0] * vert1[0] + baryCoord[1] * vert2[0] + baryCoord[2] * vert3[0];
	float v = baryCoord[0] * vert1[1] + baryCoord[1] * vert2[1] + baryCoord[2] * vert3[1];
	return vec2f{ u,v };
}

vec3f Triangle::interpolate(const vec3f &baryCoord, const vec3f& vert1, const vec3f& vert2, const vec3f& vert3)
{
	float u = baryCoord[0] * vert1[0] + baryCoord[1] * vert2[0] + baryCoord[2] * vert3[0];
	float v = baryCoord[0] * vert1[1] + baryCoord[1] * vert2[1] + baryCoord[2] * vert3[1];
	float w = baryCoord[0] * vert1[2] + baryCoord[1] * vert2[2] + baryCoord[2] * vert3[2];
	return vec3f{ u,v,w };
}

Mesh::Mesh() {
	model = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1,
	};
}

void Mesh::setModel(const mat4f& m)
{
	this->model = m;
}
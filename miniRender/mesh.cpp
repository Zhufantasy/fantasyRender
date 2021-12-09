#include "mesh.h"
#include "math.h"
#include "tmp.h"

//²Î¿¼:https://leetcode-cn.com/circle/discuss/7OldE4/
bool Triangle::insideTriangle(const vec2f &p) const
{
	vec3f beryCoord = calculateBarycentricCoordinates(this, p);
	if (beryCoord[0] > 0 && beryCoord[1] > 0 && beryCoord[2] > 0) {
		return true;
	}
	else {
		return false;
	}
}

//²Î¿¼:https://leetcode-cn.com/circle/discuss/7OldE4/
void Triangle::counterClockWise()
{
	if (((verticesP[2]->posi[0] - verticesP[0]->posi[0])*(verticesP[1]->posi[1] - verticesP[0]->posi[1]) - (verticesP[2]->posi[1] - verticesP[0]->posi[1])*(verticesP[1]->posi[0] - verticesP[0]->posi[0])) > 0) {
		return;
	}
	else {
		std::swap(verticesP[1], verticesP[2]);
	}
	return;
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
#include "triangle.h"

Triangle::Triangle(const std::array<std::array<int, 3>, 3> &input) :vertices(input)
{
	counterClockWise();
}

//²Î¿¼:https://leetcode-cn.com/circle/discuss/7OldE4/
bool Triangle::insideTriangle(const std::array<int, 2> &p) const
{
	if (((p[0] - vertices[0][0])*(vertices[1][1] - vertices[0][1]) - (p[1] - vertices[0][1])*(vertices[1][0] - vertices[0][0])) < 0) {
		return false;
	}
	if (((p[0] - vertices[1][0])*(vertices[2][1] - vertices[1][1]) - (p[1] - vertices[1][1])*(vertices[2][0] - vertices[1][0])) < 0) {
		return false;
	}
	if (((p[0] - vertices[2][0])*(vertices[0][1] - vertices[2][1]) - (p[1] - vertices[2][1])*(vertices[0][0] - vertices[2][0])) < 0) {
		return false;
	}
	return true;
}

//²Î¿¼:https://leetcode-cn.com/circle/discuss/7OldE4/
void Triangle::counterClockWise()
{
	if (((vertices[2][0] - vertices[0][0])*(vertices[1][1] - vertices[0][1]) - (vertices[2][1] - vertices[0][1])*(vertices[1][0] - vertices[0][0])) > 0) {
		return;
	}
	else {
		std::swap(vertices[1], vertices[2]);
	}
	return;
}
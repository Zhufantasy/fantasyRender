#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include<array>
#include<algorithm>

class Triangle {
public:
	std::array<std::array<int, 3>, 3> vertices;

	Triangle() = default;
	Triangle(const std::array<std::array<int, 3>, 3> &input);

	bool insideTriangle(const std::array<int, 2> &p) const;


private:
	//将三角形三个顶点修改为逆时针方向
	void counterClockWise();

};

#endif // __TRIANGLE_H__


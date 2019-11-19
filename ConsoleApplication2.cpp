// ConsoleApplication2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
//#include "vec3.h"
#include "ray.h"
#include <iostream>

bool hit_Sphere(ray r ,vec3 sphereCenter,float radius) {
	vec3 unit = unit_vector(r.direction() - r.origin());
	vec3 cameraToSphere = sphereCenter - r.origin();
	vec3  a = cross(unit,cameraToSphere);
	if (a.length() > radius) {
		return false;
	}
	else
	{
		return true;
	}
}



vec3 color(ray r) {
	vec3 unit = unit_vector(r.direction());// ;
	float t = (unit.y() + sqrt(2) / 1.5) / sqrt(5);
	vec3 skyColor = (1 - t) * vec3(1, 1, 1) + t * vec3(0.1, 0.44, 1);
	if (hit_Sphere(r,vec3(0,0,-6),3.0)) {
		return vec3(0.5, 0.8, 0.4);
	}
	else {
		return skyColor;
	}
	//return 
}

int main()
{
	int nx = 200;
	int ny = 100;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 camera(0, 0, 0);
	float width = 4;
	float height = 2;
	vec3 leftBottomCorner(-2,-1,-1);

	//vec3 lefrBottomCorner();
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			
			
			//float r = float(i) / float(nx);
			//float g = float(j) / float(ny);
			//float b = 0;// float(j*i) * 2 / float(ny*ny);
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(camera, leftBottomCorner +vec3( u * width,v*height,-0));

			


			vec3 col = color(r);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

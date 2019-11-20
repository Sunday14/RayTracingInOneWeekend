// ConsoleApplication2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
//#include "vec3.h"
#include "ray.h"
#include "svpng.inc"
#include <iostream>

bool hit_Sphere(ray r ,vec3 sphereCenter,float radius) {
	vec3 unit = unit_vector(r.direction() - r.origin());
	vec3 cameraToSphere = sphereCenter - r.origin();
	vec3  a = cross(unit,cameraToSphere);
	float A = pow(r.direction().length(),2);
	float B = 2 * dot(r.direction(),r.origin() - sphereCenter);
	float C = dot(r.origin() - sphereCenter, r.origin() - sphereCenter) - radius * radius;
	float judge = B * B - 4 * A *C;


	bool isIntersection = false;


	if (a.length() <= radius) {
		//isIntersection = true;
	}
	if (judge >= 0) {
		isIntersection = true;
	}
	return isIntersection;
}



vec3 color(ray r) {
	vec3 unit = unit_vector(r.direction());// ;
	float t = (unit.y() + sqrt(2) / 1.5) / sqrt(5);
	vec3 skyColor = (1 - t) * vec3(1, 1, 1) + t * vec3(0.1, 0.44, 1);
	if (hit_Sphere(r,vec3(0.5,0,-1.5),0.8)) {
		return vec3(0.5, 0.8, 0.4);
	}
	else {
		return skyColor;
	}
	//return 
}

int main()
{
	const int nx = 800;
	const int ny = 400;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 camera(0, 0, 0);
	float width = 4;
	float height = 2;
	vec3 leftBottomCorner(-2,-1,-0.7);

	//vec3 lefrBottomCorner();
	FILE *fp = fopen("rgb.png", "wb");
	unsigned char rgb[nx * ny * 3], *p = rgb;
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			
			
			//float r = float(i) / float(nx);
			//float g = float(j) / float(ny);
			//float b = 0;// float(j*i) * 2 / float(ny*ny);
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(camera, leftBottomCorner +vec3( u * width,v*height,0));

			


			vec3 col = color(r);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);

			*p++ = (unsigned char)ir;    /* R */
			*p++ = (unsigned char)ig;    /* G */
			*p++ = ib;

			
			//std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	svpng(fp, nx, ny, rgb, 0);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln
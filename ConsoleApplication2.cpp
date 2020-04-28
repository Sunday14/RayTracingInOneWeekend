// ConsoleApplication2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
//#include "vec3.h"
#include "ray.h"
#include "svpng.inc"
#include "sphere.h"
#include "hitable_list.h"
#include <iostream>
#include <time.h>
#define MAXFLOAT 1000.0




float hit_Sphere(const vec3& sphereCenter,float radius, ray r) {
	vec3 unit = unit_vector(r.direction() - r.origin());
	vec3 oc = r.origin() - sphereCenter;
	//vec3 cameraToSphere = sphereCenter - r.origin();
	float  a =  dot(r.direction(),r.direction());// cross(unit, cameraToSphere);
	//float A = pow(r.direction().length(),2);
	float b = 2 * dot(r.direction(),r.origin() - sphereCenter);
	float c = dot(r.origin() - sphereCenter, r.origin() - sphereCenter) - radius * radius;
	float discriminant = b * b - 4 * a *c;

	if (discriminant < 0) {
		return -1.0;
	}
	else {
		return (-b - sqrt(discriminant)) / (2.0*a);
	}


	//bool isIntersection = false;


	//if (a.length() <= radius) {
	//	//isIntersection = true;
	//}
	//if (judge >= 0) {
	//	isIntersection = true;
	//}
	//if (isIntersection) {
	//	return (-B - sqrt(judge)) / (2.0*A);
	//}
	//else {
	//	return -1.0;
	//}
	//return isIntersection;
}



vec3 color_1(ray r) {
	//vec3 unit = unit_vector(r.direction());// ;
	//float t = (unit.y() + sqrt(2) / 1.5) / sqrt(5);
	//vec3 skyColor = (1 - t) * vec3(1, 1, 1) + t * vec3(0.1, 0.44, 1);
	float t = hit_Sphere( vec3(0.0, 0, -1), 0.5, r);

	if (t > 0.0) {
		vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0,0,-1));
		return 0.5 * vec3(N.x() + 1 ,N.y() + 1,N.z() +1);

		//return vec3(0.5, 0.8, 0.4);
	}
	//else {
		//return skyColor;
	//}
	//return 
	vec3 unit_direction = unit_vector(r.direction());
	t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t) *vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}


double Rands() {
	return float(rand()) / float(RAND_MAX + 1.0);
}

vec3 random_in_sphere() {
	vec3 p;
	do {
		p = 2.0* vec3(Rands(), Rands(), Rands()) - vec3(1, 1, 1);
	}while(p.squared_length() >= 1.0);
	return p;
}

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = 2.0*vec3(Rands(), Rands(), Rands()) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0);
	return p;
}

vec3 color_2(const ray& r,hitable * world) {
	hit_record rec;
	if (world->hit(r, 0.001, MAXFLOAT, rec)) {
		return  0.5*vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}
	else {
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y() + 1.0);
		return (1.0 - t) *vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

vec3 color(const ray& r,hitable *world) {
	hit_record rec;
	if (world->hit(r, 0.0, MAXFLOAT, rec)) {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5*color(ray(rec.p,target-rec.p),world);
	}
	else {
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y() + 1.0);
		return (1.0 - t) *vec3(1.0, 1.0, 1.0) + t * vec3(0.9, 0.3, 0.2);
	}
}



int main()
{
	const int nx = 600;
	const int ny = 300;
	int ns = 100;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	//vec3 camera(0, 0, 0);
	float width = 4;
	float height = 2;

	vec3 horizotal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 leftBottomCorner(-2,-1,-1.0);

	//vec3 lefrBottomCorner();
	FILE *fp = fopen("rgb.png", "wb");

	hitable *list[2];
	list[0] = new sphere(vec3(0,0,-1),0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);

	hitable *world = new hitable_list(list, 2);

	camera cam;
	srand((unsigned)time(NULL));

	unsigned char rgb[nx * ny * 3], *cc = rgb;
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			
			
			//float r = float(i) / float(nx);
			//float g = float(j) / float(ny);
			//float b = 0;// float(j*i) * 2 / float(ny*ny);
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			//ray r(camera, leftBottomCorner +u*horizotal + v * vertical);
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = float(i + Rands()) / float(nx);
				float v = float(j + Rands()) / float(ny);
				ray r = cam.get_ray(u,v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r,world);
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

			//vec3 p = r.point_at_parameter(2.0);
			//vec3 col = color(r, world);
			//col = color_1(r);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);

			*cc++ = (unsigned char)ir;    /* R */
			*cc++ = (unsigned char)ig;    /* G */
			*cc++ = ib;

			
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
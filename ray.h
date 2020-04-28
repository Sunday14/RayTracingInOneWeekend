#pragma once
#ifndef RAYH
#define RAYH

#include "vec3.h"


class ray {
public: 
	ray(){}
	ray(const vec3& a,const vec3& b) { A = a; B = b; }
	vec3 origin() const { return A; }
	vec3 direction() const { return B; }
	vec3 point_at_parameter(float t) const { return A + t * B; }
	

	vec3 A;
	vec3 B;
};


class camera {
public:
	camera() {
		lower_left_corner = vec3(-2.0, -1.0, -1.0);
		horizontal = vec3(4.0,0.0,0.0 );
		vertical = vec3(0.0,2.0,0.0);
		origin = vec3(0.0,0.0,0.0);
	}
	ray get_ray(float u, float v) { return ray(origin, lower_left_corner + u * horizontal + v * vertical); }
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
};



#endif // !RAYH


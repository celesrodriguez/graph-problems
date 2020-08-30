#ifndef POINT_H_
#define POINT_H_

#include <math.h>

struct Point {
    float x;
    float y;


    Point(float x, float y): x(x), y(y)
	{
	}

	float DistanceTo(Point p){
		return sqrt(pow(p.x - x, 2) + pow(p.y - y, 2));
	}
};

#endif

#include "astromath.h"
#include <cmath>
double format_a360( double a )
{
	while( a > 360.0 ){
		a -= 360.0;
	}
	while( a < 0.0 ){
		a += 360.0;
	}
	return a;
}

double format_a180( double a )
{
	while( a > 180.0 ){
		a -= 360.0;
	}
	while( a < -180.0 ){
		a += 360.0;
	}
	return a;
}

double arc_angle( double arc )
{
	return arc * 180.0 / PI;
}

double angle_arc( double angle )
{
	return PI * angle / 180.0;
}

#ifndef LINESEGMENT2D_H
#define LINESEGMENT2D_H

#include "Vector2D.h"



typedef struct LineSegment2D
{
	Vector2D mP0;		// Point on the line
	Vector2D mP1;		// Point on the line
	Vector2D mN;		// Line's normal
	float mNdotP0;		// To avoid computing it every time it's needed
}LineSegment2D;


/*
This function builds a 2D line segment's data using 2 points
 - Computes the normal (Unit Vector)
 - Computes the dot product of the normal with one of the points

 - Parameters
	- LS:		The to-be-built line segment
	- Point0:	One point on the line
	- Point1:	Another point on the line

 - Returns 1 if the line equation was built successfully 
*/
int BuildLineSegment2D(LineSegment2D *LS, Vector2D *Point0, Vector2D *Point1);




#endif
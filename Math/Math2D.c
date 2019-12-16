/* Start Header -------------------------------------------------------

  Copyright (C) 2019 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.

File Name:  <Project1_Part1>
Purpose:  <Math libraries created for use in 2D games later in the course>
Language:  <specify language and compiler>
Platform: <specify compiler version, hardware requirements, operating systems>
Project: <Student Login - taksh.goyal, Class - CS 529, Assignment - CS529_Project1_Part1>
Author:  <Name - Taksh Goyal, Student Login - taksh.goyal, Student ID - 60001319>
Creation date: <19th September, 2019>

 - End Header --------------------------------------------------------*/


#include "Math2D.h"
#include "stdio.h"
#include "Vector2D.h"
#include "Math.h"
 /*
 This function checks if the point P is colliding with the circle whose
 center is "Center" and radius is "Radius"
 */
int StaticPointToStaticCircle(Vector2D* pP, Vector2D* pCenter, float Radius)
{
	float xcentdist = pP->x - pCenter->x;
	float ycentdist = pP->y - pCenter->y;
	if (pow(xcentdist, 2) + (pow(ycentdist, 2)) <= (pow(Radius, 2)))
		return 1;
	return 0;
}


/*
This function checks if the point Pos is colliding with the rectangle
whose center is Rect, width is "Width" and height is Height
*/
int StaticPointToStaticRect(Vector2D* pPos, Vector2D* pRect, float Width, float Height)
{
	Vector2D tl, br;
	tl.x = pRect->x - (Width / 2.0f);
	tl.y = pRect->y + (Height / 2.0f);

	br.x = pRect->x + (Width / 2.0f);
	br.y = pRect->y - (Height / 2.0f);
	if (pPos->x < tl.x || pPos->x > br.x || pPos->y > tl.y || pPos->y < br.y)
		return 0;
	return 1;
}

/*
This function checks for collision between 2 circles.
Circle0: Center is Center0, radius is "Radius0"
Circle1: Center is Center1, radius is "Radius1"
*/
int StaticCircleToStaticCircle(Vector2D* pCenter0, float Radius0, Vector2D* pCenter1, float Radius1)
{
	float radsumsq = (pow(Radius0 + Radius1, 2));
	float xcentdist = pCenter0->x - pCenter1->x;
	float ycentdist = pCenter0->y - pCenter1->y;
	float centerDist = pow(xcentdist, 2) + (pow(ycentdist, 2));
	if (centerDist <= radsumsq)
		return 1;
	return 0;
}

/*
This functions checks if 2 rectangles are colliding
Rectangle0: Center is pRect0, width is "Width0" and height is "Height0"
Rectangle1: Center is pRect1, width is "Width1" and height is "Height1"
*/
int StaticRectToStaticRect(Vector2D* pRect0, float Width0, float Height0, Vector2D* pRect1, float Width1, float Height1)
{
	Vector2D tl0, br0, tl1, br1;
	tl0.x = pRect0->x - (Width0 / 2); tl0.y = pRect0->y + (Height0 / 2);
	br0.x = pRect0->x + (Width0 / 2); br0.y = pRect0->y - (Height0 / 2);
	tl1.x = pRect1->x - (Width1 / 2); tl1.y = pRect1->y + (Height1 / 2);
	br1.x = pRect1->x + (Width1 / 2); br1.y = pRect1->y - (Height1 / 2);
	if (br0.x < tl1.x || tl0.y < br1.y || br1.x < tl0.x || br0.y > tl1.y)
		return 0;
	return 1;
}

//////////////////////
// New to project 2 //
//////////////////////


/*
This function determines the distance separating a point from a line

 - Parameters
	- P:		The point whose location should be determined
	- LS:		The line segment

 - Returned value: The distance. Note that the returned value should be:
	- Negative if the point is in the line's inside half plane
	- Positive if the point is in the line's outside half plane
	- Zero if the point is on the line
*/
float StaticPointToStaticLineSegment(Vector2D *P, LineSegment2D *LS)
{
	float NdotP, Result, NdotP0;

	NdotP0 = LS->mNdotP0;
	NdotP = Vector2DDotProduct(&LS->mN, P);

	Result = NdotP - NdotP0;

	if (Result > 0 || Result < 0)
		return Result;
	else
		return 0;
}


/*
This function checks whether an animated point is colliding with a line segment

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedPointToStaticLineSegment(Vector2D *Ps, Vector2D *Pe, LineSegment2D *LS, Vector2D *Pi)
{
	float result1, result2;

	result1 = StaticPointToStaticLineSegment(Ps, LS);
	result2 = StaticPointToStaticLineSegment(Pe, LS);

	if ((result1 > 0 && result2 > 0) || (result1 < 0 && result2 < 0))
	{
		return -1.0f;
	}

	Vector2D Pvel, PiP0, P1P0, P0P1, PiP1;
	float NdotPVel, NdotP0, NdotPs, NdotPe, t;
	Vector2DSub(&Pvel, Pe, Ps);

	NdotP0 = LS->mNdotP0;
	NdotPVel = Vector2DDotProduct(&Pvel, &LS->mN);
	NdotPs = Vector2DDotProduct(Ps, &LS->mN);
	NdotPe = Vector2DDotProduct(Pe, &LS->mN);

	t = (NdotP0 - NdotPs) / NdotPVel;

	Vector2DScaleAdd(Pi, &Pvel, Ps, t); // Pi value assigned

	Vector2DSub(&PiP0, Pi, &LS->mP0);
	Vector2DSub(&PiP1, Pi, &LS->mP1);
	Vector2DSub(&P1P0, &LS->mP1, &LS->mP0);
	Vector2DNeg(&P0P1, &P1P0);

	if (NdotPVel == 0)
		return -1.0f;
	else if ((NdotPs < NdotP0) && (NdotPe < NdotP0))
		return -1.0f;
	else if ((NdotPs > NdotP0) && (NdotPe > NdotP0))
		return -1.0f;
	else if (Vector2DDotProduct(&PiP0, &P1P0) < 0)
		return -1.0f;
	else if (Vector2DDotProduct(&PiP1, &P0P1) < 0)
		return -1.0f;
	else
		return t;

	
}


/*
This function checks whether an animated circle is colliding with a line segment

 - Parameters
	- Ps:		The center's starting location
	- Pe:		The center's ending location
	- Radius:	The circle's radius
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedCircleToStaticLineSegment(Vector2D *Ps, Vector2D *Pe, float Radius, LineSegment2D *LS, Vector2D *Pi)
{
	Vector2D incident, v, PiP1, PiP0, P1P0, P0P1;
	float D, t, NdotP0, NdotPs, NdotV, NdotPe, Ndotv, R, Result1, Result2;

	Result1 = StaticPointToStaticLineSegment(Ps, LS);
	Result2 = StaticPointToStaticLineSegment(Pe, LS);

	if ((Result1 > 0 && Result2 > 0) || (Result1 < 0 && Result2 < 0))
	{
		return -1.0f;
	}


	R = StaticPointToStaticLineSegment(Ps, LS);
	D = Radius;

	if (R > 0)
	{
		D = Radius;

	}
	else if (R < 0)
	{
		D = -Radius;
	}

	LineSegment2D temp;

	Vector2D t1;
	Vector2D t2;
	Vector2DScaleAdd(&t1, &LS->mN, Ps, D);
	Vector2DScaleAdd(&t2, &LS->mN, Pe, D);

	BuildLineSegment2D(&temp, &t1, &t2);

	t = AnimatedPointToStaticLineSegment(&t1, &t2, &temp, Pi);

	//Vector2DSub(&incident, Pe, Ps); //incident def
	//Vector2DDotProduct(&incident, &LS->mN);
	//incident.x = LS->mN.x;
	//incident.y = LS->mN.y;
	//Vector2DSet(&super, &incident.x, &incident.y); // super def
	//Vector2DNeg(&super, &super);
	//Vector2DSub(&mid, &incident, &super); //mid def
	//Vector2DSub(&reflected, &mid, &super);
	//Vector2DAdd(&PePrime, Pi, &reflected);
	//Vector2DNormalize(&unitVecV, &reflected);

	Vector2DSub(&v, &Pe, &Ps);
	NdotP0 = temp.mNdotP0;
	NdotPs = Vector2DDotProduct(&temp.mN, &Ps);
	NdotPe = Vector2DDotProduct(&temp.mN, &Pe);
	Ndotv = Vector2DDotProduct(&temp.mN, &v);
	t = (NdotP0 - NdotPs + D) / (Ndotv);
	Vector2DScaleAdd(Pi, &v, &t1, t); // Pi assigned
	Vector2DSub(&PiP1, Pi, &t2);
	Vector2DSub(&PiP0, Pi, &t1);
	Vector2DSub(&P1P0, &t2, &t1);
	Vector2DNeg(&P0P1, &P1P0);




	if (R < 0)
	{
		if (((NdotPs - NdotP0) < D) && ((NdotPe - NdotP0) < D))
			return -1.0f;
	}
	else
		if (R > 0)
		{
			if (((NdotPs - NdotP0) > D) && ((NdotPe - NdotP0) > D))
				return -1.0f;
		}
		else if (Vector2DDotProduct(&PiP1, &P0P1) < 0)
		{
			return -1.0f;
		}
		else if (Vector2DDotProduct(&PiP0, &P1P0) < 0)
		{
			return -1.0f;
		}
		else
			return t;

	
}


/*
This function reflects an animated point on a line segment.
It should first make sure that the animated point is intersecting with the line 

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedPointOnStaticLineSegment(Vector2D *Ps, Vector2D *Pe, LineSegment2D *LS, Vector2D *Pi, Vector2D *R)
{
	Vector2D incident, v;
	float t, IdotN;
	t = AnimatedPointToStaticLineSegment(Ps, Pe, LS, Pi);
	if (t == -1.0f)
	{
		return -1.0f;
		exit(0);
	}
	//Vector2DSub(&v, Ps, Pe);
	//Vector2DScaleAdd(Pi, Ps, &v, t);
	Vector2DSub(&incident, Pe, Pi); //incident def
	IdotN = Vector2DDotProduct(&incident, &LS->mN);
	//incident.x *= LS->mN.x;
	//incident.y *= LS->mN.y;
	//Vector2DSet(&super, incident.x, incident.y); // super def
	//Vector2DNeg(&super, &super);
	//Vector2DSub(&mid, &incident, &super); //mid def
	//Vector2DSub(&reflected, &mid, &super);
	//Vector2DAdd(&PePrime, Pi, &reflected);
	//Vector2DNormalize(&unitVecV, &reflected);
	Vector2DScaleAdd(R, &LS->mN, &incident, -(2 * IdotN));
	return t;
}


/*
This function reflects an animated circle on a line segment.
It should first make sure that the animated point is intersecting with the line 

 - Parameters
	- Ps:		The center's starting location
	- Pe:		The center's ending location
	- Radius:	The circle's radius
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedCircleOnStaticLineSegment(Vector2D *Ps, Vector2D *Pe, float Radius, LineSegment2D *LS, Vector2D *Pi, Vector2D *R)
{
	Vector2D temp1;
	Vector2D temp2;

	float dist = StaticPointToStaticLineSegment(Ps, LS);

	Vector2D offset;
	Vector2DScale(&offset, &LS->mN, Radius);


	if (dist < 0) {
		Vector2DSub(&temp1, &LS->mP0, &offset);
		Vector2DSub(&temp2, &LS->mP1, &offset);
	}
	if (dist > 0) {
		Vector2DAdd(&temp1, &LS->mP0, &offset);
		Vector2DAdd(&temp2, &LS->mP1, &offset);
	}

	LineSegment2D tL;
	BuildLineSegment2D(&tL, &temp1, &temp2);

	float t = ReflectAnimatedPointOnStaticLineSegment(Ps, Pe, &tL, Pi, R);

	return t;
}


/*
This function checks whether an animated point is colliding with a static circle

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- Center:	The circle's center
	- Radius:	The circle's radius
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedPointToStaticCircle(Vector2D *Ps, Vector2D *Pe, Vector2D *Center, float Radius, Vector2D *Pi)
{
	Vector2D v,PsC;
	float M, S2, S, N2, ti0;  //ti0 is time of intersection of the first point of intersection
	Vector2DSub(&v, Pe, Ps);
	Vector2DSub(&PsC, Center, Ps);
	Vector2DNormalize(&v, &v);
	M = Vector2DDotProduct(&PsC, &v);
	N2 = pow(Vector2DLength(&PsC), 2) - pow(M, 2); // Calculated Nsquare
	S2 = pow(Radius, 2) - N2;
	S = sqrt(S2);
	ti0 = (M - S) / Vector2DLength(&v);
	Vector2DScaleAdd(Pi, &v, Ps, ti0);


	if (M<0 && Vector2DDistance(Ps, Center)>Radius)
	{
		return -1.0f;
	}
	else if (N2 > pow(Radius, 2))
	{
		return 1.0f;
	}
	else
		return ti0;
}



/*
This function reflects an animated point on a static circle.
It should first make sure that the animated point is intersecting with the circle 

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- Center:	The circle's center
	- Radius:	The circle's radius
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedPointOnStaticCircle(Vector2D *Ps, Vector2D *Pe, Vector2D *Center, float Radius, Vector2D *Pi, Vector2D *R)
{
	float t;
	Vector2D n,m;
	t = AnimatedPointToStaticCircle(Ps, Pe, Center, Radius, Pi);
	Vector2DSub(&n, Center, Pi);
	Vector2DNormalize(&n, &n);
	Vector2DSub(&m, Ps, Pi);
	Vector2DNeg(&m, &m);
	Vector2DScaleAdd(R, &n, &m, 2 * Vector2DDotProduct(&m, &n));
	return -1.0f;
}


/*
This function checks whether an animated circle is colliding with a static circle

 - Parameters
	- Center0s:		The starting position of the animated circle's center 
	- Center0e:		The ending position of the animated circle's center 
	- Radius0:		The animated circle's radius
	- Center1:		The static circle's center
	- Radius1:		The static circle's radius
	- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedCircleToStaticCircle(Vector2D *Center0s, Vector2D *Center0e, float Radius0, Vector2D *Center1, float Radius1, Vector2D *Pi)
{
	float t;
	t = AnimatedPointToStaticCircle(&Center0s, &Center0e, &Center1, Radius1, &Pi);
	Radius1 = Radius1 + Radius0;
	t = AnimatedPointToStaticCircle(&Center0s, &Center0e, &Center1, Radius1, &Pi);
	return t;
}


/*
This function reflects an animated circle on a static circle.
It should first make sure that the animated circle is intersecting with the static one 

 - Parameters
	- Center0s:		The starting position of the animated circle's center 
	- Center0e:		The ending position of the animated circle's center 
	- Radius0:		The animated circle's radius
	- Center1:		The static circle's center
	- Radius1:		The static circle's radius
	- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:			Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedCircleOnStaticCircle(Vector2D *Center0s, Vector2D *Center0e, float Radius0, Vector2D *Center1, float Radius1, Vector2D *Pi, Vector2D *R)
{

	return -1.0f;
}

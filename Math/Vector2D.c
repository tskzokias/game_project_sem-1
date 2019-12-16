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


#include "Vector2D.h"
#include <math.h>
#define EPSILON 0.0001
#define PI      3.1415926535897932384626433832795

 // ---------------------------------------------------------------------------

void Vector2DZero(Vector2D* pResult)
{
	pResult->x = 0;
	pResult->y = 0;
}

// ---------------------------------------------------------------------------

void Vector2DSet(Vector2D* pResult, float x, float y)
{
	pResult->x = x;
	pResult->y = y;
}

// ---------------------------------------------------------------------------

void Vector2DNeg(Vector2D* pResult, Vector2D* pVec0)
{
	pResult->x = -pVec0->x;
	pResult->y = -pVec0->y;
}

// ---------------------------------------------------------------------------

void Vector2DAdd(Vector2D* pResult, Vector2D* pVec0, Vector2D* pVec1)
{
	pResult->x = pVec0->x + pVec1->x;
	pResult->y = pVec0->y + pVec1->y;
}

// ---------------------------------------------------------------------------

void Vector2DSub(Vector2D* pResult, Vector2D* pVec0, Vector2D* pVec1)
{
	pResult->x = pVec0->x - pVec1->x;
	pResult->y = pVec0->y - pVec1->y;
}

// ---------------------------------------------------------------------------

void Vector2DNormalize(Vector2D* pResult, Vector2D* pVec0)
{
	pResult->x = pVec0->x / sqrt(pow(pVec0->x, 2) + pow(pVec0->y, 2));
	pResult->y = pVec0->y / sqrt(pow(pVec0->x, 2) + pow(pVec0->y, 2));
}

// ---------------------------------------------------------------------------

void Vector2DScale(Vector2D* pResult, Vector2D* pVec0, float c)
{
	pResult->x = pVec0->x * c;
	pResult->y = pVec0->y * c;
}

// ---------------------------------------------------------------------------

void Vector2DScaleAdd(Vector2D* pResult, Vector2D* pVec0, Vector2D* pVec1, float c)
{
	pResult->x = (pVec0->x * c) + pVec1->x;
	pResult->y = (pVec0->y * c) + pVec1->y;
}

// ---------------------------------------------------------------------------

void Vector2DScaleSub(Vector2D* pResult, Vector2D* pVec0, Vector2D* pVec1, float c)
{
	pResult->x = (pVec0->x * c) - pVec1->x;
	pResult->y = (pVec0->y * c) - pVec1->y;
}

// ---------------------------------------------------------------------------

float Vector2DLength(Vector2D* pVec0)
{
	return (sqrt(pow(pVec0->x, 2) + pow(pVec0->y, 2)));
}

// ---------------------------------------------------------------------------

float Vector2DSquareLength(Vector2D* pVec0)
{
	return (pow(pVec0->x, 2) + pow(pVec0->y, 2));
}

// ---------------------------------------------------------------------------

float Vector2DDistance(Vector2D* pVec0, Vector2D* pVec1)
{
	float xdist = pVec0->x - pVec1->x;
	float ydist = pVec0->y - pVec1->y;
	return (sqrt(pow(xdist, 2) + (pow(ydist, 2))));
}

// ---------------------------------------------------------------------------

float Vector2DSquareDistance(Vector2D* pVec0, Vector2D* pVec1)
{
	float xdist = pVec0->x - pVec1->x;
	float ydist = pVec0->y - pVec1->y;
	return (pow(xdist, 2) + pow(ydist, 2));
}

// ---------------------------------------------------------------------------

float Vector2DDotProduct(Vector2D* pVec0, Vector2D* pVec1)
{
	return ((pVec0->x * pVec1->x) + (pVec0->y * pVec1->y));
}

// ---------------------------------------------------------------------------

void Vector2DFromAngleDeg(Vector2D* pResult, float angle)
{
	pResult->x = ((pResult->x) * cos((angle * PI) / 180)) - ((pResult->y) * sin(angle * PI) / 180);
	pResult->y = ((pResult->x) * sin((angle * PI) / 180)) + ((pResult->y) * cos(angle * PI) / 180);
}

// ---------------------------------------------------------------------------

void Vector2DFromAngleRad(Vector2D* pResult, float angle)
{
	pResult->x = ((pResult->x) * cos(angle)) - ((pResult->y) * sin(angle));
	pResult->y = ((pResult->x) * sin(angle)) + ((pResult->y) * cos(angle));
}

float Vector2DAngleFromVec2(Vector2D* pResult)
{
	float angle;
	angle = atan2(pResult->y, pResult->x);
	return angle;
}

// ---------------------------------------------------------------------------

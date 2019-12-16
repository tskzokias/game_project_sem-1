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




#include "Matrix2D.h"
#define PI      3.1415926535897932384626433832795


 /*
 This function sets the matrix Result to the identity matrix
 */
void Matrix2DIdentity(Matrix2D* pResult)
{
	pResult->m[0][0] = 1;
	pResult->m[0][1] = 0;
	pResult->m[0][2] = 0;
	pResult->m[1][0] = 0;
	pResult->m[1][1] = 1;
	pResult->m[1][2] = 0;
	pResult->m[2][0] = 0;
	pResult->m[2][1] = 0;
	pResult->m[2][2] = 1;
}

// ---------------------------------------------------------------------------

/*
This functions calculated the transpose matrix of Mtx and saves it in Result
*/
void Matrix2DTranspose(Matrix2D* pResult, Matrix2D* pMtx)
{
	Matrix2D temp = *pMtx;
	temp.m[0][1] = pMtx->m[1][0];
	temp.m[0][2] = pMtx->m[2][0];
	temp.m[1][0] = pMtx->m[0][1];
	temp.m[1][2] = pMtx->m[2][1];
	temp.m[2][0] = pMtx->m[0][2];
	temp.m[2][1] = pMtx->m[1][2];
	*pResult = temp;
}

// ---------------------------------------------------------------------------

/*
This function multiplies Mtx0 with Mtx1 and saves the result in Result
Result = Mtx0*Mtx1
*/
void Matrix2DConcat(Matrix2D* pResult, Matrix2D* pMtx0, Matrix2D* pMtx1)
{
	if (pResult == pMtx0 || pResult == pMtx1) {
		Matrix2D temp;
		temp.m[0][0] = ((pMtx0->m[0][0]) * (pMtx1->m[0][0])) + ((pMtx0->m[0][1]) * (pMtx1->m[1][0])) + ((pMtx0->m[0][2]) * (pMtx1->m[2][0]));
		temp.m[0][1] = ((pMtx0->m[0][0]) * (pMtx1->m[0][1])) + ((pMtx0->m[0][1]) * (pMtx1->m[1][1])) + ((pMtx0->m[0][2]) * (pMtx1->m[2][1]));
		temp.m[0][2] = ((pMtx0->m[0][0]) * (pMtx1->m[0][2])) + ((pMtx0->m[0][1]) * (pMtx1->m[1][2])) + ((pMtx0->m[0][2]) * (pMtx1->m[2][2]));
		temp.m[1][0] = ((pMtx0->m[1][0]) * (pMtx1->m[0][0])) + ((pMtx0->m[1][1]) * (pMtx1->m[1][0])) + ((pMtx0->m[1][2]) * (pMtx1->m[2][0]));
		temp.m[1][1] = ((pMtx0->m[1][0]) * (pMtx1->m[0][1])) + ((pMtx0->m[1][1]) * (pMtx1->m[1][1])) + ((pMtx0->m[1][2]) * (pMtx1->m[2][1]));
		temp.m[1][2] = ((pMtx0->m[1][0]) * (pMtx1->m[0][2])) + ((pMtx0->m[1][1]) * (pMtx1->m[1][2])) + ((pMtx0->m[1][2]) * (pMtx1->m[2][2]));
		temp.m[2][0] = ((pMtx0->m[2][0]) * (pMtx1->m[0][0])) + ((pMtx0->m[2][1]) * (pMtx1->m[1][0])) + ((pMtx0->m[2][2]) * (pMtx1->m[2][0]));
		temp.m[2][1] = ((pMtx0->m[2][0]) * (pMtx1->m[0][1])) + ((pMtx0->m[2][1]) * (pMtx1->m[1][1])) + ((pMtx0->m[2][2]) * (pMtx1->m[2][1]));
		temp.m[2][2] = ((pMtx0->m[2][0]) * (pMtx1->m[0][2])) + ((pMtx0->m[2][1]) * (pMtx1->m[1][2])) + ((pMtx0->m[2][2]) * (pMtx1->m[2][2]));
		*pResult = temp;
	}
	else {
		pResult->m[0][0] = ((pMtx0->m[0][0]) * (pMtx1->m[0][0])) + ((pMtx0->m[0][1]) * (pMtx1->m[1][0])) + ((pMtx0->m[0][2]) * (pMtx1->m[2][0]));
		pResult->m[0][1] = ((pMtx0->m[0][0]) * (pMtx1->m[0][1])) + ((pMtx0->m[0][1]) * (pMtx1->m[1][1])) + ((pMtx0->m[0][2]) * (pMtx1->m[2][1]));
		pResult->m[0][2] = ((pMtx0->m[0][0]) * (pMtx1->m[0][2])) + ((pMtx0->m[0][1]) * (pMtx1->m[1][2])) + ((pMtx0->m[0][2]) * (pMtx1->m[2][2]));
		pResult->m[1][0] = ((pMtx0->m[1][0]) * (pMtx1->m[0][0])) + ((pMtx0->m[1][1]) * (pMtx1->m[1][0])) + ((pMtx0->m[1][2]) * (pMtx1->m[2][0]));
		pResult->m[1][1] = ((pMtx0->m[1][0]) * (pMtx1->m[0][1])) + ((pMtx0->m[1][1]) * (pMtx1->m[1][1])) + ((pMtx0->m[1][2]) * (pMtx1->m[2][1]));
		pResult->m[1][2] = ((pMtx0->m[1][0]) * (pMtx1->m[0][2])) + ((pMtx0->m[1][1]) * (pMtx1->m[1][2])) + ((pMtx0->m[1][2]) * (pMtx1->m[2][2]));
		pResult->m[2][0] = ((pMtx0->m[2][0]) * (pMtx1->m[0][0])) + ((pMtx0->m[2][1]) * (pMtx1->m[1][0])) + ((pMtx0->m[2][2]) * (pMtx1->m[2][0]));
		pResult->m[2][1] = ((pMtx0->m[2][0]) * (pMtx1->m[0][1])) + ((pMtx0->m[2][1]) * (pMtx1->m[1][1])) + ((pMtx0->m[2][2]) * (pMtx1->m[2][1]));
		pResult->m[2][2] = ((pMtx0->m[2][0]) * (pMtx1->m[0][2])) + ((pMtx0->m[2][1]) * (pMtx1->m[1][2])) + ((pMtx0->m[2][2]) * (pMtx1->m[2][2]));
	}

}

// ---------------------------------------------------------------------------

/*
This function creates a translation matrix from x & y and saves it in Result
*/
void Matrix2DTranslate(Matrix2D* pResult, float x, float y)
{
	float Tx = x, Ty = y;
	pResult->m[0][0] = 1;
	pResult->m[0][1] = 0;
	pResult->m[0][2] = Tx;
	pResult->m[1][0] = 0;
	pResult->m[1][1] = 1;
	pResult->m[1][2] = Ty;
	pResult->m[2][0] = 0;
	pResult->m[2][1] = 0;
	pResult->m[2][2] = 1;
}

// ---------------------------------------------------------------------------

/*
This function creates a scaling matrix from x & y and saves it in Result
*/
void Matrix2DScale(Matrix2D* pResult, float x, float y)
{
	float Sx = x, Sy = y;
	pResult->m[0][0] = Sx;
	pResult->m[0][1] = 0;
	pResult->m[0][2] = 0;
	pResult->m[1][0] = 0;
	pResult->m[1][1] = Sy;
	pResult->m[1][2] = 0;
	pResult->m[2][0] = 0;
	pResult->m[2][1] = 0;
	pResult->m[2][2] = 1;
}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in degree.
Save the resultant matrix in Result
*/
void Matrix2DRotDeg(Matrix2D* pResult, float Angle)
{
	float degconv = ((Angle * PI) / 180.0f);
	pResult->m[0][0] = cos(degconv);
	pResult->m[0][1] = -sin(degconv);
	pResult->m[0][2] = 0;
	pResult->m[1][0] = sin(degconv);
	pResult->m[1][1] = cos(degconv);
	pResult->m[1][2] = 0;
	pResult->m[2][0] = 0;
	pResult->m[2][1] = 0;
	pResult->m[2][2] = 1;
}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in radian.
Save the resultant matrix in Result
*/
void Matrix2DRotRad(Matrix2D* pResult, float Angle)
{
	pResult->m[0][0] = cos(Angle);
	pResult->m[0][1] = -sin(Angle);
	pResult->m[0][2] = 0;
	pResult->m[1][0] = sin(Angle);
	pResult->m[1][1] = cos(Angle);
	pResult->m[1][2] = 0;
	pResult->m[2][0] = 0;
	pResult->m[2][1] = 0;
	pResult->m[2][2] = 1;
}

// ---------------------------------------------------------------------------

/*
This function multiplies the matrix Mtx with the vector Vec and saves the result in Result
Result = Mtx * Vec
*/
void Matrix2DMultVec(Vector2D* pResult, Matrix2D* pMtx, Vector2D* pVec)
{
	Vector2D temp;
	temp.x = (pMtx->m[0][0] * pVec->x) + (pMtx->m[0][1] * pVec->y) + (pMtx->m[0][2] * 1.0f);
	temp.y = (pMtx->m[1][0] * pVec->x) + (pMtx->m[1][1] * pVec->y) + (pMtx->m[1][2] * 1.0f);
	*pResult = temp;

}

// ---------------------------------------------------------------------------

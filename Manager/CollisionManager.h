/* Start Header -------------------------------------------------------

  Copyright (C) 2019 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.

File Name:  <CollisionManager.h>
Purpose:  <Implements Collision based requirements for physics/body required in the GAME>
Language:  <C, C++, SDL - Compilers provided by MSVS2019>
Platform: <MSVS2019, Windows 10>
Project: <Student Login - taksh.goyal, Class - CS 529, Assignment - CS529_Final_Project>
Author:  <Name - Taksh Goyal, Student Login - taksh.goyal, Student ID - 60001319>
Creation date: <23rd November, 2019>

 - End Header --------------------------------------------------------*/

#pragma once
#include <list>
#include "..\Components\Body.h"

class Body;

class Shape
{
public:
	enum class SHAPE_TYPE
	{
		CIRCLE, 
		RECTANGLE,
		AABB,
		NUM
	};

	Shape(SHAPE_TYPE type);
	~Shape() {}

	virtual bool TestPoint(float PointX, float PointY) = 0;

	SHAPE_TYPE mType;
	Body* mpOwnerBody;
};

class ShapeCircle : public Shape
{
public:
	ShapeCircle();
	~ShapeCircle();

	bool TestPoint(float Radius1, float Radius2);
	float mRadius;
};

class ShapeAABB : public Shape
{
public:
	ShapeAABB();
	~ShapeAABB();

	bool TestPoint(float PointX, float PointY);

	float mWidth, mHeight;
};

class Contact
{
public:
	Contact();
	~Contact();

	Body* mBodies[2];
};

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void Reset();

	std::list<Contact*> mContacts;
	/*bool CheckCollisionCIRCLEAABB(Shape* pCircleShape1, float PosX1, float PosY1,Shape* pCircleShape2, float PosX2, float PosY2);
	bool CheckCollisionCIRCLECIRCLE(Shape* pCircleShape1, float mPosX1, float mPosY1, Shape* pCircleShape2, float mPosX2, float mPosY2);
	bool CheckCollisionAABBAABB(Shape* pCircleShape1, float mPosX1, float mPosY1, Shape* pCircleShape2, float mPosX2, float mPosY2);
	bool CheckCollisionAABBCIRCLE(Shape* pCircleShape1, float mPosX1, float mPosY1, Shape* pCircleShape2, float mPosX2, float mPosY2);*/
	bool CheckCollisionAndGenerateContact(Shape* pShape1, float PosX1, float PosY1, Shape* pShape2, float PosX2, float PosY2);
	bool (*CollisionFunctions[(unsigned int)Shape::SHAPE_TYPE::NUM][(unsigned int)Shape::SHAPE_TYPE::NUM])
	(Shape* pShape1, float PosX1, float PosY1, Shape* pShape2, float PosX2, float PosY2, std::list<Contact*>& Contacts);
};
#include "CollisionManager.h"
#include "math.h"
#include "..\Math\Vector2D.h"
#include <iostream>

Shape::Shape(SHAPE_TYPE Type) : mType(Type)
{
	mpOwnerBody = nullptr;
}

ShapeCircle::ShapeCircle() : Shape(SHAPE_TYPE::CIRCLE)
{
	mRadius = 0.0f;
}

ShapeCircle::~ShapeCircle()
{

}

ShapeAABB::ShapeAABB() : Shape(SHAPE_TYPE::AABB)
{
	mWidth = mHeight = 0.0f;
}

ShapeAABB::~ShapeAABB()
{

}

bool ShapeAABB::TestPoint(float PointX, float PointY)
{
	return false;
}

bool ShapeCircle::TestPoint(float Radius1, float Radius2)
{
	return false;
}

bool /*CollisionManager::*/
CheckCollisionCIRCLECIRCLE(Shape* pCircleShape1, float PosX1, float PosY1, 
							Shape* pCircleShape2, float PosX2, float PosY2,
							std::list<Contact*>& mContacts)
{

	//Collision Math and Logic
	float C1C2DistSq, r1, r2;
	C1C2DistSq = pow((PosX1 - PosX2), 2) + pow((PosY1 - PosY2), 2);
	r1 = ((ShapeCircle*)pCircleShape1)->mRadius;
	r2 = ((ShapeCircle*)pCircleShape2)->mRadius;
	if (C1C2DistSq > ((r1 + r2) * (r1 + r2)))
	{
		return false;
	}

	Contact* pContact = new Contact();
	pContact->mBodies[0] = pCircleShape1->mpOwnerBody;
	pContact->mBodies[1] = pCircleShape2->mpOwnerBody;
	mContacts.push_back(pContact);

	return true;
}

bool /*CollisionManager::*/
CheckCollisionCIRCLEAABB(Shape* pCircleShape1, float PosX1, float PosY1,
						Shape* pAABBShape2, float PosX2, float PosY2, 
						std::list<Contact*> &mContacts)
{
	Contact* pContact = new Contact();
	pContact->mBodies[0] = pCircleShape1->mpOwnerBody;
	pContact->mBodies[1] = pAABBShape2->mpOwnerBody;
	mContacts.push_back(pContact);

	//Collision Math and Logic
	/*float C1A2DistSq;
	C1A2DistSq = pow((PosX1 - PosX2), 2) + pow((PosY1 - PosY2), 2);*/
	return true;
}

bool /*CollisionManager::*/
CheckCollisionAABBCIRCLE(Shape* pAABBShape1, float PosX1, float PosY1,
						Shape* pCircleShape2, float PosX2, float PosY2,
						std::list<Contact*> &mContacts)
{
	Contact* pContact = new Contact();
	pContact->mBodies[0] = pAABBShape1->mpOwnerBody;
	pContact->mBodies[1] = pCircleShape2->mpOwnerBody;
	mContacts.push_back(pContact);

	//Collision Math And Logic
	return true;
}

bool /*CollisionManager::*/
CheckCollisionAABBAABB(Shape* pAABBShape1, float PosX1, float PosY1,
						Shape* pAABBShape2, float PosX2, float PosY2,
						std::list<Contact*> &mContacts)
{
	//Collision Math and Logic
	ShapeAABB* pAABB1 = (ShapeAABB*)pAABBShape1;
	ShapeAABB* pAABB2 = (ShapeAABB*)pAABBShape2;

	Vector2D tl0, br0, tl1, br1;
	tl0.x = PosX1 - (pAABB1->mWidth / 2); tl0.y = PosY1 + (pAABB1->mHeight / 2);
	br0.x = PosX1 + (pAABB1->mWidth / 2); br0.y = PosY1 - (pAABB1->mHeight / 2);
	tl1.x = PosX2 - (pAABB2->mWidth / 2); tl1.y = PosY2 + (pAABB2->mHeight / 2);
	br1.x = PosX2 + (pAABB2->mWidth / 2); br1.y = PosY2 - (pAABB2->mHeight / 2);

	if (br0.x < tl1.x || tl0.y < br1.y || br1.x < tl0.x || br0.y > tl1.y)
		return false;

	Contact* pContact = new Contact();
	pContact->mBodies[0] = pAABBShape1->mpOwnerBody;
	pContact->mBodies[1] = pAABBShape2->mpOwnerBody;
	mContacts.push_back(pContact);

	return true;
}

CollisionManager::CollisionManager()//:mContacts()
{
	CollisionFunctions[(unsigned int)Shape::SHAPE_TYPE::CIRCLE][(unsigned int)Shape::SHAPE_TYPE::CIRCLE] = CheckCollisionCIRCLECIRCLE;
	CollisionFunctions[(unsigned int)Shape::SHAPE_TYPE::CIRCLE][(unsigned int)Shape::SHAPE_TYPE::AABB] = CheckCollisionCIRCLEAABB;
	CollisionFunctions[(unsigned int)Shape::SHAPE_TYPE::AABB][(unsigned int)Shape::SHAPE_TYPE::CIRCLE] = CheckCollisionAABBCIRCLE;
	CollisionFunctions[(unsigned int)Shape::SHAPE_TYPE::AABB][(unsigned int)Shape::SHAPE_TYPE::AABB] = CheckCollisionAABBAABB;
}

CollisionManager::~CollisionManager()
{
	Reset();
}

void CollisionManager::Reset()
{
	for (auto c : mContacts)
		delete c;

	mContacts.clear();
}

bool CollisionManager::CheckCollisionAndGenerateContact
(Shape* pShape1, float PosX1, float PosY1, Shape* pShape2, float PosX2, float PosY2)
{
	return CollisionFunctions[(unsigned int)pShape1->mType][(unsigned int)pShape2->mType]
	(pShape1, PosX1, PosY1, pShape2, PosX2, PosY2, this->mContacts);
}

Contact::Contact()
{
	mBodies[0] = mBodies[1] = nullptr;
}

Contact::~Contact()
{

}
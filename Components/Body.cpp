/* Start Header -------------------------------------------------------

  Copyright (C) 2019 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.

File Name:  <Body.cpp>
Purpose:  <Implements Body.h and completes its functionalities>
Language:  <C, C++, SDL - Compilers provided by MSVS2019>
Platform: <MSVS2019, Windows 10>
Project: <Student Login - taksh.goyal, Class - CS 529, Assignment - CS529_Final_Project>
Author:  <Name - Taksh Goyal, Student Login - taksh.goyal, Student ID - 60001319>
Creation date: <17th November, 2019>

 - End Header --------------------------------------------------------*/
#include "Body.h"
#include "memory"
#include "Transform.h"
#include "Component.h"
#include "../GameObject.h"
#include "..\Manager\EventManager.h"

Body::Body() : Component(COMPONENT_TYPE::COMPONENT_BODY)
{
	mPrevPosX = mPrevPosY= mVelX= mVelY= mAccX = mPosX = mPosY = mAccY= mTotalForceX= mTotalForceY=
		mMass = mInvMass = mAddedForceX = mAddedForceY = 0.0f;

	mpShape = nullptr;
	IfPlayerFlag = false;
}

Body::~Body()
{

}

void Body::Initialize(void)
{
	Transform* mpTransform = static_cast<Transform*>(GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));

	if (nullptr != mpTransform)
	{
		mPrevPosX = mPosX = mpTransform->GetPosX();
		mPrevPosY = mPosY = mpTransform->GetPosY();
	}
}

void Body::Serialize(FILE** fpp)
{
	fscanf_s(*fpp, "%f\n", &mMass);

	if (0.0f != mMass)
		mInvMass = 1.0f / mMass;
	else
		mInvMass = 0.0f;

	char shapeType[256];
	memset(shapeType, 0, 256 * sizeof(char));

	fscanf_s(*fpp, "%255s\n", shapeType, sizeof(shapeType));

	if (0 == strcmp(shapeType, "AABB"))
	{
		mpShape = new ShapeAABB();
		mpShape->mpOwnerBody = this;

		ShapeAABB* pAABB = static_cast<ShapeAABB*>(mpShape);
		fscanf_s(*fpp, "%f %f \n", &pAABB->mWidth, &pAABB->mHeight);
	}
	else if (0 == strcmp(shapeType, "Circle"))
	{
		mpShape = new ShapeCircle();
		mpShape->mpOwnerBody = this;

		ShapeCircle* pCircle = static_cast<ShapeCircle*>(mpShape);
		fscanf_s(*fpp, "%f\n", &pCircle->mRadius);
	}
}

void Body::Integrate(float Gravity, float DeltaTime)
{
	mAccX = mAccY = 0.0f;

	DeltaTime = DeltaTime / 1000.0f;

	mPrevPosX = mPosX;
	mPrevPosY = mPosY;

	mInvMass = 1 / mMass;
	if (mMass == 2) // Short Screen so no gravity for bullet
		mInvMass = 0.0f;

	//Apply Gravity
	float g = mMass * Gravity;
	mTotalForceY = mAddedForceY + g; 

	//Apply Acceleration
	mAccX = mTotalForceX * mInvMass;
	mAccY = mTotalForceY * mInvMass;

	//Apply Velocity
	mVelX = (mAccX * DeltaTime) + mVelX;
	mVelY = (mAccY * DeltaTime) + mVelY;

	//Change Position
	mPosX = mVelX * DeltaTime + mPrevPosX;
	mPosY = mVelY * DeltaTime + mPrevPosY;

	Transform* mpTransform = static_cast<Transform*> (GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
	
	if (mMass != 0.0) {
		if (mpTransform != nullptr) {
			mpTransform->mPosY = mPosY;
			mpTransform->mPosX = mPosX;
		}
	}
	else
	{
		mPosX = mpTransform->mPosX;
		mPosY = mpTransform->mPosY;
	}

	mTotalForceX = mTotalForceY = 0.0f;
	mAddedForceX = mAddedForceY = 0.0f;
}

void Body::AddForce(float x, float y)
{
	mTotalForceX += x;
	mTotalForceY += y;
}

void Body::AddVelocity(float x, float y)
{
	mVelX = x;
	mVelY = y;
}

void Body::AppliedVelocity(float x, float y)
{
	mVelX += x;
	mVelY += y;
}

void Body::HandleEvent(Event* pEvent)
{
	if (pEvent->mEventType == EVENT_TYPE::COLLIDE)
	{
		CollisionEvent* pCollEvent = (CollisionEvent*)pEvent;
		if (pCollEvent->mpObject1 == this->GetOwner() || pCollEvent->mpObject2 == this->GetOwner())
		{
			Transform* pTransform = static_cast<Transform*>(this->GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
			Body* pBody = static_cast<Body*>(this->GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));
			if (nullptr != pTransform && nullptr != pBody)
			{
				if (pBody->mMass == 0.0f)
				{
					pTransform->UpdatePosition(1.0f, 0.0f);
				}
				if (pBody->mMass == 0.5f)
				{
					//pTransform->UpdatePosition(-10.0f, 0.0f);
					pBody->AddVelocity(100.0f, -150.0f);
				}
				else if (pBody->mMass == 1.0f) // For Player With Mass 1.0
				{
					pBody->AddVelocity(-100.0f, -350.0f);
				}
			}
		}
		printf("%s", "CollisonEventHandled!! for body\n");
	}
}
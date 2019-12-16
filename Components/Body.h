/* Start Header -------------------------------------------------------

  Copyright (C) 2019 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.

File Name:  <Body.h>
Purpose:  <Implements Body based controls required in the GAME(Physics)>
Language:  <C, C++, SDL - Compilers provided by MSVS2019>
Platform: <MSVS2019, Windows 10>
Project: <Student Login - taksh.goyal, Class - CS 529, Assignment - CS529_Final_Project>
Author:  <Name - Taksh Goyal, Student Login - taksh.goyal, Student ID - 60001319>
Creation date: <17th November, 2019>

 - End Header --------------------------------------------------------*/

#pragma once

#include "Component.h"
#include "..\Manager\CollisionManager.h"

class Shape;

class Body : public Component
{
public:
	Body();
	~Body();
	void Serialize(FILE** fpp);

	void Update() {}
	void Initialize(void);
	void Integrate(float Gravity, float DeltaTime);

	float mPosX, mPosY, mPrevPosX, mPrevPosY, mVelX, mVelY, mAccX, mAccY;
	float mTotalForceX, mTotalForceY, mMass, mInvMass;
	float mAddedForceX, mAddedForceY;

	void AddForce(float x, float y);
	void AddVelocity(float x, float y);
	void Body::AppliedVelocity(float x, float y);

	void HandleEvent(Event* pEvent);

public:
	//bool OneTimeOnly;
	Shape* mpShape;
	bool IfPlayerFlag;

};


/* Start Header -------------------------------------------------------

  Copyright (C) 2019 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.

File Name:  <UpDown.h>
Purpose:  <Header File for automatic up and down component to any Game Object>
Language:  <C, C++, SDL - Compilers provided by MSVS2019>
Platform: <MSVS2019, Windows 10>
Project: <Student Login - taksh.goyal, Class - CS 529, Assignment - CS529_Final_Project>
Author:  <Name - Taksh Goyal, Student Login - taksh.goyal, Student ID - 60001319>
Creation date: <31st October, 2019>

 - End Header --------------------------------------------------------*/


#pragma once
#include "Component.h"
class GameObject;
class Event;
class Transform;
class Body;

class UpDown : public Component
{
public:
	UpDown();
	~UpDown();
	void Serialize(FILE** fpp);

	void Update();
	bool IsGoingUp() 
	{ 
		return mGoingUp; 
	}

	void HandleEvent(Event* pEvent);
	void Initialize();

	//GameObject* mpOwner;
	int mTimer;
	bool mGoingUp;

	//For Timer Based Attacking
	float delayStartBullet;
	float delayStartGrenade;

	//Bullet / Grenade Req
	Transform* mpTransform;
	Body* pBody;
};


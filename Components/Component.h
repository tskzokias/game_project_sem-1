/* Start Header -------------------------------------------------------

  Copyright (C) 2019 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.

File Name:  <Component.h>
Purpose:  <Header File for Base Class(purely virtual class), inherited by all the other components(Sprite, Controller, Transform, UpDown>
Language:  <C, C++, SDL - Compilers provided by MSVS2019>
Platform: <MSVS2019, Windows 10>
Project: <Student Login - taksh.goyal, Class - CS 529, Assignment - CS529_Final_Project>
Author:  <Name - Taksh Goyal, Student Login - taksh.goyal, Student ID - 60001319>
Creation date: <31st October, 2019>

 - End Header --------------------------------------------------------*/


#pragma once
#include "stdio.h"
//#include "..\Manager\EventManager.h" // no include when forward declaring classes

class GameObject;
class Event;

enum class COMPONENT_TYPE
{
	COMPONENT_TRANSFORM,
	COMPONENT_SPRITE,
	COMPONENT_CONTROLLER,
	COMPONENT_UP_DOWN, 
	COMPONENT_BODY,
};

class Component
{
public:
	Component()
	{
		mpOwner = nullptr;
	}
	Component(COMPONENT_TYPE type);
	virtual ~Component();
	virtual void Serialize(FILE** fpp) = 0;
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void HandleEvent(Event* pEvent) = 0;

	COMPONENT_TYPE GetType() const
	{ 
 		return mType; 
	}
	GameObject* GetOwner() const 
	{
		return mpOwner; 
	}
	void SetOwner(GameObject* owner)
	{ 
		mpOwner = owner; 
	}

public:
	COMPONENT_TYPE mType;
	GameObject* mpOwner;
	//bool OneTimeOnly;
};
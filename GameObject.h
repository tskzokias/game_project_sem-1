/* Start Header -------------------------------------------------------

  Copyright (C) 2019 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.

File Name:  <GameObject.h>
Purpose:  <Header File for Handling Game Objects made, Adding all necessary components >
Language:  <C, C++, SDL - Compilers provided by MSVS2019>
Platform: <MSVS2019, Windows 10>
Project: <Student Login - taksh.goyal, Class - CS 529, Assignment - CS529_Final_Project>
Author:  <Name - Taksh Goyal, Student Login - taksh.goyal, Student ID - 60001319>
Creation date: <31st October, 2019>

 - End Header --------------------------------------------------------*/


#pragma once

#include <vector>
#include "Components/Component.h"

class Component;

class Event;

class GameObject
{

public:
	GameObject();
	~GameObject();

	void Update();
	Component* GetComponent(COMPONENT_TYPE type);
	Component* AddComponent(COMPONENT_TYPE type);
	std::vector <Component*> mComponents;
	void HandleEvent(Event* pEvent);
	void Initialize();

public:
	bool IfActiveFlag;
};


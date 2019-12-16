/* Start Header -------------------------------------------------------

  Copyright (C) 2019 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.

File Name:  <PhysicsManager.cpp>
Purpose:  <Implements Physics required in the GAME>
Language:  <C, C++, SDL - Compilers provided by MSVS2019>
Platform: <MSVS2019, Windows 10>
Project: <Student Login - taksh.goyal, Class - CS 529, Assignment - CS529_Final_Project>
Author:  <Name - Taksh Goyal, Student Login - taksh.goyal, Student ID - 60001319>
Creation date: <17th October, 2019>

 - End Header --------------------------------------------------------*/
#pragma once
#include "..\include_sdl\SDL.h"
#include "EventManager.h"
class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	void Update(float);

public:
	float delayStartMaxX; // Right Side
	float delayStartMinX; // Left Side
};

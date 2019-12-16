/* Start Header -------------------------------------------------------

  Copyright (C) 2019 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.

File Name:  <Transform.cpp>
Purpose:  <Implements Model(OpenGL transformations, positions related) required in the GAME>
Language:  <C, C++, SDL - Compilers provided by MSVS2019>
Platform: <MSVS2019, Windows 10>
Project: <Student Login - taksh.goyal, Class - CS 529, Assignment - CS529_Final_Project>
Author:  <Name - Taksh Goyal, Student Login - taksh.goyal, Student ID - 60001319>
Creation date: <17th October, 2019>

 - End Header --------------------------------------------------------*/
#pragma once

#include "Component.h"
#include "..\Math\glm\glm.hpp"
#include "..\Math\glm\gtc\matrix_transform.hpp"

class Transform : public Component
{
public: // Member Functions, Getter Setter
	Transform();
	~Transform();
	void Serialize(FILE** fpp);

	void Update();
	void UpdatePosition(float dx, float dy);
	void Initialize();
	float GetPosX()
	{
		return mPosX;
	}

	float GetPosY()
	{
		return mPosY;
	}

	void HandleEvent(Event* pEvent) {}
	void Rotate(float angle);

public: // Data members
	float mPosX;
	float mPosY;
	float currentangle;
	float mScaleX, mScaleY;
	glm::mat4 Model;
	glm::mat4 Proj;
};


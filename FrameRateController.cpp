/* Start Header -------------------------------------------------------

  Copyright (C) 2019 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.

File Name:  <FrameRateController.cpp>
Purpose:  <Implementation of the header file FrameRateController.h - Controlling FrameRate>
Language:  <C, C++, SDL - Compilers provided by MSVS2019>
Platform: <MSVS2019, Windows 10>
Project: <Student Login - taksh.goyal, Class - CS 529, Assignment - CS529_Final_Project>
Author:  <Name - Taksh Goyal, Student Login - taksh.goyal, Student ID - 60001319>
Creation date: <17th October, 2019>

 - End Header --------------------------------------------------------*/


#include "FrameRateController.h"
#include "include\include_sdl\SDL_timer.h"
#include "limits.h"

FrameRateController::FrameRateController(Uint8 MaxFrameRate)
{
	if (0 == MaxFrameRate)
	{
		MaxFrameRate = UINT_MAX;
	}

	mMaxFrameRate = MaxFrameRate;
	mTicksPerFrame = 1000 / mMaxFrameRate;

	mTickStart = 0;
	mTickEnd = 0;
	mFrameTime = 0;
}

FrameRateController::~FrameRateController()
{

}

void FrameRateController::FrameStart()
{
	mTickStart = SDL_GetTicks();
}

 void FrameRateController::FrameEnd()
{
	mTickEnd = SDL_GetTicks();

	while( (mTickEnd - mTickStart) < mTicksPerFrame)
		mTickEnd = SDL_GetTicks();

	mFrameTime = mTickEnd - mTickStart;
}
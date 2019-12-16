/* Start Header -------------------------------------------------------

  Copyright (C) 2019 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.

File Name:  <FrameRateController.h>
Purpose:  <Header file for implementation of class with frame rate controlling capabilities>
Language:  <C, C++, SDL - Compilers provided by MSVS2019>
Platform: <MSVS2019, Windows 10>
Project: <Student Login - taksh.goyal, Class - CS 529, Assignment - CS529_Final_Project>
Author:  <Name - Taksh Goyal, Student Login - taksh.goyal, Student ID - 60001319>
Creation date: <17th October, 2019>

 - End Header --------------------------------------------------------*/


#pragma once
#include "include\include_sdl\SDL_stdinc.h"

class FrameRateController
{
public:
	FrameRateController(Uint8 MaxFrameRate);
	~FrameRateController();

	Uint32 FrameTime() { return mFrameTime; }

	void FrameStart();
	void FrameEnd();


private:
	Uint32 mTickStart;
	Uint32 mTickEnd;
	Uint32 mMaxFrameRate;
	Uint32 mTicksPerFrame;
	Uint32 mFrameTime;

};
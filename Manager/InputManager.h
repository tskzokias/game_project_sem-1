/* Start Header -------------------------------------------------------

  Copyright (C) 2019 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.

File Name:  <InputManager.h>
Purpose:  <Header File for Movement Based Input Handling/Basic Declaration>
Language:  <C, C++, SDL - Compilers provided by MSVS2019>
Platform: <MSVS2019, Windows 10>
Project: <Student Login - taksh.goyal, Class - CS 529, Assignment - CS529_Final_Project>
Author:  <Name - Taksh Goyal, Student Login - taksh.goyal, Student ID - 60001319>
Creation date: <17th October, 2019>

 - End Header --------------------------------------------------------*/

#pragma once
#include "..\include\include_sdl\SDL.h"
class InputManager
{
public:

	InputManager();
	~InputManager();

	void Update();

	bool IsKeyPressed(unsigned int KeyScanCode);
	bool IsKeyReleased(unsigned int KeyScanCode);
	bool IsKeyTriggered(unsigned int KeyScanCode);


private:

	Uint8 mCurrentKeyStates[512];
	Uint8 mPreviousKeyStates[512];

};


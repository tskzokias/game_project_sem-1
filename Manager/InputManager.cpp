/* Start Header -------------------------------------------------------

  Copyright (C) 2019 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.

File Name:  <InputManager.cpp>
Purpose:  <Implements Movement based controls required in the GAME>
Language:  <C, C++, SDL - Compilers provided by MSVS2019>
Platform: <MSVS2019, Windows 10>
Project: <Student Login - taksh.goyal, Class - CS 529, Assignment - CS529_Final_Project>
Author:  <Name - Taksh Goyal, Student Login - taksh.goyal, Student ID - 60001319>
Creation date: <17th October, 2019>

 - End Header --------------------------------------------------------*/

#include "InputManager.h"
#include "..\include\include_sdl\SDL_scancode.h"
#include "memory.h"
#include <iostream>


InputManager::InputManager()
{
	memset(mCurrentKeyStates, 0, 512 * sizeof(Uint8));
	memset(mPreviousKeyStates, 0, 512 * sizeof(Uint8));
}


InputManager:: ~InputManager()
{

}

bool InputManager::IsKeyPressed(unsigned int KeyScanCode)
{
	if (KeyScanCode > 512) // check
		return false;

	if (mCurrentKeyStates[KeyScanCode])
		return true;

	return false;
}

bool InputManager::IsKeyTriggered(unsigned int KeyScanCode)
{
	if (KeyScanCode > 512) // check
		return false;

	if (mCurrentKeyStates[KeyScanCode] && !mPreviousKeyStates[KeyScanCode])
		return true;

	return false;
}



bool InputManager::IsKeyReleased(unsigned int KeyScanCode)
{
	if (KeyScanCode > 512)
		return false;

	if (!mCurrentKeyStates[KeyScanCode] && mPreviousKeyStates[KeyScanCode])
		return true;

	return false;
}


void InputManager::Update()
{
	memcpy(mPreviousKeyStates, mCurrentKeyStates, 512);

	// get keyboard states.
	int fetchedNum = 0;
	const Uint8* currentkeystates = SDL_GetKeyboardState(&fetchedNum);

	if (fetchedNum > 512)
		fetchedNum = 512;

	memcpy(mCurrentKeyStates, currentkeystates, 512 * sizeof(Uint8));
}
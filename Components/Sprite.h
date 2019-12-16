/* Start Header -------------------------------------------------------

  Copyright (C) 2019 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.

File Name:  <Sprite.h>
Purpose:  <Header File for loading the image to the surface from Resources folder>
Language:  <C, C++, SDL - Compilers provided by MSVS2019>
Platform: <MSVS2019, Windows 10>
Project: <Student Login - taksh.goyal, Class - CS 529, Assignment - CS529_Final_Project>
Author:  <Name - Taksh Goyal, Student Login - taksh.goyal, Student ID - 60001319>
Creation date: <31st October, 2019>

 - End Header --------------------------------------------------------*/

#pragma once
#include "Component.h"
#include <string>
#include "..\glew.h"

struct SDL_Surface;

class Sprite : public Component
{
public:
	Sprite();
	~Sprite();

	void Update();

	void Serialize(FILE** fpp);
	void HandleEvent(Event* pEvent) {}
	SDL_Surface* GetSurface()
	{
		return mpSurface;
	}

	void SetSurface(SDL_Surface* surface)
	{
		mpSurface = surface;
	}
	void Initialize();

public:
	std::string fullpath;
	SDL_Surface* mpSurface;
	unsigned int surface;
};


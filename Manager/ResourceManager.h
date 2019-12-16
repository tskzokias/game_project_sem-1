/* Start Header -------------------------------------------------------

  Copyright (C) 2019 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.

File Name:  <ResourceManager.h>
Purpose:  <Basic declaration of the header file implemented by cpp file for handling various resources>
Language:  <C, C++, SDL - Compilers provided by MSVS2019>
Platform: <MSVS2019, Windows 10>
Project: <Student Login - taksh.goyal, Class - CS 529, Assignment - CS529_Final_Project>
Author:  <Name - Taksh Goyal, Student Login - taksh.goyal, Student ID - 60001319>
Creation date: <17th October, 2019>

 - End Header --------------------------------------------------------*/

#pragma once
#include "..\include\include_sdl\SDL_surface.h"
#include "unordered_map"

struct SDL_Surface;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	SDL_Surface* LoadSurface(const char* pFilePath);
	unsigned int UploadTextures(const char* c_FilePath);
	unsigned int LoadTextures(const char* c_FilePath);

	std::unordered_map<std::string, SDL_Surface*> mSurfaces;
	std::unordered_map<std::string, unsigned int> mTextures;

	unsigned int GetTextureID(const char* c_FilePath);
};


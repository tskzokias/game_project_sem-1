/* Start Header -------------------------------------------------------

  Copyright (C) 2019 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.

File Name:  <ResourceManager.cpp>
Purpose:  <For managing the cleaning/freeing of the SDL_Surface* pointers> 
Language:  <C, C++, SDL - Compilers provided by MSVS2019>
Platform: <MSVS2019, Windows 10>
Project: <Student Login - taksh.goyal, Class - CS 529, Assignment - CS529_Final_Project>
Author:  <Name - Taksh Goyal, Student Login - taksh.goyal, Student ID - 60001319>
Creation date: <17th October, 2019>

 - End Header --------------------------------------------------------*/
#define STB_IMAGE_IMPLEMENTATION
#include "ResourceManager.h"
//#include "..\include\include_sdl\SDL.h"
#include "..\include\glew.h"
#include "..\include\stb_image.h"
#include <iostream>

ResourceManager::ResourceManager()
{

}
ResourceManager ::~ResourceManager()
{
	for (auto element : mSurfaces)
		SDL_FreeSurface(element.second);  // element defined in main, please check for implementation

	mSurfaces.clear();
}

SDL_Surface* ResourceManager::LoadSurface(const char* pFilePath)
{
	SDL_Surface* pSurface = mSurfaces[pFilePath];

	if (nullptr != pSurface)
		return pSurface;

	pSurface = SDL_LoadBMP(pFilePath);
	if (nullptr != pSurface)
		mSurfaces[pFilePath] = pSurface;

	return pSurface;
}

unsigned int ResourceManager::LoadTextures(const char* c_FilePath)
{
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

	unsigned char* data = stbi_load(c_FilePath, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	return texture1;
}

unsigned int ResourceManager::GetTextureID(const char* c_FilePath)
{
	int id = UploadTextures(c_FilePath);
	return id;
}

unsigned int ResourceManager :: UploadTextures(const char* c_FilePath)
{
	unsigned int pTextures = mTextures[c_FilePath];

	if (NULL != pTextures)
		return pTextures;
	
	pTextures = LoadTextures(c_FilePath);
	if (NULL != pTextures)
		mTextures[c_FilePath] = pTextures;

	return pTextures;
}
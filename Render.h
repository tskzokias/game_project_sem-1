/* Start Header -------------------------------------------------------

  Copyright (C) 2019 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.

File Name:  <Body.cpp>
Purpose:  <Implements OpenGL drawing on the screen/ Loading Shaders and working with them>
Language:  <C, C++, SDL - Compilers provided by MSVS2019>
Platform: <MSVS2019, Windows 10>
Project: <Student Login - taksh.goyal, Class - CS 529, Assignment - CS529_Final_Project>
Author:  <Name - Taksh Goyal, Student Login - taksh.goyal, Student ID - 60001319>
Creation date: <17th November, 2019>

 - End Header --------------------------------------------------------*/
#pragma once
#include "Math/glm/glm.hpp"
#include "Math/glm/gtc/type_ptr.hpp"
#include <string>
class Render
{
public:
	void Initialize();
	void Draw();
	Render();
	~Render();
	void Bind();
	void Unbind();
	bool LoadShaders(std::string vs, std::string fs, int& ProgramId);
	std::string LoadTextFromFile(std::string path);

	glm::mat4 Proj;
	int ProgramId;
	unsigned int VBO, VertexArrayID, EBO;
	bool mode;
};


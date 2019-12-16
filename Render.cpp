#include "include/glew.h"
#include "Render.h"
#include "Math/glm/glm.hpp"
#include "Manager/InputManager.h"
#include "Math/glm/gtc/type_ptr.hpp"
#include "Components/Transform.h"
#include "Components/Sprite.h"
#include "Manager/GameObjectManager.h"
#include "GameObject.h"
#include <iostream>
#include <fstream>

extern GameObjectManager* gpGameObjectManager;
extern InputManager* gpInputManager;

Render::Render()
{
	Proj = glm::mat4(1.0f);
	ProgramId = NULL;
	VBO = VertexArrayID = EBO = NULL;
	mode = false;
}

Render::~Render()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VertexArrayID);
}

void Render::Initialize()
{
	float vertices[32] = {
		// positions              // colors                // texture coords
		0.0f,  1.0f, 0.0f,        1.0f, 0.0f, 0.0f,        0.0f, 0.0f,
		1.0f,  0.0f, 0.0f,        0.0f, 1.0f, 0.0f,        1.0f, 1.0f,
		0.0f,  0.0f, 0.0f,        0.0f, 0.0f, 1.0f,        1.0f, 0.0f,
		1.0f,  1.0f, 0.0f,        1.0f, 1.0f, 1.0f,        0.0f, 1.0f
	};

	unsigned int indices[6] = {
		0, 1, 2, // first triangle
		0, 3, 1	 // second triangle
	};

	Proj = glm::mat4(1.0);
	Proj = glm::ortho(0.0f, 1024.0f, 768.0f, 0.0f, -1.0f, 1.0f);

	//int ProgramId;

	glGenVertexArrays(1, &VertexArrayID);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);  

	glBindVertexArray(VertexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	LoadShaders("VertexShader.vs", "FragmentShader.fs", ProgramId);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Render::Bind()
{
	glUseProgram(ProgramId);
	glBindVertexArray(VertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void Render::Draw()
{
	//Drawing all the present Game Objects
	for (auto go : gpGameObjectManager->GetGameObjects())
	{

		Transform* pTransform = static_cast<Transform*>(go->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
		Sprite* pSprite = static_cast<Sprite*>(go->GetComponent(COMPONENT_TYPE::COMPONENT_SPRITE));

		if (pSprite != nullptr && pTransform != nullptr)
		{
			unsigned int projLoc = glGetUniformLocation(ProgramId, "projection");
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pTransform->Proj));

			unsigned int ModelLoc = glGetUniformLocation(ProgramId, "Model");
			glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(pTransform->Model));

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, pSprite->surface);

			glUniform1i(glGetUniformLocation(ProgramId, "texture1"), 0);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			/*if (gpInputManager->IsKeyTriggered(SDL_SCANCODE_BACKSPACE))
			{
				mode = !mode;

				if (mode == true)
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				}
				else if (mode == false)
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				}
			}*/
		}

	}
	if (gpInputManager->IsKeyTriggered(SDL_SCANCODE_BACKSPACE))
	{
		for (auto go : gpGameObjectManager->GetGameObjects())
		{
			Transform* pTransform = static_cast<Transform*>(go->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
			Sprite* pSprite = static_cast<Sprite*>(go->GetComponent(COMPONENT_TYPE::COMPONENT_SPRITE));

			//Collider instead of Shape Logic
			//pTransform->mPosX = pTransform->mScaleX;
			//pTransform->mPosY = pTransform->mScaleY;

			//glm::mat4 Model = glm::mat4(1.0f);
			/*pTransform->mPosX = ;
			pTransform->mPosY = ;*/
			//Model = glm::scale(Model, glm::vec3(pTransform->mScaleX, pTransform->mScaleY, 1.0f));
			//Model = glm::translate(Model, glm::vec3(pTransform->mPosX, pTransform->mPosY, 0.0f));

			if (pSprite != nullptr && pTransform != nullptr)
			{
				unsigned int projLoc = glGetUniformLocation(ProgramId, "projection");
				glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pTransform->Proj));

				unsigned int ModelLoc = glGetUniformLocation(ProgramId, "Model");
				glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(pTransform->Model));

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, pSprite->surface);

				glUniform1i(glGetUniformLocation(ProgramId, "texture1"), 0);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

				mode = !mode;

				//glDisable(GL_BLEND);

				if (mode == true)
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				}
				else if (mode == false)
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				}
			}
		}
	}
}

void Render::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

bool Render:: LoadShaders(std::string vs, std::string fs, int& ProgramId)
{
	bool fail = 0;

	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vShaderCode;
	std::string fShaderCode;

	vShaderCode = LoadTextFromFile(vs);
	// can check for error later 

	fShaderCode = LoadTextFromFile(fs);
	// can check for error later 

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// compiling vs 
	const char* VertexSourcePointer = vShaderCode.c_str();
	std::cout << VertexSourcePointer;
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader 
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector < char > VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf(" % s\n", &VertexShaderErrorMessage[0]);
	}

	char const* FragmentSourcePointer = fShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader 
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector < char > FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf(" % s\n", &FragmentShaderErrorMessage[0]);
	}

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderID);
	glAttachShader(ProgramId, FragmentShaderID);
	glLinkProgram(ProgramId);

	// Check the program 
	glGetProgramiv(ProgramId, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector <char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramId, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf(" % s\n", &ProgramErrorMessage[0]);
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	return fail;
}

std::string Render :: LoadTextFromFile(std::string path)
{
	std::ifstream sourceFile(path.c_str(), std::ios::in);
	if (sourceFile.is_open())
	{
		std::string content;
		content.assign((std::istreambuf_iterator <char>(sourceFile)), std::istreambuf_iterator <char>());
		sourceFile.close();
		return content;
	}
	else
	{
		return "error";
	}
}
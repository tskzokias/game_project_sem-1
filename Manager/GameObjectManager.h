/* Start Header -------------------------------------------------------

  Copyright (C) 2019 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.

File Name:  <GameObjectManager.h>
Purpose:  <Header File for Handling the number and types of Game Objects made >
Language:  <C, C++, SDL - Compilers provided by MSVS2019>
Platform: <MSVS2019, Windows 10>
Project: <Student Login - taksh.goyal, Class - CS 529, Assignment - CS529_Final_Project>
Author:  <Name - Taksh Goyal, Student Login - taksh.goyal, Student ID - 60001319>
Creation date: <31st October, 2019>

 - End Header --------------------------------------------------------*/

#pragma once
#include <vector>

class GameObject;

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void AddGameObject(GameObject* pGameObject);
	std::vector<GameObject*> GetGameObjects();
	std::vector<GameObject*> mGameObjects;

private:
	

};


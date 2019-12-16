/* Start Header -------------------------------------------------------

  Copyright (C) 2019 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.

File Name:  <Main.cpp>
Purpose:  <Takes in all header header files and completes their definiton and uses them>
Language:  <C, C++, SDL - Compilers provided by MSVS2019>
Platform: <MSVS2019, Windows 10>
Project: <Student Login - taksh.goyal, Class - CS 529, Assignment - CS529_Final_Project>
Author:  <Name - Taksh Goyal, Student Login - taksh.goyal, Student ID - 60001319>
Creation date: <31st October, 2019>

 - End Header --------------------------------------------------------*/

#include "stdio.h"
#include "GameObject.h"
#include "include/glew.h"
#include "Components/Sprite.h"
#include "Components\UpDown.h"
#include "Components\Transform.h"
#include "Manager/PhysicsManager.h"
#include "include\include_sdl\SDL.h"
#include "include\include_sdl\SDL_opengl.h"
#include "include/sound_include/irrKlang.h"
#include "Manager\GameObjectManager.h"
#include "Manager\CollisionManager.h"
#include "Manager\ResourceManager.h"
#include "Components\Controller.h"
#include "Manager/EventManager.h"
#include "Manager\InputManager.h"
#include "FrameRateController.h"
#include "ObjectFactory.h"
#include "Render.h"
//#include "Components\Body.h"

#include "fstream"
#include <iostream>

//#define IMG_SPEED 10.0f

InputManager* gpInputManager;
PhysicsManager* gpPhysicsManager;
ResourceManager* gpResourceManager;
GameObjectManager* gpGameObjectManager;
FrameRateController* gpFrameRateController;
CollisionManager* gpCollisionManager;
EventManager* gpEventManager;
Controller* gpController;
Sprite* gpSprite;

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

#pragma comment(lib, "legacy_stdio_definitions.lib")

using namespace irrklang;

void DeleteGameObject();

int main(int argc, char* args[])
{
	SDL_Window *pWindow;
	SDL_Surface* pWindowSurface;
	int GameObjectsCount = 0;

	gpInputManager = new InputManager();
	gpPhysicsManager = new PhysicsManager();
	gpResourceManager = new ResourceManager();
	gpGameObjectManager = new GameObjectManager();
	gpFrameRateController = new FrameRateController(60);
	gpCollisionManager = new CollisionManager();
	gpEventManager = new EventManager();
	gpController = new Controller();
	gpSprite = new Sprite();

	ISoundEngine *SoundEngine = createIrrKlangDevice();

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	glewExperimental = GL_TRUE;

	SDL_GLContext maincontext;

	int error = 0;
	bool appIsRunning = true;

	// Initialize SDL
	if((error = SDL_Init( SDL_INIT_VIDEO )) < 0 )
	{
		printf("Couldn't initialize SDL, error %i\n", error);
		return 1;
	}

	// glew
	pWindow = SDL_CreateWindow("1S_Game_Window",		// window title
		SDL_WINDOWPOS_UNDEFINED,					// initial x position
		SDL_WINDOWPOS_UNDEFINED,					// initial y position
		1024,										// width, in pixels
		768,										// height, in pixels
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);



	// Check that the window was successfully made
	if (NULL == pWindow)
	{
		// In the event that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	pWindowSurface = SDL_GetWindowSurface(pWindow); //pWindowSurface initialised

	maincontext = SDL_GL_CreateContext(pWindow);
	if (glewInit() != GLEW_OK)
	{
		printf("\n GLEW Failed");
	}

	SDL_GL_MakeCurrent(pWindow, maincontext);
	SDL_GL_SetSwapInterval(1);

	Render* pRender = new Render();
	pRender->Initialize();

	ObjectFactory* pObjectFactory = new ObjectFactory();
	ObjectFactory* pObjectFactory1 = new ObjectFactory();

	pObjectFactory->LoadLevel("Resources/Level1.txt");
	SoundEngine->play2D("Resources/Audio_Files/Savage.mp3", GL_TRUE); // Uncomment/comment to play/stop Background Music
	//pObjectFactory1->LoadObject("Resources/Menu123.txt");

	GameObject* GameScreen;
	GameScreen = new GameObject();

	GameScreen->AddComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM);
	Transform* GameScreenTr = static_cast<Transform*>(GameScreen->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
	GameScreenTr->Initialize();
	GameScreenTr->mPosX = 0.0f;
	GameScreenTr->mPosY = 768.0f;
	GameScreenTr->mScaleX = 1024.0f;
	GameScreenTr->mScaleY = 768.0f;

	GameScreen->AddComponent(COMPONENT_TYPE::COMPONENT_SPRITE);
	Sprite* GameSprite = static_cast<Sprite*>(GameScreen->GetComponent(COMPONENT_TYPE::COMPONENT_SPRITE));
	GameSprite->fullpath = "Resources/Control_Page123.png";
	GameSprite->surface = gpResourceManager->GetTextureID(GameSprite->fullpath.c_str());

	gpGameObjectManager->AddGameObject(GameScreen);

	int endscreencounter = 0;
	
	// Game loop
	while(true == appIsRunning)
	{
		gpFrameRateController->FrameStart();
		float frameTime = gpFrameRateController->FrameTime();

		glEnable(GL_TEXTURE_2D);  // Enable Texture Mapping ( NEW )
		glShadeModel(GL_SMOOTH);  // Enable Smooth Shading
		
		glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Trying Blend with transparency
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations
		
		SDL_Event e;
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				appIsRunning = false;
			}

		}

		gpInputManager->Update();

		if (gpInputManager->IsKeyTriggered(SDL_SCANCODE_RETURN))
		{
			//GameStart = true;
			GameScreen->IfActiveFlag = false;
		}

		if (gpInputManager->IsKeyReleased(SDL_SCANCODE_ESCAPE)) // Press Escape to close the window
		{
			GameObject* GameScreen;
			GameScreen = new GameObject();

			GameScreen->AddComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM);
			Transform* GameScreenTr = static_cast<Transform*>(GameScreen->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
			GameScreenTr->Initialize();
			GameScreenTr->mPosX = 0.0f;
			GameScreenTr->mPosY = 768.0f;
			GameScreenTr->mScaleX = 1024.0f;
			GameScreenTr->mScaleY = 768.0f;

			GameScreen->AddComponent(COMPONENT_TYPE::COMPONENT_SPRITE);
			Sprite* GameSprite = static_cast<Sprite*>(GameScreen->GetComponent(COMPONENT_TYPE::COMPONENT_SPRITE));
			GameSprite->fullpath = "Resources/Game_OverRev.png";
			GameSprite->surface = gpResourceManager->GetTextureID(GameSprite->fullpath.c_str());

			gpGameObjectManager->AddGameObject(GameScreen);

			++endscreencounter;

			if(endscreencounter >= 40.0f)
				appIsRunning = false;
		}
		pRender->Bind();

		pRender->Draw();

		pRender->Unbind();


		gpPhysicsManager->Update(frameTime);
		gpEventManager->Update(frameTime);
		
		//Update All Game Objects
		for (auto go : gpGameObjectManager->GetGameObjects())
		{
			go->Update();
 			GameObjectsCount = gpGameObjectManager->mGameObjects.size();
			//Body* pBo = static_cast<Body*>(go->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));
			if (GameObjectsCount == 2 /*|| pBo->mMass == 1.0f*/) //Win Condition
			{
				GameObject* GameScreen;
				GameScreen = new GameObject();

				GameScreen->AddComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM);
				Transform* GameScreenTr = static_cast<Transform*>(GameScreen->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
				GameScreenTr->Initialize();
				GameScreenTr->mPosX = 0.0f;
				GameScreenTr->mPosY = 768.0f;
				GameScreenTr->mScaleX = 1024.0f;
				GameScreenTr->mScaleY = 768.0f;

				GameScreen->AddComponent(COMPONENT_TYPE::COMPONENT_SPRITE);
				Sprite* GameSprite = static_cast<Sprite*>(GameScreen->GetComponent(COMPONENT_TYPE::COMPONENT_SPRITE));
				GameSprite->fullpath = "Resources/Control_Page123Exit.png";
				GameSprite->surface = gpResourceManager->GetTextureID(GameSprite->fullpath.c_str());

				gpGameObjectManager->AddGameObject(GameScreen);
			}
		}


	
		SDL_GL_SwapWindow(pWindow);

		gpFrameRateController->FrameEnd();

		//Delete Out of Bound GameObjects Logic
		DeleteGameObject();
	}

	// Close and destroy the window
	SDL_DestroyWindow(pWindow);
	SDL_GL_DeleteContext(maincontext);
	delete(gpResourceManager);
	delete(gpInputManager);
	delete(gpFrameRateController);
	delete(gpGameObjectManager);
	delete(gpPhysicsManager);
	delete(gpCollisionManager);
	delete(gpEventManager);
	delete(pObjectFactory);
	SDL_FreeSurface(pWindowSurface);
	delete(pRender);

	// Quit SDL subsystems
	SDL_Quit();
	

	return 0;
}

void DeleteGameObject()
{
	std::vector<GameObject*>::iterator it;
	for (it = gpGameObjectManager->mGameObjects.begin(); it != gpGameObjectManager->mGameObjects.end();)
	{
		if ((*it)->IfActiveFlag == false )
		{
			GameObject* tempObj = (*it);
			it = gpGameObjectManager->mGameObjects.erase(it);
			delete tempObj;
		}
		else
			++it;
	}
}
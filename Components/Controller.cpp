#include "Body.h"
#include "Sprite.h"
#include <iostream>
#include "Transform.h"
#include "Controller.h"
#include "..\GameObject.h"
#include "..\include\glew.h"
#include "..\Manager\InputManager.h"
#include "../Manager/ResourceManager.h"
#include "..\Manager\GameObjectManager.h"
#include "../include/sound_include/irrKlang.h"
#include "..\include\include_sdl\SDL_scancode.h"

using namespace irrklang;

#define IMG_SPEED 200

extern InputManager* gpInputManager;
extern GameObjectManager* gpGameObjectManager;
extern ResourceManager* gpResourceManager;
ISoundEngine* SoundEngine = createIrrKlangDevice();

Controller::Controller() : Component(COMPONENT_TYPE::COMPONENT_CONTROLLER)
{
	mpOwner = nullptr;
	//OneTimeOnly = true;
}

Controller::~Controller()
{
	
}

void Controller::Update()
{
	//OneTimeOnly = true;
	Transform* mpTransform = static_cast<Transform*>(this->GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
	Body* pBody = static_cast<Body*>(this->GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));

	if (nullptr != mpTransform && nullptr != pBody)
	{
		if (gpInputManager->IsKeyPressed(SDL_SCANCODE_W) && nullptr != pBody)
		{
			pBody->AddVelocity(0.0f, -IMG_SPEED*1.6f);
		}
		if (gpInputManager->IsKeyPressed(SDL_SCANCODE_S) && nullptr != pBody)
		{
			pBody->AddVelocity(0.0f, IMG_SPEED);
		}
		if (gpInputManager->IsKeyPressed(SDL_SCANCODE_A) && nullptr != pBody)
		{			
			pBody->AddVelocity(-IMG_SPEED, pBody->mVelY);
		}
		if (gpInputManager->IsKeyPressed(SDL_SCANCODE_D) && nullptr != pBody)
		{
			pBody->AddVelocity(IMG_SPEED, pBody->mVelY);
		}
		if (gpInputManager->IsKeyPressed(SDL_SCANCODE_Q) && nullptr != mpTransform)
		{
			mpTransform->Rotate(-3.0f);
		}
		if (gpInputManager->IsKeyPressed(SDL_SCANCODE_E) && nullptr != mpTransform)
		{
			mpTransform->Rotate(+3.0f);
		}
		if (gpInputManager->IsKeyTriggered(SDL_SCANCODE_SPACE))
		{
			//Going According to How we proceed in a .txt file
			GameObject* Bullet;
			Bullet = new GameObject();
			//Bullet->IfActiveFlag = true;

			//First Transform
			Bullet->AddComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM);
			Transform* BulletTr = static_cast<Transform*>(Bullet->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
			BulletTr->Initialize();
			BulletTr->mPosX = mpTransform->mPosX + 80.0f;
			BulletTr->mPosY = mpTransform->mPosY - 70.0f;
			BulletTr->Model = mpTransform->Model;
			BulletTr->currentangle = mpTransform->currentangle;
			BulletTr->mScaleX = 25.0f;
			BulletTr->mScaleY = -7.0f;

			//Second Sprite
			Bullet->AddComponent(COMPONENT_TYPE::COMPONENT_SPRITE);
			Sprite* BulletSprite = static_cast<Sprite*>(Bullet->GetComponent(COMPONENT_TYPE::COMPONENT_SPRITE));
			BulletSprite->fullpath = "Resources/Bullet.png";
			BulletSprite->surface = gpResourceManager->GetTextureID(BulletSprite->fullpath.c_str());

			//Since controlled by the player itself, so no controller or updown

			//Third Body
			Bullet->AddComponent(COMPONENT_TYPE::COMPONENT_BODY);
			Body* BulletBody = static_cast<Body*>(Bullet->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));
			BulletBody->mMass = 2.0f;
			BulletBody->mPosX = pBody->mPosX + 80.0f;
			BulletBody->mPosY = pBody->mPosY - 80.0f;

			//Fourth Shape(Part of Third only)
			BulletBody->mpShape = new ShapeAABB();
			BulletBody->mpShape->mpOwnerBody = BulletBody;
			ShapeAABB* pAABB = static_cast<ShapeAABB*>(BulletBody->mpShape);
			pAABB->mWidth = 15.0f;
			pAABB->mHeight = 5.0f;

			//Add velocity for it to be fired in x dir
			BulletBody->AddVelocity(IMG_SPEED * 6, 0.0f);

			SoundEngine->play2D("Resources/Audio_Files/Fire_Sound.mp3", GL_FALSE);

			//Add to GameObjectManager since it does the launching of all gameobjects in Object Factory and calls all the updates in main
			gpGameObjectManager->AddGameObject(Bullet);
		
		}
		if (gpInputManager->IsKeyTriggered(SDL_SCANCODE_G))
		{
			//Going According to How we proceed in a .txt file
			GameObject* Grenade;
			Grenade = new GameObject();
			//Bullet->IfActiveFlag = true; By default

			//1. Transform
			Grenade->AddComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM);
			Transform* GrenadeTr = static_cast<Transform*>(Grenade->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
			GrenadeTr->Initialize();
			GrenadeTr->mPosX = mpTransform->mPosX + 80.0f;
			GrenadeTr->mPosY = mpTransform->mPosY - 70.0f;
			GrenadeTr->Model = mpTransform->Model;
			GrenadeTr->mScaleX = 30.0f;
			GrenadeTr->mScaleY = 30.0f;

			//2. Sprite
			Grenade->AddComponent(COMPONENT_TYPE::COMPONENT_SPRITE);
			Sprite* GrenadeSprite = static_cast<Sprite*>(Grenade->GetComponent(COMPONENT_TYPE::COMPONENT_SPRITE));
			GrenadeSprite->fullpath = "Resources/CutGrenade.png";
			GrenadeSprite->surface = gpResourceManager->GetTextureID(GrenadeSprite->fullpath.c_str());

			//Since controlled by the player itself, so no controller or updown

			//3. Body
			Grenade->AddComponent(COMPONENT_TYPE::COMPONENT_BODY);
			Body* GrenadeBody = static_cast<Body*>(Grenade->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));
			GrenadeBody->mMass = 3.0f;
			GrenadeBody->mPosX = GrenadeTr->mPosX;
			GrenadeBody->mPosY = GrenadeTr->mPosY;
			//GrenadeBody->mInvMass = 1.0f / GrenadeBody->mMass;

			//Fourth Shape(Part of Third only)
			GrenadeBody->mpShape = new ShapeAABB();
			GrenadeBody->mpShape->mpOwnerBody = GrenadeBody;
			ShapeAABB* pAABB = static_cast<ShapeAABB*>(GrenadeBody->mpShape);
			pAABB->mWidth = 30.0f;
			pAABB->mHeight = 30.0f;

			//Add velocity for it to be fired in x dir
			GrenadeBody->AppliedVelocity(IMG_SPEED*2, 0.0f);

			//SoundEngine->play2D("Resources/Audio_Files/Fire_Sound.mp3", GL_FALSE);

			//Add to GameObjectManager since it does the launching of all gameobjects in Object Factory and calls all the updates in main
			gpGameObjectManager->AddGameObject(Grenade);
		}

	}
}

void Controller::Serialize(FILE** fpp)
{ 
	//mIsPlayer = true;
}

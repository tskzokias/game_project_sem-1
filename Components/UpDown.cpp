#include "Body.h"
#include "UpDown.h"
#include "Sprite.h"
#include "Transform.h"
#include "..\GameObject.h"
#include "..\FrameRateController.h"
#include "..\Manager\EventManager.h"
#include "..\Manager\ResourceManager.h"
#include "..\Manager\GameObjectManager.h"
#include "../include/sound_include/irrKlang.h"

#define IMG_SPEED 200

using namespace irrklang;

extern FrameRateController* gpFrameRateController;
extern EventManager* gpEventManager;
extern ResourceManager* gpResourceManager;
extern GameObjectManager* gpGameObjectManager;
extern ISoundEngine* SoundEngine;

UpDown::UpDown() : Component(COMPONENT_TYPE::COMPONENT_UP_DOWN)
{
	mGoingUp = true;
	mTimer = 1000;
	mpOwner = nullptr;
	delayStartBullet = 0.0f;
	delayStartGrenade = 0.0f;
	mpTransform = nullptr;
	pBody = nullptr;
}

UpDown::~UpDown()
{

}

void UpDown::Initialize()
{
	gpEventManager->Subscribe(EVENT_TYPE::COLLIDE, this->GetOwner());
}

void UpDown::Update()
{
	mTimer -= gpFrameRateController->FrameTime();

	//Incrementing Dely of each weapon component
	delayStartBullet += 1.0f;
	delayStartGrenade += 1.0f;

	if (mTimer < 0)
	{
		mTimer = 1000;
		mGoingUp = !mGoingUp;
	}

	Transform* mpTransform = static_cast<Transform*>(this->GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
	Body* pBody = static_cast<Body*>(this->GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));

	if (nullptr != mpTransform)
	{
		if (true == mGoingUp)
			mpTransform->UpdatePosition(0.0f, 5.0f);

		else
			mpTransform->UpdatePosition(0.0f, -5.0f);
	}

	if (delayStartBullet >= 150.0f)
	{
		if (pBody->mMass == 0.0f)
		{
			//Going According to How we proceed in a .txt file
			GameObject* Bullet; //New Bullet GameObject
			Bullet = new GameObject();
			//Bullet->IfActiveFlag = true;

			//First Transform
			Bullet->AddComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM);
			Transform* BulletTr = static_cast<Transform*>(Bullet->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
			BulletTr->Initialize();
			BulletTr->mPosX = mpTransform->mPosX + 80.0f;
			BulletTr->mPosY = mpTransform->mPosY - 70.0f;
			BulletTr->Model = mpTransform->Model;
			BulletTr->mScaleX = 25.0f;
			BulletTr->mScaleY = 7.0f;

			//Second Sprite
			Bullet->AddComponent(COMPONENT_TYPE::COMPONENT_SPRITE);
			Sprite* BulletSprite = static_cast<Sprite*>(Bullet->GetComponent(COMPONENT_TYPE::COMPONENT_SPRITE));
			BulletSprite->fullpath = "Resources/RevBullet.png";
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
			BulletBody->AddVelocity(-IMG_SPEED * 6, 0.0f);

			SoundEngine->play2D("Resources/Audio_Files/Fire_Sound.mp3", GL_FALSE);

			//Add to GameObjectManager since it does the launching of all gameobjects in Object Factory and calls all the updates in main
			gpGameObjectManager->AddGameObject(Bullet);

			//Reset Timer Bullet
			delayStartBullet = 0.0f;
		}
	}
	if (delayStartGrenade >= 300.0f)
	{
		if (pBody->mMass == 0.5f)
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
			GrenadeBody->mInvMass = 1.0f / GrenadeBody->mMass;

			//Fourth Shape(Part of Third only)
			GrenadeBody->mpShape = new ShapeAABB();
			GrenadeBody->mpShape->mpOwnerBody = GrenadeBody;
			ShapeAABB* pAABB = static_cast<ShapeAABB*>(GrenadeBody->mpShape);
			pAABB->mWidth = 30.0f;
			pAABB->mHeight = 30.0f;

			//Add velocity for it to be fired in x dir
			GrenadeBody->AppliedVelocity(-IMG_SPEED * 2, -IMG_SPEED);

			SoundEngine->play2D("Resources/Audio_Files/Fire_Sound.mp3", GL_FALSE);

			//Add to GameObjectManager since it does the launching of all gameobjects in Object Factory and calls all the updates in main
			gpGameObjectManager->AddGameObject(Grenade);

			//Reset Timer Grenade
			delayStartGrenade = 0.0f;
		}
	}
}

void UpDown::Serialize(FILE** fpp)
{
	int goingUp;
	int time;
	fscanf_s(*fpp, "%i %i\n", &goingUp, &time);

	mGoingUp = (bool)goingUp;
	time = mTimer;
}

void UpDown::HandleEvent(Event* pEvent)
{
	if (pEvent->mEventType == EVENT_TYPE::COLLIDE)
	{
		CollisionEvent* pCollEvent = (CollisionEvent*)pEvent;
		if (pCollEvent->mpObject1 == this->GetOwner() || pCollEvent->mpObject2 == this->GetOwner())
		{
			Transform* pTransform = static_cast<Transform*>(this->GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
			Body* pBody = static_cast<Body*>(this->GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));
			if (nullptr != pTransform && nullptr != pBody)
			{
				pTransform->UpdatePosition(1.0f, 0.0f);
  				pBody->AddVelocity(20.0f, 0.0f);
			}
		}
		printf("%s", "CollisonEventHandled!!\n");
	}
}
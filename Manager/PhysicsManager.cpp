#include "PhysicsManager.h"
#include "..\GameObject.h"
#include "..\Components\Body.h"
#include "GameObjectManager.h"
#include "CollisionManager.h"
#include "..\Components\Transform.h"
#include "EventManager.h"
#include "SDL_timer.h"
#include "..\include\include_sdl\SDL_events.h"
#include "../include/sound_include/irrKlang.h"
#include "SDL_opengl.h"

using namespace irrklang;

extern GameObjectManager* gpGameObjectManager;
extern CollisionManager* gpCollisionManager;
extern EventManager* gpEventManager;
//ISoundEngine* SoundEngine = createIrrKlangDevice();
extern ISoundEngine* SoundEngine; //= createIrrKlangDevice();

PhysicsManager::PhysicsManager()
{
	delayStartMinX = 0.0f;
	delayStartMaxX = 0.0f;
}

PhysicsManager::~PhysicsManager()
{

}

void PhysicsManager::Update(float FrameTime)
{
	for (GameObject* pObj : gpGameObjectManager->GetGameObjects())
	{
		Body* pBo = (Body*)(pObj->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));
		Transform* pTr = (Transform*)(pObj->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
		if (pBo)
			pBo->Integrate(300.0f, FrameTime);

		delayStartMaxX += 1.0f;
		delayStartMinX += 1.0f;

		//To not go Outside Viewport
		if (pTr->mPosX > 923.56f && pBo->mPosX > 923.56f)
		{
			pTr->mPosX = 923.56f;
			pBo->mPosX = 923.56f;
			if (pBo->mMass >= 0.0f && pBo->mMass <= 2.0f) //Bullet Crosses | Logic
			{
				pObj->IfActiveFlag = false;
			}
			if (pBo->mMass == 3.0f) // Grenade Crosses | Takes Time | Logic
			{
				//Since it updates per frame so, "Desi Timer" resets to 0, starts counting to 2000 and boomm....
				if (delayStartMaxX >= 2000.0f) //For Grenade
				{
					SoundEngine->play2D("Resources/Audio_Files/Grenade_Sound.mp3", false);
					pBo->mpShape = new ShapeAABB();
					pBo->mpShape->mpOwnerBody = pBo;
					//Actual Grenade AABB increase for blast
					ShapeAABB* pAABB = static_cast<ShapeAABB*>(pBo->mpShape);
					pAABB->mWidth = 200.0f;
					pAABB->mHeight = -200.0f;
					delayStartMaxX = 0.0f;
					pObj->IfActiveFlag = false;
				}
			}
		}
		else if (pTr->mPosX < 0 && pBo->mPosX < 0)
		{
			pTr->mPosX = 0.0f;
			pBo->mPosX = 0.0f;
			if (pBo->mMass == 2.0f || pBo->mMass == 1.0f) //Bullet Crosses | Logic
			{
				pObj->IfActiveFlag = false;
			}
			if (pBo->mMass == 3.0f) // Grenade Crosses | Takes Time | Logic
			{
				//Since it updates per frame so, "Desi Timer" resets to 0, starts counting to 2000 and boomm....
				if (delayStartMinX >= 2000)
				{
					SoundEngine->play2D("Resources/Audio_Files/Grenade_Sound.mp3", false);
					pBo->mpShape = new ShapeAABB();
					pBo->mpShape->mpOwnerBody = pBo;
					ShapeAABB* pAABB = static_cast<ShapeAABB*>(pBo->mpShape);
					pAABB->mWidth = 200.0f;
					pAABB->mHeight = 200.0f;
					delayStartMinX = 0.0f;
					pObj->IfActiveFlag = false;
				}
			}
		}
		if (pTr->mPosY > 768.0f && pBo->mPosY > 768.0f)
		{
			pTr->mPosY = 768.0f;
		}
		else if (pTr->mPosY < 107.997f && pBo->mPosY <107.997f)
		{
			pTr->mPosY = 107.997f;
		}
	}

	//Reset Previous Contacts
	gpCollisionManager->Reset();

	if (gpGameObjectManager->GetGameObjects().empty() == false)
	{
		auto pObj1 = gpGameObjectManager->mGameObjects.begin();
		auto pObjLast = gpGameObjectManager->mGameObjects.end();

		for (; pObj1 != pObjLast; ++pObj1)
		{
			Body* pBody1 = (Body *)((*pObj1)->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));

			if (nullptr == pBody1)
				continue;

			for (auto pObj2 = pObj1 + 1; pObj2 != pObjLast; ++pObj2)
			{
				Body* pBody2 = (Body*)((*pObj2)->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));

				if (nullptr == pBody2)
					continue;

				bool isCollision = gpCollisionManager->CheckCollisionAndGenerateContact(pBody1->mpShape, pBody1->mPosX, pBody1->mPosY, pBody2->mpShape, pBody2->mPosX, pBody2->mPosY);

				if (isCollision) 
					printf("Collision: %s\n", isCollision ? "true" : "false");
				/*else
				{
					printf("Collision: %s\n", isCollision ? "true" : "false");
				}*/
			}
		}
	}

	for (GameObject* pObj : gpGameObjectManager->GetGameObjects())
	{
		Body* pBo = static_cast<Body *>(pObj->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));
		Transform* pTr = static_cast<Transform *>((Transform*)pObj->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));

		if (nullptr != pBo && nullptr != pTr)
		{
			pBo->mPosX = pTr->mPosX;
			pBo->mPosY = pTr->mPosY;
		}
	}

	for (auto pContact : gpCollisionManager->mContacts)
	{
		CollisionEvent collideEvent;

		collideEvent.mpObject1 = pContact->mBodies[0]->GetOwner();
		collideEvent.mpObject2 = pContact->mBodies[1]->GetOwner();

		gpEventManager->BroadCastEventToSubscribers(&collideEvent);
	}
}
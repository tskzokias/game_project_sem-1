#include "EventManager.h"
#include "GameObjectManager.h"


extern GameObjectManager* gpGameObjectManager;
extern EventManager* gpEventManager;

void EventManager::BroadCastEvent(Event* pEvent)
{
	for (GameObject* pObj : gpGameObjectManager->mGameObjects)
		pObj->HandleEvent(pEvent);
}

void EventManager::AddTimedEvent(Event* pEvent)
{
	mEvents.push_back(pEvent);
}

void EventManager::Update(float FrameTime)
{
	auto it = mEvents.begin();
	while (it != mEvents.end())
	{
		Event* pEvent = *it;
		pEvent->mTimer -= FrameTime;

		if (pEvent->mTimer < 0.0f)
		{
			BroadCastEvent(pEvent);
			delete pEvent;
			mEvents.erase(it);
			++it;
		}
		else
			++it;
	}
}

void EventManager::Subscribe(EVENT_TYPE et, GameObject* pGO)
{
	for (auto pRegisteredGO : mSubscriptions[et])
	{
		if (pRegisteredGO == pGO)
			return;
	}

	mSubscriptions[et].push_back(pGO);
}

void EventManager::BroadCastEventToSubscribers(Event* pEvent)
{
	printf("%s", "Event Broadcasted!!\n");
	for (auto pGO : mSubscriptions[pEvent->mEventType])
	{
		pGO->HandleEvent(pEvent);
	}
}

CollisionEvent::CollisionEvent() : Event(EVENT_TYPE::COLLIDE), mpObject1(NULL), mpObject2(NULL)
{

}

CollisionEvent::~CollisionEvent()
{

}
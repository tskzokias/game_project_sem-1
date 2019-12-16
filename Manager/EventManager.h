/* Start Header -------------------------------------------------------

  Copyright (C) 2019 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.

File Name:  <EventManager.cpp>
Purpose:  <Implements events based/ subscription based models required in the GAME>
Language:  <C, C++, SDL - Compilers provided by MSVS2019>
Platform: <MSVS2019, Windows 10>
Project: <Student Login - taksh.goyal, Class - CS 529, Assignment - CS529_Final_Project>
Author:  <Name - Taksh Goyal, Student Login - taksh.goyal, Student ID - 60001319>
Creation date: <26th October, 2019>

 - End Header --------------------------------------------------------*/

#pragma once
#include <list>
#include <unordered_map>
#include "..\GameObject.h"

class GameObject;

enum EVENT_TYPE
{
	COLLIDE,
	PLAYER_HIT,
	NUM
};


class Event
{
public:
	Event() : mTimer(0) {}
	Event(EVENT_TYPE aType)
	{
		mEventType = aType;
	}
	virtual ~Event() {}

	EVENT_TYPE mEventType;
	float mTimer;
};

class EventManager
{
public:
	EventManager() {}
	~EventManager() {}

	void BroadCastEvent(Event* pEvent);
	void BroadCastEventToSubscribers(Event* pEvent);
	void AddTimedEvent(Event* pEvent);

	void Update(float FrameTime);

	void Subscribe(EVENT_TYPE et, GameObject* pGO);

	std::list<Event*> mEvents;
	std::unordered_map<EVENT_TYPE, std::list<GameObject*>> mSubscriptions;
};

class CollisionEvent : public Event
{
public:
	CollisionEvent();
	~CollisionEvent();

	GameObject* mpObject1;
	GameObject* mpObject2;
};
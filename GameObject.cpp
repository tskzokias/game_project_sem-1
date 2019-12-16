#include "GameObject.h"
#include "Components\UpDown.h"
#include "Components\Sprite.h"
#include "Components\Transform.h"
#include "Components\Controller.h"
#include "Components/Body.h"

GameObject::GameObject()
{
	IfActiveFlag = true;
}

GameObject::~GameObject()
{
	

}

void GameObject::Update()
{
	for (auto component : mComponents)
	{
		COMPONENT_TYPE type = component->GetType();

		switch (type)
		{
		case COMPONENT_TYPE::COMPONENT_CONTROLLER:
			((static_cast<Controller*> (component))->Update());
			break;
		case COMPONENT_TYPE::COMPONENT_TRANSFORM:
			((static_cast<Transform*> (component))->Update());
			break;
		case COMPONENT_TYPE::COMPONENT_SPRITE:
			((static_cast<Sprite*> (component))->Update());
			break;
		case COMPONENT_TYPE::COMPONENT_UP_DOWN:
			((static_cast<UpDown*> (component))->Update());
			break;
		case COMPONENT_TYPE::COMPONENT_BODY:
			((static_cast<Body*> (component))->Update());
			/*if ((static_cast<Body*> (component))->mMass == 1.0f)
			{
				((static_cast<Body*> (component))->IfPlayerFlag) = true;
			}*/
			break;
		}
	}
}

Component* GameObject::GetComponent(COMPONENT_TYPE type)
{
	for (auto component : mComponents)
	{
		if (component->GetType() == type)
			return component; //Return component if found through all GameObject Component types, else nullptr
	}

	return nullptr;
}

Component* GameObject::AddComponent(COMPONENT_TYPE type)
{
	Component* pComponent = GetComponent(type);
	if (nullptr != pComponent)
		return pComponent;

	switch (type)
	{
	case COMPONENT_TYPE::COMPONENT_TRANSFORM:
		pComponent = new Transform(); // new Transform;
		break;
	case COMPONENT_TYPE::COMPONENT_SPRITE:
		pComponent = new Sprite();
		break;
	case COMPONENT_TYPE::COMPONENT_CONTROLLER:
		pComponent = new Controller();
		break;
	case COMPONENT_TYPE::COMPONENT_UP_DOWN:
		pComponent = new UpDown();
		break;
	case COMPONENT_TYPE::COMPONENT_BODY:
		pComponent = new Body();
		break;
	}

	pComponent->SetOwner(this);
	mComponents.push_back(pComponent);
	return pComponent;
}

void GameObject::Initialize()
{

	for (auto component : mComponents) {
		component->Initialize();
	}
}

void GameObject::HandleEvent(Event* pEvent)
{
 	for (auto component : mComponents) 
	{
		component->HandleEvent(pEvent);
	}
}
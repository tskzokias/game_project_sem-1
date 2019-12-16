#include "ObjectFactory.h"
#include <string>
#include "Components/Transform.h"
#include <iostream>
#include "Components/Component.h"
#include "Manager/GameObjectManager.h"
#include "Manager/InputManager.h"

extern GameObjectManager* gpGameObjectManager;
extern InputManager* gpInputManager;

void ObjectFactory::LoadLevel(const char* pFileName)
{
	FILE* fp;
	fopen_s(&fp, pFileName, "r");
	if (fp)
	{
		while (!feof(fp))
		{
			char archetype[256];
			memset(archetype, 0, sizeof(archetype));

			fscanf_s(fp, "%255s", archetype, sizeof(archetype));

			std::string fullpath = "Resources/";
			fullpath += archetype;

			GameObject* pNewGameObject = LoadObject(fullpath.c_str());
			Transform* pTransform = static_cast<Transform*>(pNewGameObject->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
			pTransform->Serialize(&fp);
			//pNewGameObject->Initialize();
			
		}
		fclose(fp);
	}
	if (fp)
		fclose(fp);

	return;
}

//void ObjectFactory::Loadmenu(const char* pFileName)
//{
//	FILE* fp;
//	fopen_s(&fp, pFileName, "r");
//	if (fp)
//	{
//		while (!feof(fp))
//		{
//			char archetype[256];
//			memset(archetype, 0, sizeof(archetype));
//
//			fscanf_s(fp, "%255s", archetype, sizeof(archetype));
//
//			std::string fullpath = "Resources/";
//			fullpath += archetype;
//
//			GameObject* pNewGameObject = LoadObject(fullpath.c_str());
//			Transform* pTransform = static_cast<Transform*>(pNewGameObject->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
//			pTransform->Serialize(&fp);
//			//pNewGameObject->Initialize();
//
//		}
//		fclose(fp);
//	}
//	if (fp)
//		fclose(fp);
//
//	return;
//}

GameObject* ObjectFactory::LoadObject(const char* Filename)
{
	GameObject* pNewObject = nullptr;
	
	FILE* fp = NULL;
	fopen_s(&fp, Filename, "r");
	if (fp)
	{
		if (!fp)
		{
			std::cout << "File Not Opened Correctly!! Try Again!!!!!!! ";
		}

		pNewObject = new GameObject();
		while (!feof(fp))
		{
			char component[256];
			memset(component, 0, 256 * sizeof(char));

			fscanf_s(fp, "%255s\n", component, sizeof(component));

			Component* pnewComponent = nullptr;
			if (0 == strcmp(component, "Transform"))
				pnewComponent = pNewObject->AddComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM);
			if (0 == strcmp(component, "Sprite"))
				pnewComponent = pNewObject->AddComponent(COMPONENT_TYPE::COMPONENT_SPRITE);
			if (0 == strcmp(component, "UpDown"))
				pnewComponent = pNewObject->AddComponent(COMPONENT_TYPE::COMPONENT_UP_DOWN);
			if (0 == strcmp(component, "Controller"))
				pnewComponent = pNewObject->AddComponent(COMPONENT_TYPE::COMPONENT_CONTROLLER);
			if (0 == strcmp(component, "Body"))
				pnewComponent = pNewObject->AddComponent(COMPONENT_TYPE::COMPONENT_BODY);

			if (nullptr != pnewComponent)
				pnewComponent->Initialize();

			if (nullptr != pnewComponent)
				pnewComponent->Serialize(&fp);

			//pNewObject->mComponents.push_back(pnewComponent);
		}
		fclose(fp);
		gpGameObjectManager->AddGameObject(pNewObject);

	}
	if (fp)
		fclose(fp);
	return pNewObject;
}
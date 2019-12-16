#include "Sprite.h"
#include "string.h"
#include "..\Manager\ResourceManager.h"
#include "..\Manager\InputManager.h"

extern ResourceManager* gpResourceManager;
extern InputManager* gpInputManager;

Sprite::Sprite() : Component(COMPONENT_TYPE::COMPONENT_SPRITE)
{
	mpSurface = nullptr;
	surface = NULL;
	fullpath = '\0';
}

Sprite::~Sprite()
{
	
}

void Sprite::Update()
{
	
}

void Sprite::Serialize(FILE** fpp)
{
	char imageName[256];
	memset(imageName, 0, 256 * sizeof(char));

	fscanf_s(*fpp, "%255s\n", imageName, sizeof(imageName));

	std::string fullpath = "Resources/";
	fullpath += imageName;

	surface = gpResourceManager->GetTextureID(fullpath.c_str());
}

void Sprite::Initialize()
{
	
	
}
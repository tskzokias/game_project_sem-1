#include "Component.h"

Component::Component(COMPONENT_TYPE type)
{
	mpOwner = nullptr;
	mType = type;
}

Component::~Component()
{
	//delete(mpOwner);
}

void Component::Serialize(FILE** fpp)
{

}
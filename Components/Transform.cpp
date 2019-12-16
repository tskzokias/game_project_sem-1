#include "Transform.h"
#include <string>
#include "..\include\glew.h"

Transform::Transform() : Component(COMPONENT_TYPE::COMPONENT_TRANSFORM)
{
	mPosX = 0.0f;
	mPosY = 0.0f;
	Model = glm::mat4(1.0f);
	Proj = glm::mat4(1.0f);
	mScaleX = 0.0f;
	mScaleY = 0.0f;
	currentangle = 0.0f;
}

Transform::~Transform()
{

}

void Transform::Initialize()
{
	currentangle = -90.0f;
	Model = glm::mat4(1.0f);
	Model = glm::scale(Model, glm::vec3(mScaleX, mScaleY, 1.0f));
	Model = glm::translate(Model, glm::vec3(mPosX, mPosY, 0.0f));
	Model = glm::rotate(Model, glm::radians(currentangle), glm::vec3(0.0, 0.0, 1.0));
}

void Transform::Serialize(FILE** fpp)
{

	fscanf_s(*fpp, "%f %f %f %f\n", &mPosX, &mPosY, &mScaleX, &mScaleY);


}

void Transform::Update()
{
	Model = glm::mat4(1.0f);
	Model = glm::translate(Model, glm::vec3(static_cast<GLfloat>(this->mPosX), static_cast<GLfloat>(this->mPosY), 0.0f));
	Model = glm::scale(Model, glm::vec3(mScaleX, mScaleY, 1.0f));
	Proj = glm::ortho(0.0f, 1024.0f, 768.0f, 0.0f, -1.0f, 1.0f);
	Model = glm::rotate(Model, glm::radians(currentangle), glm::vec3(0.0, 0.0, 1.0));
}

void Transform::UpdatePosition(float dx, float dy)
{
	mPosX += dx;
	mPosY += dy;
}

void Transform::Rotate(float angle)
{
	currentangle += angle;
	//Model = glm::rotate(Model, glm::radians(cuurent), glm::vec3(0.0, 0.0, 1.0));
}
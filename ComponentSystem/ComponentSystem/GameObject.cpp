#include "GameObject.h"

const bool GameObject::IsActive() const
{
	return myIsActive;
}

const std::string& GameObject::GetName() const
{
	return myName;
}

void GameObject::SetTag(const Tag aTag)
{
	myTag = aTag;
}

const Tag GameObject::GetTag() const
{
	return myTag;
}

void GameObject::SetActive(bool isActive)
{
	myIsActive = isActive;
}

void GameObject::SetName(const std::string& aName)
{
	myName = aName;
}
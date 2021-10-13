#include "GameObject.h"
#include "Component.h"
#include "ComponentAdmin.h"

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

void GameObject::Destroy(GameObject* aGameObject)
{
	ComponentAdmin::GetInstance()->RemoveGameObject(aGameObject);
}

const size_t& GameObject::GetGameObjectID() const
{
	return myID;
}

void GameObject::Reset()
{
	myIsActive = true;
	myName = "";
	myTag = Tag::Untagged;
	myID = -1;
}

void GameObject::OnDestroy()
{
	
}

void GameObject::OnCreate()
{
	
}

void GameObject::SetActive(bool isActive)
{
	
}

void GameObject::SetName(const std::string& aName)
{
	myName = aName;
}
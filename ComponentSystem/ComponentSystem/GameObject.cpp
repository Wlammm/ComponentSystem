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

GameObject* GameObject::Instantiate()
{
	return ComponentAdmin::GetInstance()->CreateGameObject();
}

void GameObject::Destroy(GameObject* aGameObject, const float aTime)
{
	ComponentAdmin::GetInstance()->RemoveGameObject(aGameObject, aTime);
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
}

void GameObject::SetActive(bool isActive)
{
	ComponentAdmin::GetInstance()->SetActive(this, isActive);
}

void GameObject::SetName(const std::string& aName)
{
	myName = aName;
}
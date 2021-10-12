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

void GameObject::Reset()
{
	myComponents.clear();
	myIsActive = true;
	myName = "";
	myTag = Tag::Untagged;
}

void GameObject::OnDestroy()
{
	for (int i = 0; i < myComponents.size(); ++i)
	{
		myComponents[i]->OnDestroy();
	}
}

void GameObject::OnCreate()
{
	for (int i = 0; i < myComponents.size(); ++i)
	{
		myComponents[i]->OnCreate();
	}
}

void GameObject::SetActive(bool isActive)
{
	if (!isActive && myIsActive)
	{
		for (int i = 0; i < myComponents.size(); ++i)
		{
			myComponents[i]->OnDisable();
		}
	}

	if (isActive && !myIsActive)
	{
		for (int i = 0; i < myComponents.size(); ++i)
		{
			myComponents[i]->OnEnable();
		}
	}

	myIsActive = isActive;
}

void GameObject::SetName(const std::string& aName)
{
	myName = aName;
}
#include "ComponentAdmin.h"
#include "GameObject.h"
#include "Component.h"

ComponentAdmin* ComponentAdmin::ourInstance = nullptr;

ComponentAdmin::ComponentAdmin()
{
	ourInstance = this;
}

ComponentAdmin::~ComponentAdmin()
{
	ourInstance = nullptr;
}

void ComponentAdmin::Init()
{
	myGameObjects.Init<GameObject>();
}

void ComponentAdmin::Update()
{
	for (int i = 0; i < myActiveGameObjects.size(); ++i)
	{
		for (auto comps : myComponentsOnGameObjects[myActiveGameObjects[i]])
		{
			myComponents[myComponentToIndex[comps.first]].Get<Component>(comps.second)->Update();
		}
	}
}

void ComponentAdmin::LateUpdate()
{
	for (int i = 0; i < myActiveGameObjects.size(); ++i)
	{
		for (auto comps : myComponentsOnGameObjects[myActiveGameObjects[i]])
		{
			myComponents[myComponentToIndex[comps.first]].Get<Component>(comps.second)->LateUpdate();
		}
	}
}

GameObject* ComponentAdmin::CreateGameObject()
{
	assert(myGameObjects.GetMaxIndex() - myGameObjects.GetEmptyIndexes().size() < MAX_GAMEOBJECTS && "Max gameobjects reached. Try inreasing MAX_GAMEOBJECTS in types.h");

	size_t id = -1;
	GameObject* ob = myGameObjects.EmblaceBack<GameObject>(id);
	ob->Reset();
	ob->myID = id;
	myActiveGameObjects.push_back(id);
	return ob;
}

void ComponentAdmin::RemoveGameObject(GameObject* anObject)
{
	myActiveGameObjects.erase(std::remove(myActiveGameObjects.begin(), myActiveGameObjects.end(), anObject->GetGameObjectID()));
	myGameObjects.Remove<GameObject>(anObject->myID);

	for (auto& comp : myComponentsOnGameObjects[anObject->GetGameObjectID()])
	{
		myComponents[myComponentToIndex[comp.first]].Remove<void>(comp.second);
	}
}

ComponentAdmin* ComponentAdmin::GetInstance()
{
	return ourInstance;
}
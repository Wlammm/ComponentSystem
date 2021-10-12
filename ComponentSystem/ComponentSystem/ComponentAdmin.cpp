#include "ComponentAdmin.h"
#include "GameObject.h"

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

}

void ComponentAdmin::LateUpdate()
{

}

GameObject* ComponentAdmin::CreateGameObject()
{
	assert(myGameObjects.GetMaxIndex() - myGameObjects.GetEmptyIndexes().size() < MAX_GAMEOBJECTS && "Max gameobjects reached. Try inreasing MAX_GAMEOBJECTS in types.h");

	if (myGameObjects.GetEmptyIndexes().size() > 0)
	{
		GameObject* ob = myGameObjects.Get<GameObject>(myGameObjects.GetEmptyIndexes().back());
		ob->Reset();
		return ob;
	}

	return myGameObjects.EmblaceBack<GameObject>();
}

void ComponentAdmin::RemoveGameObject(GameObject* anObject)
{
	myGameObjects.Remove<GameObject>(anObject);
}

ComponentAdmin* ComponentAdmin::GetInstance()
{
	return ourInstance;
}
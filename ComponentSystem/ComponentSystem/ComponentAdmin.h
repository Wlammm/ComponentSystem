#pragma once

#include <string>
#include <unordered_map>
#include <map>
#include "Types.h"
#include "ComponentManager.hpp"
#include <queue>

class GameObject;

class ComponentAdmin
{
public:
	ComponentAdmin();
	~ComponentAdmin();

	void Init();

	void Update();
	void LateUpdate();

	void SetActive(GameObject* ob, const bool aState);

	template<typename T>
	T* AddComponent(const GameObjectID aID)
	{
		GameObject* toLookFor = &myBase[aID];
		assert(std::find(myActiveGameObjects.begin(), myActiveGameObjects.end(), toLookFor) != myActiveGameObjects.end() && "Trying to add component to non active gameobject.");

		T* comp =  myComponentManager.AddComponent<T>(aID);
		comp->myGameObject = &myBase[aID];
		comp->myIsActive = true;
		return comp;
	}

	template<typename T>
	void RemoveComponent(const GameObjectID aID)
	{
		std::string typeName = typeid(T).name();
		myComponentsToRemove.push_back({ typeName, aID });
	}

	template<typename T>
	const bool HasComponent(const GameObjectID aID)
	{
		return myComponentManager.HasComponent<T>(aID);
	}

	GameObject* CreateGameObject();
	void RemoveGameObject(GameObject* anObject, const float aTime);

private:

	GameObject* myBase;
	std::queue<GameObject*> myGameObjects;
	std::vector<GameObject*> myActiveGameObjects;

	std::map<GameObject*, float> myGameObjectsToBeDeleted;

	std::vector<std::pair<std::string, GameObjectID>> myComponentsToRemove;

	ComponentManager myComponentManager;
	
public:
	static ComponentAdmin* GetInstance();

private:
	static ComponentAdmin* ourInstance;

};
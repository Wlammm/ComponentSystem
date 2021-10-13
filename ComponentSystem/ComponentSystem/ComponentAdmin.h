#pragma once

#include <string>
#include <unordered_map>
#include "Types.h"
#include "OpaqueVector.hpp"
#include "Component.h"
#include "GameObject.h"

class ComponentAdmin
{
public:
	ComponentAdmin();
	~ComponentAdmin();

	void Init();

	void Update();
	void LateUpdate();

	template<typename T>
	const size_t GetComponentIndex()
	{
		std::string typeName = typeid(T).name();

		if (myComponentToIndex.find(typeName) != myComponentToIndex.end())
		{
			return myComponentToIndex[typeName];
		}

		myComponentToIndex[typeName] = myComponents.size();
		myComponents.push_back(CU::OpaqueVector());
		myComponents.back().Init<T>(MAX_COMPONENTS_OF_TYPE);
		return myComponentToIndex[typeName];
	}

	template<typename T>
	T* AddComponent(GameObject* ob)
	{
		size_t compTypeIndex = GetComponentIndex<T>();
		std::string typeName = typeid(T).name();

		size_t gameObjectID = ob->GetGameObjectID();

		size_t compIndex = -1;
		T* compT = myComponents[compTypeIndex].EmblaceBack<T>(compIndex);
		Component* comp = static_cast<Component*>(compT);
		comp->myGameObject = ob;

		assert(myComponentsOnGameObjects[gameObjectID].find(typeName) == myComponentsOnGameObjects[gameObjectID].end() && "Components of type already exists on this gameobject.");

		myComponentsOnGameObjects[gameObjectID][typeName] = compIndex;

		return compT;
	}

	template<typename T>
	void RemoveComponent(GameObject* ob)
	{
		size_t compTypeIndex = GetComponentIndex<T>();
		std::string typeName = typeid(T).name();

		size_t gameObjectID = ob->GetGameObjectID();

		size_t indexToRemove = -1;
		for (auto& comp : myComponentsOnGameObjects[gameObjectID])
		{
			if (comp.first == typeName)
			{
				indexToRemove = comp.second;
				break;
			}
		}

		myComponentsOnGameObjects[gameObjectID].erase(typeName);

		assert(indexToRemove != -1 && "Component does not exist on gameobject.");

		myComponents[myComponentToIndex[typeName]].Remove<void>(indexToRemove);
	}

	GameObject* CreateGameObject();
	void RemoveGameObject(GameObject* anObject);

private:
	std::unordered_map<std::string, unsigned int> myComponentToIndex;
	std::vector<CU::OpaqueVector> myComponents;

	std::vector<size_t> myActiveGameObjects;

	CU::OpaqueVector myGameObjects;

	// myComponentsOnGameObject[gameObjectID][componentTypeName] -> ID i opaque vectorn.
	std::unordered_map<size_t, std::unordered_map<std::string, size_t>> myComponentsOnGameObjects;
public:
	static ComponentAdmin* GetInstance();

private:
	static ComponentAdmin* ourInstance;

};
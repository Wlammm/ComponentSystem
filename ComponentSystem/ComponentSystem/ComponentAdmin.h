#pragma once

#include <string>
#include <unordered_map>
#include "Types.h"
#include "OpaqueVector.hpp"

class GameObject;

class ComponentAdmin
{
public:
	ComponentAdmin();
	~ComponentAdmin();

	void Init();

	void Update();
	void LateUpdate();

	template<typename T>
	const unsigned int GetComponentIndex()
	{
		std::string typeName = typeid(T).name();

		if (myComponentToIndex.find(typeName) != myComponentToIndex.end())
		{
			return myComponentToIndex[typeName];
		}

		myComponentToIndex[typeName] = myComponents.size();
		CU::OpaqueVector vec = myComponents.emplace_back();
		vec.Init<T>(MAX_COMPONENTS_OF_TYPE);
		return myComponentToIndex[typeName];
	}

	GameObject* CreateGameObject();
	void RemoveGameObject(GameObject* anObject);

private:
	std::unordered_map<std::string, unsigned int> myComponentToIndex;
	std::vector<CU::OpaqueVector> myComponents;

	CU::OpaqueVector myGameObjects;

public:
	static ComponentAdmin* GetInstance();

private:
	static ComponentAdmin* ourInstance;

};
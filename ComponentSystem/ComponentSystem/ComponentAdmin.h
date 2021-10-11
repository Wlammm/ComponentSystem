#pragma once

#include "Types.hpp"
#include <vector>
#include <unordered_map>
#include "OpaqueVector.hpp"
#include <typeinfo>
#include "GameObject.h"

class ComponentAdmin
{
public:
	ComponentAdmin() = default;
	~ComponentAdmin() = default;

	template<typename T>
	void RegisterComponent()
	{
		std::string typeName = typeid(T).name();

		if (myComponents.find(typeName) == myComponents.end())
		{
			CU::OpaqueVector opVec{};
			opVec.Init<T>(MAX_COMPONENTS);

			myComponents[typeName] = opVec;
			return;
		}

		assert(false && "Component already registered.");
	}

	template<typename T>
	T* AddComponent(GameObject* ob)
	{
		std::string typeName = typeid(T).name();
		assert(myComponents.find(typeName) != myComponents.end() && "Component not registered.");
		assert(myComponents[typeName].Size() < MAX_COMPONENTS && "Too many components of size. Try increasing MAX_COMPONENTS in Types.hpp");

		return myComponents[typeName].EmblaceBack();
	}

	template<typename T>
	void RemoveComponent(GameObject* ob)
	{
		myComponents[""].
	}

	template<typename T> 
	T* GetComponent(GameObject* ob)
	{

	}

private:
	std::unordered_map<std::string, CU::OpaqueVector> myComponents;

};
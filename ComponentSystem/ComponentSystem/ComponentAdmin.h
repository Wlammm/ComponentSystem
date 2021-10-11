#pragma once

#include "Types.hpp"
#include <vector>
#include <unordered_map>
#include "OpaqueVector.hpp"
#include <typeinfo>
#include "Component.h"
#include "GameObject.h"

class GameObject;


class ComponentAdmin
{
public:
	ComponentAdmin()
	{
		ourInstance = this;
	}

	~ComponentAdmin()
	{
		ourInstance = nullptr;
	}

	static ComponentAdmin* GetInstance()
	{
		return ourInstance;
	}

private:
	static ComponentAdmin* ourInstance;

public:
	//ComponentAdmin() = default;
	//~ComponentAdmin() = default;

	void Init()
	{
		myGameObjects.Init<GameObject>(MAX_GAMEOBJECTS);
	}

	template<typename T>
	void RegisterComponent()
	{
		std::string typeName = typeid(T).name();

		if (myComponents.find(typeName) == myComponents.end())
		{
			CU::OpaqueVector opVec{};
			opVec.Init<T>(MAX_COMPONENTS);

			myComponents[typeName] = opVec;
			myComponentSignatures.insert({ typeName, myNextComponentType });
			++myNextComponentType;
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

		T* comp = myComponents[typeName].EmblaceBack();
		comp->Reset();
		comp->myComponentSignature = GetComponentSignature<T>();
		comp->myGameObject = ob;
		comp->OnCreate();
		return comp;
	}

	template<typename T>
	void GetComponentSignature()
	{
		std::string typeName = typeid(T).name();
		assert(myComponentSignatures.find(typeName) != myComponentSignatures.end());

		return myComponentSignatures[typeName];
	}

	template<typename T>
	void RemoveComponent(GameObject* ob)
	{
		Signature componentSignature = GetComponentSignature<T>();
		std::string typeName = typeid(T).name();
		for (int i = 0; i < ob->myComponents.size(); ++i)
		{
			if (ob->myComponents[i]->myComponentSignature == componentSignature)
			{
				Component* comp = ob->myComponents[i];
				comp->OnDestroy();
				myComponents[typeName].Remove(comp);
			}
		}
	}

	template<typename T>
	CU::OpaqueVector& GetAllComponentsOfType()
	{
		std::string typeName = typeid(T).name();
		return myComponents[typeName];
	}

	void Update()
	{
		for (auto& comp : myComponents)
		{
			for (size_t i = 0; i < comp.second.GetMaxIndex(); ++i)
			{
				const std::vector<size_t>& emptyIndexes = comp.second.GetEmptyIndexes();
				if (std::find(emptyIndexes.begin(), emptyIndexes.end(), i) == emptyIndexes.end())
				{
					comp.second.Get<Component>(i)->Update();
				}
			}
		}
	}

	void LateUpdate()
	{
		for (auto& comp : myComponents)
		{
			for (size_t i = 0; i < comp.second.GetMaxIndex(); ++i)
			{
				const std::vector<size_t>& emptyIndexes = comp.second.GetEmptyIndexes();
				if (std::find(emptyIndexes.begin(), emptyIndexes.end(), i) == emptyIndexes.end())
				{
					comp.second.Get<Component>(i)->LateUpdate();
				}
			}
		}
	}

	GameObject* CreateGameObject()
	{
		assert(myGameObjects.Size() < MAX_GAMEOBJECTS && "GameObject limit reached. Try increasing MAX_GAMEOBJECTS in Types.hpp");

		GameObject* ob = myGameObjects.EmblaceBack<GameObject>();
		ob->Reset();
		ob->OnCreate();
		return ob;
	}

	void RemoveComponent(Component* aComponent)
	{
		for (auto& vec : myComponents)
		{
			Component* firstComp = vec.second.Get<Component>(0);
			Component* lastComp = vec.second.Get<Component>(vec.second.GetMaxIndex());

			if (&aComponent < &lastComp && &aComponent > &firstComp)
			{
				vec.second.Remove(aComponent);
				return;
			}
		}
	}

	void DestroyGameObject(GameObject* anObject)
	{
		anObject->OnDestroy();
		
		for (int i = 0; i < anObject->myComponents.size(); ++i)
		{
			RemoveComponent(anObject->myComponents[i]);
		}

		myGameObjects.Remove(anObject);
	}

private:
	size_t myNextComponentType = { 0 };
	std::unordered_map<std::string, Signature> myComponentSignatures;
	std::unordered_map<std::string, CU::OpaqueVector> myComponents;
	CU::OpaqueVector myGameObjects;
};

ComponentAdmin* ComponentAdmin::ourInstance = nullptr;
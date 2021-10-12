#pragma once

#include "Types.hpp"
#include <vector>
#include <string>
#include <unordered_map>
#include "Tag.hpp"
#include "Component.h"

class GameObject
{
public:
	GameObject() = default;
	~GameObject() = default;

	void SetActive(bool isActive);
	const bool IsActive() const;

	void SetName(const std::string& aName);
	const std::string& GetName() const;

	void SetTag(const Tag aTag);
	const Tag GetTag() const;

	template<typename T>
	T* AddComponent()
	{
		return ComponentAdmin::GetInstance()->AddComponent<T>(this);
	}

	template<typename T>
	void RemoveComponent()
	{
		ComponentAdmin::GetInstance()->RemoveComponent<T>(this);
	}

	template<typename T>
	const bool HasComponent()
	{
		Signature componentSignature = ComponentAdmin::GetInstance()->GetComponentSignature<T>();

		if (componentSignature == mySignature)
		{
			return true;
		}

		return false;
	}


private:
	friend class ComponentAdmin;

	void Reset();
	void OnDestroy();
	void OnCreate();

	std::vector<Component*> myComponents;
	Signature mySignature;

	bool myIsActive = true;
	std::string myName = "";
	Tag myTag;
};
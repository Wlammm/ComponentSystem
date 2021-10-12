#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "Tag.hpp"

class Component;

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

	void Destroy(GameObject* aGameObject);

	template<typename T>
	T* AddComponent()
	{

	}

	template<typename T>
	void RemoveComponent()
	{

	}

	template<typename T>
	const bool HasComponent()
	{

	}


private:
	friend class ComponentAdmin;

	void Reset();
	void OnDestroy();
	void OnCreate();

	std::unordered_map<std::string, unsigned int> myComponents;

	bool myIsActive = true;
	std::string myName = "";
	Tag myTag;
};
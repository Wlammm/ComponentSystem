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

	const size_t& GetGameObjectID() const;

	template<typename T>
	T* AddComponent()
	{
		return nullptr;
	}

	template<typename T>
	void RemoveComponent()
	{

	}

	template<typename T>
	const bool HasComponent()
	{
		return false;
	}

private:
	friend class ComponentAdmin;

	void Reset();
	void OnDestroy();
	void OnCreate();

	size_t myID = -1;
	bool myIsActive = true;
	std::string myName = "";
	Tag myTag = Tag::Untagged;
};
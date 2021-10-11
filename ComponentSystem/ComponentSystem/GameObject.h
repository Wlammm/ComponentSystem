#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "Tag.hpp"

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

private:
	bool myIsActive = true;
	std::string myName = "";
	Tag myTag;

	size_t myGameObjectID = -1;
};
#pragma once

#include "Types.hpp"

class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(GameObjectID anEntity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
public:
	void InsertData(GameObjectID anEntity, T aComponent)
	{
		assert(myGameObjectToIndexMap.find(anEntity) == myGameObjectToIndexMap.end() && "Component already exists on entity.");

		int newIndex = mySize;
		myGameObjectToIndexMap[anEntity] = newIndex;
		myIndexToGameObjectMap[newIndex] = anEntity;
		myComponentArray[newIndex] = aComponent;
		mySize++;
	}

	void RemoveData(GameObjectID anEntity)
	{
		assert(myGameObjectToIndexMap.find(anEntity) != myGameObjectToIndexMap.end() && "Entity does not exists.");

		int indexOfRemovedEntity = myGameObjectToIndexMap[anEntity];
		int indexOfLastElement = mySize - 1;
		myComponentArray[indexOfRemovedEntity] = myComponentArray[indexOfLastElement];

		Entity entityOfLastElement = myIndexToGameObjectMap[indexOfLastElement];
		myGameObjectToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		myIndexToGameObjectMap[indexOfRemovedEntity] = entityOfLastElement;

		myGameObjectToIndexMap.erase(anEntity);
		myIndexToGameObjectMap.erase(indexOfLastElement);
	}

	T& GetData(GameObjectID anEntity)
	{
		assert(myGameObjectToIndexMap.find(anEntity) != myGameObjectToIndexMap.end() && "Component does not exist on entity.");

		return myComponentArray[myGameObjectToIndexMap[anEntity]];
	}

	void EntityDestroyed(GameObjectID anEntity) override
	{
		if (myGameObjectToIndexMap.find(anEntity) != myGameObjectToIndexMap.end())
		{
			RemoveData(anEntity);
		}
	}

private:
	std::array<T, MAX_ENTITIES> myComponentArray{};
	std::unordered_map<GameObjectID, int> myGameObjectToIndexMap{};
	std::unordered_map<int, GameObjectID> myIndexToGameObjectMap{};
	int mySize{};
};
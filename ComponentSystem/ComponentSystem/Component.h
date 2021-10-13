#pragma once

class GameObject;

class Component
{
public:
	Component() = default;
	virtual ~Component();

	void SetActive(const bool aState);
	const bool IsActive() const;

	GameObject* GetGameObject() const;

protected:
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

	// Runs once per frame.
	virtual void Update();
	// Runs once per frame after update.
	virtual void LateUpdate();

	// Runs when the component is created.
	virtual void OnCreate();
	// Runs when the component or gameobject is destroyed.
	virtual void OnDestroy();

	// Runs when the component or gameobject is re-enabled.
	virtual void OnEnable();
	// Runs when the componnet or gmaeobject is disabled.
	virtual void OnDisable();

	// Runs once a collision with this object has happened.
	virtual void OnCollision(GameObject* anOther);

	// Runs the frame this object enters a trigger.
	virtual void OnTriggerEnter(GameObject* anOther);
	// Runs the frame this object leaves a trigger.
	virtual void OnTriggerExit(GameObject* anOther);
	// Runs every frame this object is inside a trigger.
	virtual void OnTrigger(GameObject* anOther);

private:
	friend class ComponentAdmin;
	friend class GameObject;

	GameObject* myGameObject = nullptr;
	bool myIsActive = true;
};
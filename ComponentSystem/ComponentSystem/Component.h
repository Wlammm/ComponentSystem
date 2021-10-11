#pragma once

class GameObject;

class Component
{
public:
	Component() = default;
	Component();
	virtual ~Component();

protected:
	virtual void Update();
	virtual void LateUpdate();
	virtual void OnRender();

	virtual void OnCreate();
	virtual void OnDestroy();

private:
	friend class ComponentAdmin;
	GameObject* myGameObject = nullptr;

	bool myIsActive = true;
};
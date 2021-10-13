#include <iostream>
#include "ComponentAdmin.h"
#include "PrinterComponent.h"
#include "GameObject.h"

int main()
{
	ComponentAdmin* admin = new ComponentAdmin();
	admin->Init();

	GameObject* gameObject = admin->CreateGameObject();
	gameObject->SetName("tst");
	admin->RemoveGameObject(gameObject);
	gameObject = admin->CreateGameObject();
	PrinterComponent* comp = admin->AddComponent<PrinterComponent>(gameObject);
	admin->RemoveComponent<PrinterComponent>(gameObject);
	while (true)
	{
		admin->Update();
		admin->LateUpdate();
	}

	return 0;
}
#include <iostream>
#include "ComponentAdmin.h"
#include "PrinterComponent.h"

int main()
{
	ComponentAdmin* admin = new ComponentAdmin();
	admin->Init();
	admin->RegisterComponent<PrinterComponent>();

	GameObject* gameObject = admin->CreateGameObject();
	gameObject->AddComponent<PrinterComponent>();

	while (true)
	{
		admin->Update();
		admin->LateUpdate();
	}

	return 0;
}
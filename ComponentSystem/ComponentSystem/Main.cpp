#include <iostream>
#include "ComponentAdmin.h"
#include "PrinterComponent.h"

int main()
{
	ComponentAdmin* admin = new ComponentAdmin();
	admin->Init();

	GameObject* gameObject = admin->CreateGameObject();
	while (true)
	{
		admin->Update();
		admin->LateUpdate();
	}

	return 0;
}
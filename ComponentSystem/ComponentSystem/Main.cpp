#include <iostream>
#include "ComponentAdmin.h"
#include "PrinterComponent.h"
#include "GameObject.h"

int main()
{
	ComponentAdmin* admin = new ComponentAdmin();
	admin->Init();

	GameObject* gameObject = Instantiate();
	gameObject->SetName("tst");
	Destroy(gameObject);
	gameObject = Instantiate();
	while (true)
	{
		admin->Update();
		admin->LateUpdate();
	}

	return 0;
}
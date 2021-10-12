#pragma once

#include "Component.h"

class PrinterComponent : public Component
{
public:
	PrinterComponent() = default;
	~PrinterComponent() = default;

	void Update() override;


private:
};
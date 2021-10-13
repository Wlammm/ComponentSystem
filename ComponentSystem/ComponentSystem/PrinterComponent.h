#pragma once

#include "Component.h"

class PrinterComponent : public Component
{
public:
	~PrinterComponent();

	void Update() override;

private:
};
#pragma once

#include "Engine/RenderableObject.h"


class SpinningSphere : public RenderableObject
{
private:
	float _degree;

public:
	SpinningSphere(std::string name = "Spinning Sphere");

	virtual void Init() override;

	virtual void Update() override;
};
#include "SpinningSphere.h"


SpinningSphere::SpinningSphere(std::string name) : RenderableObject(name)
{
	_degree = 0.0f;
}

void SpinningSphere::Init()
{
	RenderableObject::Init();

	SetObjectRotation(_degree, 1.0f, 0.0f, 0.0f);
}

void SpinningSphere::Update()
{
	RenderableObject::Update();
	
	_degree += 0.5f;

	SetObjectRotation(_degree, 1.0f, 0.0f, 0.0f);
}
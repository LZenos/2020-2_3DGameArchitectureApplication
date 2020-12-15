#pragma once

#include "CompositeObject.h"


class NonRenderableObject : public CompositeObject
{
public:
	NonRenderableObject(std::string object_name) : CompositeObject(object_name) {}


	virtual void Init() override
	{
		CompositeObject::Init();
	}

	virtual void Update() override
	{
		CompositeObject::Update();
	}

	virtual void Render() override {}

	virtual void OnCollision(BoxCollider* other) override
	{
		CompositeObject::OnCollision(other);
	}

	virtual void ReleaseMemory() override
	{
		CompositeObject::ReleaseMemory();

		delete this;
	}
};
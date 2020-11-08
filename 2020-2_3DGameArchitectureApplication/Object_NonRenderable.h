#pragma once

#include "Object.h"


class NonRenderableObject : public Object
{
public:
	NonRenderableObject(std::string object_name) : Object(object_name) {}


	virtual void Init() override {}

	virtual void Update() override {}

	virtual void Render() override {}

	virtual void ReleaseMemory() override { delete this; }
};
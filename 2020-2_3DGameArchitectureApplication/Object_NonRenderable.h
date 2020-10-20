#pragma once

#include "Object.h"


class NonRenderableObject : public Object
{
public:
	NonRenderableObject(std::string object_name);
	~NonRenderableObject();

	virtual void Update() override;

	virtual void ReleaseMemory() override;
};
#pragma once

#include "NonRenderableObject.h"
#include "Renderer.h"


class Light : public NonRenderableObject
{
public:
	Light(std::string object_name = "Light") : NonRenderableObject(object_name)
	{
		Renderer::GetInstance().AddLight(this);
	}
};
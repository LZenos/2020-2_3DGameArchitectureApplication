#pragma once

#include "Object_NonRenderable.h"


class Light : public NonRenderableObject
{
public:
	Light(std::string object_name = "Light") : NonRenderableObject(object_name) {}
};
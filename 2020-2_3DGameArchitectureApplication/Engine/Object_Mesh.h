#pragma once

#include "RenderableObject.h"


class Mesh : public RenderableObject
{
public:
	Mesh(std::string object_name = "Mesh") : RenderableObject(object_name) {}
};
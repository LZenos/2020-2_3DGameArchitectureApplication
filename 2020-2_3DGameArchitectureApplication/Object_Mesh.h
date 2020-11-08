#pragma once

#include "Object_Renderable.h"


class Mesh : public RenderableObject
{
public:
	Mesh(std::string object_name = "Mesh") : RenderableObject(object_name) {}
};
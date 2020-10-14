#pragma once

#include "Object_Renderable.h"


class Sphere : public RenderableObject
{
public:
	Sphere(std::string object_name = "Sphere") : RenderableObject(object_name) {}

	bool Initialize(const char* dds_file_path = "Default");
};
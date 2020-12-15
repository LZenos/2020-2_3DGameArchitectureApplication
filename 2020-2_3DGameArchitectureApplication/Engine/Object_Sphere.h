#pragma once

#include "RenderableObject.h"


class Sphere : public RenderableObject
{
public:
	Sphere(std::string object_name = "Sphere") : RenderableObject(object_name) {}

	virtual void Initialize(const char* vs_path = "vs.shader", const char* fs_path = "fs.shader")
	{
		RenderableObject::Initialize("../Models/sphere.obj", "../Textures/earth.dds", vs_path, fs_path);
	}
};
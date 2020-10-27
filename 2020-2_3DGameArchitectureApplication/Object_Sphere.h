#pragma once

#include "Object_Renderable.h"


class Sphere : public RenderableObject
{
private:
	float _degree;

public:
	Sphere(std::string object_name = "Sphere") : RenderableObject(object_name) {}

	bool Initialize(const char* obj_file_path = "Default", const char* dds_file_path = "Default");

	virtual void Update() override;
};
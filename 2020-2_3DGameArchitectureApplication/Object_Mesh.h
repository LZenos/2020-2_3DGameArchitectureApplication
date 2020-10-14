#pragma once

#include "Object_Renderable.h"


class Mesh : public RenderableObject
{
public:
	Mesh(std::string object_name = "Mesh") : RenderableObject(object_name) {}

	bool Initialize(const char* obj_file_path, const char* dds_file_path, bool advanced_parser = false);
};
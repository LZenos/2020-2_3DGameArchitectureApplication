#pragma once

#include "ICleanup.h"
#include "IUpdatable.h"

#include <string>
#include <vector>

#include "include/GL/glew.h"
#include "glm/glm.hpp"


class FileManager;


class Object : public ICleanUp, public IUpdatable
{
private:
	std::string _objName;

	glm::vec3 _worldPosition;

public:
	Object(std::string object_name);
	~Object();

	std::string GetName() const;

	void SetObjectLocation(float x, float y, float z);
	void SetObjectLocation(glm::vec3 world_pos);

	glm::vec3 GetObjectLocation() const;
};
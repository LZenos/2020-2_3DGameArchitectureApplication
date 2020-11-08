#pragma once

#include "ICleanUp.h"
#include "IUpdatable.h"

#include <string>
#include <vector>

#include "include/GL/glew.h"
#include "glm/glm.hpp"


class Object : public IUpdatable, public ICleanUp
{
private:
	std::string _objName;

	glm::vec3 _position;
	float _rotationDegree;
	glm::vec3 _rotationAxis;
	glm::vec3 _scale;

	Object* _parent;

public:
	Object(std::string object_name);


	virtual void Init() override = 0;

	virtual void Update() override = 0;

	virtual void Render() = 0;


	std::string GetName() const;


	void SetObjectLocation(float x, float y, float z);
	void SetObjectLocation(glm::vec3 local_pos);

	glm::vec3 GetObjectLocation() const;


	void SetObjectRotation(float degree, float x, float y, float z);

	float GetObjectRotationDegree() const;
	glm::vec3 GetObjectRotationAxis() const;
	

	void SetObjectScale(float x, float y, float z);

	glm::vec3 GetObjectScale() const;


	void AttachTo(Object* parent);

	bool IsChild() const;

	Object* GetParent() const;


	virtual void ReleaseMemory() override = 0;
};
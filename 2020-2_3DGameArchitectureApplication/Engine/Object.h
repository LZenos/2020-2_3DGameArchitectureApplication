#pragma once

#include "IUpdatable.h"
#include "ICleanUp.h"

#include <iostream>
#include <string>
#include <vector>

#include "../include/GL/glew.h"
#include "../glm/glm.hpp"


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


	virtual void Init() override;

	virtual void Update() override = 0;

	virtual void Render() = 0;

	virtual void OnCollision(class BoxCollider* other) = 0;

	virtual void ReleaseMemory() override = 0;


	std::string GetName() const;


	void SetObjectLocation(float x, float y, float z);
	void SetObjectLocation(glm::vec3 local_pos);

	glm::vec3 GetObjectLocation() const;

	virtual glm::vec3 GetObjectWorldLocation();


	void SetObjectRotation(float degree, float x, float y, float z);

	float GetObjectRotationDegree() const;
	glm::vec3 GetObjectRotationAxis() const;
	

	void SetObjectScale(float x, float y, float z);

	glm::vec3 GetObjectScale() const;


	void SetParent(Object* parent);

	Object* GetParent() const;

	bool IsChild() const;


	template <typename T> T* Cast(Object* obj_to_cast);
	template <typename T> bool CheckType(Object* obj);

	virtual void SearchRenderableObjFromSceneGraph() = 0;
};
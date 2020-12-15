#pragma once

#include "NonRenderableObject.h"


class Renderer;


class Camera : public NonRenderableObject
{
private:
	glm::vec3 _worldAimPos;
	glm::vec3 _worldUpVector;
	float _fovDegree;
	float _aspect;
	float _near;
	float _far;

public:
	Camera(std::string object_name = "Camera");
	
	void Initialize(glm::vec3 camera_pos, glm::vec3 aim_pos, glm::vec3 up_vector,
					float fov_degree = 45.0f, float aspect = (4.0f / 3.0f), float near = 0.1f, float far = 200.0f);

	glm::vec3 GetAimPos() const;
	glm::vec3 GetUpVector() const;
	float GetFOV() const;
	float GetAspect() const;
	float GetNear() const;
	float GetFar() const;
};
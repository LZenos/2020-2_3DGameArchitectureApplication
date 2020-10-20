#include "Object_Camera.h"


Camera::Camera(std::string object_name) : NonRenderableObject(object_name)
{
	_worldAimPos = glm::vec3(0, 0, 0);
	_worldUpVector = glm::vec3(0, 1, 0);
	_fovDegree = 45.0f;
	_aspect = (4.0f / 3.0f);
	_near = 0.1f;
	_far = 100.0f;

	_interval = -0.01f;
}

void Camera::Initialize(glm::vec3 camera_pos, glm::vec3 aim_pos, glm::vec3 up_vector,
						float fov_degree, float aspect, float near, float far)
{
	SetObjectLocation(camera_pos.x, camera_pos.y, camera_pos.z);
	_worldAimPos = aim_pos;
	_worldUpVector = up_vector;
	_fovDegree = fov_degree;
	_aspect = aspect;
	_near = near;
	_far = far;
}

void Camera::Update()
{
	NonRenderableObject::Update();
	
	if (GetObjectLocation().x > 10.0f)
	{
		_interval = -0.01f;
	}
	else if (GetObjectLocation().x < -10.0f)
	{
		_interval = 0.01f;
	}

	SetObjectLocation(GetObjectLocation().x + _interval, GetObjectLocation().y, GetObjectLocation().z);
}

glm::vec3 Camera::GetAimPos() const
{
	return _worldAimPos;
}
glm::vec3 Camera::GetUpVector() const
{
	return _worldUpVector;
}
float Camera::GetFOV() const
{
	return _fovDegree;
}
float Camera::GetAspect() const
{
	return _aspect;
}
float Camera::GetNear() const
{
	return _near;
}
float Camera::GetFar() const
{
	return _far;
}
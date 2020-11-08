#pragma once

#include "ICleanUp.h"

#include <vector>

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include "glm/glm.hpp";
#include "glm/gtc/matrix_transform.hpp"


class RenderableObject;
class Camera;
class Light;


class Renderer : public ICleanUp
{
private:
	int _frameLimit;
	float _curSec;
	
	GLFWwindow* _window;

	std::vector<RenderableObject*> _renderableObjList;
	Camera* _usingCamera;
	std::vector<Light*> _lightList;

	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;
	glm::mat4 _modelMatrix;


	Renderer();

public:
	~Renderer();

	static Renderer& GetInstance();
	
	bool InitWindowSettings(const char* title, int width = 1024, int height = 768);
	void InitRenderSettings();
	
	void SetLimitFrame(int max_frame);
	
	bool IsWindowClose();

	void AddObject(RenderableObject* obj);
	void AddCamera(Camera* camera);
	void AddLight(Light* light);

	void Render();

	virtual void ReleaseMemory() override;
};
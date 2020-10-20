#pragma once

#include "ICleanup.h"
#include "IUpdatable.h"

#include <vector>

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include "glm/glm.hpp";
#include "glm/gtc/matrix_transform.hpp"


class FileManager;
class RenderableObject;
class Camera;


class Renderer : public ICleanUp
{
private:
	GLFWwindow* window;

	std::vector<RenderableObject*> _renderableObjList;
	Camera* _usingCamera;
	std::vector<IUpdatable*> _updatableObjList;

	GLuint _vertexArrayID;
	GLuint _programID;
	GLuint _matrixID;
	GLuint _viewMatrixID;
	GLuint _modelMatrixID;
	GLuint _textureID;
	GLuint _lightID;

	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;
	glm::mat4 _modelMatrix;
	glm::mat4 _MVP;

	glm::vec3 _lightPos;


	Renderer();

public:
	~Renderer();

	static Renderer& GetInstance();
	
	bool InitWindowSettings(const char* title, int width = 1024, int height = 768);
	void InitRenderSettings(const char* vs_path, const char* fs_path);
	void InitLightPosition(float x, float y, float z);
	
	bool IsWindowClose();

	void AddObject(RenderableObject* obj);
	void AddCamera(Camera* camera);

	void AddUpdatableObj(IUpdatable* obj);

	void Update();
	void Draw();

	virtual void ReleaseMemory() override;
};
#include "Renderer.h"

#include "Time.h"
#include "InputManager.h"
#include "RenderableObject.h"
#include "Object_Root.h"
#include "Object_Camera.h"
#include "Object_Light.h"

#include <stdio.h>
#include <fstream>
#include <sstream>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib-vc2017/glew32.lib")
#pragma comment(lib, "lib-vc2017/glfw3.lib")


Renderer::Renderer()
{
	_frameLimit = 0;
	_curSec = 0.0f;

	_rootObj = nullptr;

	_window = nullptr;
	
	_renderableObjList.clear();
	_mainCamera = nullptr;
	_lightList.clear();

	_projectionMatrix = glm::mat4(1.0f);
	_viewMatrix = glm::mat4(1.0f);
	_modelMatrix = glm::mat4(1.0f);
}

Renderer::~Renderer()
{
	
}


Renderer& Renderer::GetInstance()
{
	static Renderer _instance;

	return _instance;
}


bool Renderer::InitWindowSettings(const char* title, int width, int height)
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (_window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(_window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return false;
	}

	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwPollEvents();
	glfwSetCursorPos(_window, width / 2, height / 2);

	glClearColor(0.005f, 0.0f, 0.02f, 0.0f);

	InputManager::GetInstance().InitiWindow(_window);

	return true;
}

void Renderer::InitRenderSettings()
{
	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
}


void Renderer::SetLimitFrame(int max_frame)
{
	_frameLimit = max_frame;
}

bool Renderer::IsWindowClose()
{
	return (glfwGetKey(_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && 
			glfwWindowShouldClose(_window) == 0);
}


void Renderer::RegistRootObject(RootScene* root_obj)
{
	_rootObj = root_obj;
}
void Renderer::AddObject(RenderableObject* obj)
{
	_renderableObjList.push_back(obj);
}

void Renderer::AddCamera(Camera* camera)
{
	_mainCamera = camera;
	
	_projectionMatrix = glm::perspective(glm::radians(camera->GetFOV()), camera->GetAspect(), camera->GetNear(), camera->GetFar());
	_viewMatrix = glm::lookAt(camera->GetObjectLocation(), camera->GetAimPos(), camera->GetUpVector());
	_modelMatrix = glm::mat4(1.0f);
}

void Renderer::AddLight(Light* light)
{
	_lightList.push_back(light);
}


void Renderer::Render()
{
	if (_frameLimit > 0)
	{
		if (_curSec < (1.0f / (float)_frameLimit))
		{
			_curSec += Time::GetInstance().GetDeltaTime();

			return;
		}
		else
		{
			_curSec = 0.0f;
		}
	}

	_rootObj->SearchRenderableObjFromSceneGraph();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	_projectionMatrix = glm::perspective(glm::radians(_mainCamera->GetFOV()), _mainCamera->GetAspect(), _mainCamera->GetNear(), _mainCamera->GetFar());
	_viewMatrix = glm::lookAt(_mainCamera->GetObjectLocation(), _mainCamera->GetAimPos(), _mainCamera->GetUpVector());
	_modelMatrix = glm::mat4(1.0f);

	for (int i = 0; i < _renderableObjList.size(); i++)
	{
		_renderableObjList[i]->SetMVP(_modelMatrix, _viewMatrix, _projectionMatrix);


		for (int n = 0; n < _lightList.size(); n++)
		{
			glm::vec3 light_worldPos = _lightList[n]->GetObjectLocation();
			if (_lightList[n]->IsChild())
			{
				light_worldPos += _lightList[n]->GetParent()->GetObjectLocation();
			}

			_renderableObjList[i]->UniformShaderRelativeLightPos(light_worldPos);
		}

		_renderableObjList[i]->Render();
	}

	_renderableObjList.clear();


	glfwSwapBuffers(_window);
	glfwPollEvents();
}

void Renderer::ReleaseMemory()
{
	_renderableObjList.clear();
	_lightList.clear();

	glfwTerminate();
}
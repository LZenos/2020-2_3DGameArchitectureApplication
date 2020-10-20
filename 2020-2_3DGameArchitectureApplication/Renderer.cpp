#include "Renderer.h"

#include "FileManager.h"
#include "Object_Renderable.h"
#include "Object_Camera.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib-vc2017/glew32.lib")
#pragma comment(lib, "lib-vc2017/glfw3.lib")


Renderer::Renderer()
{

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

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return false;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwPollEvents();
	glfwSetCursorPos(window, width / 2, height / 2);

	glClearColor(0.0f, 0.0f, 0.2f, 0.0f);
}

void Renderer::InitRenderSettings(const char* vs_path, const char* fs_path)
{
	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glGenVertexArrays(1, &_vertexArrayID);
	glBindVertexArray(_vertexArrayID);

	_programID = FileManager::GetInstance().LoadShader(vs_path, fs_path);

	_matrixID = glGetUniformLocation(_programID, "MVP");
	_viewMatrixID = glGetUniformLocation(_programID, "V");
	_modelMatrixID = glGetUniformLocation(_programID, "M");

	_textureID = glGetUniformLocation(_programID, "myTextureSampler");

	_lightID = glGetUniformLocation(_programID, "LightPosition_worldspace");
}

void Renderer::InitLightPosition(float x, float y, float z)
{
	_lightPos = glm::vec3(x, y, z);
}

bool Renderer::IsWindowClose()
{
	return (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && 
			glfwWindowShouldClose(window) == 0);
}

void Renderer::BindCamera(Camera* camera)
{
	_projectionMatrix = glm::perspective(glm::radians(camera->GetFOV()), camera->GetAspect(), camera->GetNear(), camera->GetFar());
	_viewMatrix = glm::lookAt(camera->GetObjectLocation(), camera->GetAimPos(), camera->GetUpVector());
	_modelMatrix = glm::mat4(1.0f);
}


void Renderer::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	system("cls");
}

void Renderer::Draw(RenderableObject* obj)
{
	glUseProgram(_programID);

	glm::mat4 model_translate = glm::translate(glm::mat4(1.0f), obj->GetObjectLocation());

	_MVP = _projectionMatrix * _viewMatrix * model_translate * _modelMatrix;

	glUniformMatrix4fv(_matrixID, 1, GL_FALSE, &_MVP[0][0]);
	glUniformMatrix4fv(_modelMatrixID, 1, GL_FALSE, &_modelMatrix[0][0]);
	glUniformMatrix4fv(_viewMatrixID, 1, GL_FALSE, &_viewMatrix[0][0]);

	glUniform3f(_lightID, _lightPos.x - obj->GetObjectLocation().x, _lightPos.y - obj->GetObjectLocation().y, _lightPos.z - obj->GetObjectLocation().z);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, obj->GetTexture());
	glUniform1i(_textureID, 0);


	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, obj->GetVertexBuffer());
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, obj->GetUVBuffer());
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, obj->GetNormalBuffer());
	glVertexAttribPointer(
		2,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);


	glDrawArrays(GL_TRIANGLES, 0, obj->GetVertexSize());

	printf("%s (%.2f, %.2f, %.2f)\n", obj->GetName().c_str(), obj->GetObjectLocation().x, obj->GetObjectLocation().y, obj->GetObjectLocation().z);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Renderer::EndDraw()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Renderer::ReleaseMemory()
{
	glDeleteProgram(_programID);
	glDeleteVertexArrays(1, &_vertexArrayID);

	glfwTerminate();
}
#pragma once

#include "../include/GL/glew.h"
#include "../include/GLFW/glfw3.h"


enum class Movement
{
	IDLE,
	LEFT,
	RIGHT
};

class InputManager
{
private:
	GLFWwindow* _window;

	bool _leftKeyDown;
	bool _rightKeyDown;

	InputManager();

public:
	~InputManager();

	static InputManager& GetInstance();

	void InitiWindow(GLFWwindow* window);

	Movement GetKey() const;
	Movement GetKeyDown();
	Movement GetKeyUp();
};
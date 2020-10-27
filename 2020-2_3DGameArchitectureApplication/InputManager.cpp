#include "InputManager.h"

#include "Renderer.h"


InputManager::InputManager()
{
	_window = Renderer::GetInstance().GetWindow();

	_leftKeyDown = false;
	_rightKeyDown = false;
}

InputManager::~InputManager()
{

}


InputManager& InputManager::GetInstance()
{
	static InputManager instance;

	return instance;
}


Movement InputManager::GetKey() const
{
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		return Movement::LEFT;
	}
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		return Movement::RIGHT;
	}
	else
	{
		return Movement::IDLE;
	}
}
Movement InputManager::GetKeyDown()
{
	if (!_leftKeyDown && glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		_leftKeyDown = true;
		return Movement::LEFT;
	}
	if (!_rightKeyDown && glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		_rightKeyDown = true;
		return Movement::RIGHT;
	}
	
	if (_leftKeyDown && glfwGetKey(_window, GLFW_KEY_A) == GLFW_RELEASE)
	{
		_leftKeyDown = false;
	}
	if (_rightKeyDown && glfwGetKey(_window, GLFW_KEY_D) == GLFW_RELEASE)
	{
		_rightKeyDown = false;
	}

	return Movement::IDLE;
}
Movement InputManager::GetKeyUp()
{
	if (_leftKeyDown && glfwGetKey(_window, GLFW_KEY_A) == GLFW_RELEASE)
	{
		_leftKeyDown = false;
		return Movement::LEFT;
	}
	if (_rightKeyDown && glfwGetKey(_window, GLFW_KEY_D) == GLFW_RELEASE)
	{
		_rightKeyDown = false;
		return Movement::RIGHT;
	}

	if (!_leftKeyDown && glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		_leftKeyDown = true;
	}
	if (!_rightKeyDown && glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		_rightKeyDown = true;
	}

	return Movement::IDLE;
}
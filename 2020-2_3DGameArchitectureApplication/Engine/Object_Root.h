#pragma once

#include "NonRenderableObject.h"
#include "GameLogic.h"
#include "Renderer.h"


class RootScene : public NonRenderableObject
{
public:
	RootScene(std::string obj_name) : NonRenderableObject(obj_name)
	{
		GameLogic::GetInstance().AddUpdatableObj(this);
		Renderer::GetInstance().RegistRootObject(this);
	}
};
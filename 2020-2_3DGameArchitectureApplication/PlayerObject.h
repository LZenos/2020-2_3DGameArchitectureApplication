#pragma once

#include "Engine/RenderableObject.h"


class PlayerObject : public RenderableObject
{
private:
	int _score;

public:
	PlayerObject();


	virtual void OnCollision(BoxCollider* collider) override;
};
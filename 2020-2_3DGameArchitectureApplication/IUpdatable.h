#pragma once


class IUpdatable
{
public:
	virtual void Init() = 0;
	
	virtual void Update() = 0;
};
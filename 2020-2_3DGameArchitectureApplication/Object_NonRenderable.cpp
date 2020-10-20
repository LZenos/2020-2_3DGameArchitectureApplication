#include "Object_NonRenderable.h"

#include <stdio.h>
#include <string>


NonRenderableObject::NonRenderableObject(std::string object_name) : Object(object_name)
{

}

NonRenderableObject::~NonRenderableObject()
{

}


void NonRenderableObject::Update()
{
	printf("%s (%.2f, %.2f, %.2f) (Invisible)\n", GetName().c_str(), GetObjectLocation().x, GetObjectLocation().y, GetObjectLocation().z);
}


void NonRenderableObject::ReleaseMemory()
{
	delete this;
}
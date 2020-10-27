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
	
}


void NonRenderableObject::ReleaseMemory()
{
	delete this;
}
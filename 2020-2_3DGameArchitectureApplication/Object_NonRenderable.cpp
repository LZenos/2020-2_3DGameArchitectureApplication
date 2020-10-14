#include "Object_NonRenderable.h"


NonRenderableObject::NonRenderableObject(std::string object_name) : Object(object_name)
{

}

NonRenderableObject::~NonRenderableObject()
{

}


void NonRenderableObject::ReleaseMemory()
{
	delete this;
}
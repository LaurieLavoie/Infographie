#pragma once

#include "Entity.h"
#include "Camera.h"

//* A scene. duh.
class Scene
{
public:
	Scene();
	~Scene();

	Entity& getRoot();
	
	Camera mainCamera;

private:
	// Empty entity that acts as the root of the entities hierarchy.
	Entity root;
};


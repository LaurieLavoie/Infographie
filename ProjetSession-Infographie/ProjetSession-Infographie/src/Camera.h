#pragma once

#include "ofEasyCam.h"

#include "Entity.h"


class Camera :
	public Entity
{
public:
	Camera();
	virtual ~Camera();

	ofCamera& getOfCamera();
};


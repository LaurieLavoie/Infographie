#pragma once

#include "ofEasyCam.h"

#include "Entity.h"


class Camera :
	public Entity
{
public:
	Camera();
	virtual ~Camera();

	void setOrtho(bool val);
	bool isOrtho();

	ofCamera& getOfCamera();
};


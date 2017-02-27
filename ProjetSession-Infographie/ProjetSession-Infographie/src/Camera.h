#pragma once

#include <cmath>

#include "ofEasyCam.h"

#include "Entity.h"


#define PI 3.14159265358979323846f
#define DEG_TO_RAD(deg) ((deg/360.0f) * (2*PI))
#define RAD_TO_DEG(rad) ((rad/(2*PI)) * (360.0f))


class Camera :
	public Entity
{
public:
	Camera();
	virtual ~Camera();

	void setOrtho(bool val);
	bool isOrtho();

	void setAspectRatio(float f);
	float getAspectRatio();

	void setNearClip(float f);
	void setFarClip(float f);
	void setVerticalFov(float degrees);
	void setHorizontalFov(float degrees);

	float getNearClip();
	float getFarClip();
	float getVerticalFov();
	float getHorizontalFov();

	ofCamera& getOfCamera();

private:
	float aspectRatio;
};


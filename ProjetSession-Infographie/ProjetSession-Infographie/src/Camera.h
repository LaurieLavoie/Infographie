#pragma once

#include <cmath>

#include "ofEasyCam.h"

#include "Entity.h"


#define PI 3.14159265358979323846f
#define DEG_TO_RAD(deg) (((deg)/360.0f) * (2*PI))
#define RAD_TO_DEG(rad) (((rad)/(2*PI)) * (360.0f))


class Camera :
	public Entity
{
public:
	Camera();
	virtual ~Camera();

	/// angles are in rad
	static float HFovToVFov(float hFov, float aspect) {
		return 2.0f * atan(tan(hFov / 2.0f) / aspect);
	}

	/// angles are in rad
	static float VFovToHFov(float vFov, float aspect) {
		return 2.0f * atan(tan(vFov / 2.0f) * aspect);
	}

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

	float getLongitude();
	void setLongitude(float longitude);
	float getLatitude();
	void setLatitude(float latitude);
	float getOrbitRadius();
	void setOrbitRadius(float radius);
	ofVec3f getOrbitOrigin();
	void setOrbitOrigin(const ofVec3f& centerPoint);

private:
	float aspectRatio;

	float longitude;
	float latitude;
	float orbitRadius;
	ofVec3f orbitOrigin;
};


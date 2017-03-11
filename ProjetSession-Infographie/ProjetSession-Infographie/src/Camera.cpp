#include "Camera.h"



Camera::Camera() :
	longitude(0.0f), latitude(0.0f), orbitRadius(300.0f), orbitOrigin(0.0f, 0.0f, 0.0f)
{
	this->setAspectRatio(1.666f);
	this->node.reset(new ofCamera);

	this->orbit(longitude, latitude, orbitRadius, orbitOrigin);
}


Camera::~Camera()
{
}


void Camera::setOrtho(bool val)
{
	if (val)
	{
		this->getOfCamera().enableOrtho();
	}
	else
	{
		this->getOfCamera().disableOrtho();
	}
}


bool Camera::isOrtho()
{
	return this->getOfCamera().getOrtho();
}

void Camera::setAspectRatio(float f)
{
	this->aspectRatio = f;
}

float Camera::getAspectRatio()
{
	// TODO use the actual aspect ration instead of 1.666f
	return this->aspectRatio;
}

void Camera::setNearClip(float f)
{
	this->getOfCamera().setNearClip(f);
}

void Camera::setFarClip(float f)
{
	this->getOfCamera().setFarClip(f);
}

void Camera::setVerticalFov(float degrees)
{
	this->getOfCamera().setFov(degrees);
}

void Camera::setHorizontalFov(float degrees)
{
	float hfov = DEG_TO_RAD(degrees);
	
	float vfov = RAD_TO_DEG(HFovToVFov(hfov, this->getAspectRatio()));

	this->getOfCamera().setFov(vfov);
}

float Camera::getNearClip()
{
	return this->getOfCamera().getNearClip();
}

float Camera::getFarClip()
{
	return this->getOfCamera().getFarClip();
}

float Camera::getVerticalFov()
{
	return this->getOfCamera().getFov();
}

float Camera::getHorizontalFov()
{
	float vfov = DEG_TO_RAD(this->getVerticalFov());

	float hfov = RAD_TO_DEG(Camera::VFovToHFov(vfov,this->getAspectRatio()));

	return hfov;
}


ofCamera & Camera::getOfCamera()
{
	return *(static_cast<ofCamera*>(this->node.get()));
}

float Camera::getLongitude()
{
	return longitude;
}

void Camera::setLongitude(float longitude)
{
	this->longitude = longitude;
	this->orbit(longitude, latitude, orbitRadius, orbitOrigin);
}

float Camera::getLatitude()
{
	return latitude;
}

void Camera::setLatitude(float latitude)
{
	this->latitude = latitude;
	this->orbit(longitude, latitude, orbitRadius, orbitOrigin);
}

float Camera::getOrbitRadius()
{
	return orbitRadius;
}

void Camera::setOrbitRadius(float radius)
{
	this->orbitRadius = radius;
	this->orbit(longitude, latitude, radius, orbitOrigin);
}

ofVec3f Camera::getOrbitOrigin()
{
	return orbitOrigin;
}

void Camera::setOrbitOrigin(const ofVec3f & centerPoint)
{
	this->orbitOrigin = centerPoint;
	this->orbit(longitude, latitude, orbitRadius, centerPoint);
}

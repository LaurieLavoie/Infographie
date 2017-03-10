#include "Camera.h"



Camera::Camera()
{
	this->setAspectRatio(1.666f);
	this->node.reset(new ofCamera);
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

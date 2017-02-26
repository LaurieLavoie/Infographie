#include "Camera.h"



Camera::Camera()
{
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


ofCamera & Camera::getOfCamera()
{
	return *(static_cast<ofCamera*>(this->node.get()));
}

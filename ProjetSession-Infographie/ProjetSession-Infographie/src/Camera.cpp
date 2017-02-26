#include "Camera.h"



Camera::Camera() :
	_isOrtho(false)
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

	this->_isOrtho = val;
}


bool Camera::isOrtho() const
{
	return this->_isOrtho;
}


ofCamera & Camera::getOfCamera()
{
	return *(static_cast<ofCamera*>(this->node.get()));
}

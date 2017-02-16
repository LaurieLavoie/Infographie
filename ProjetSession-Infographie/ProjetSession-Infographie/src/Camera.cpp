#include "Camera.h"



Camera::Camera()
{
	this->node.reset(new ofCamera);
}


Camera::~Camera()
{
}

ofCamera & Camera::getOfCamera()
{
	return *(static_cast<ofCamera*>(this->node.get()));
}

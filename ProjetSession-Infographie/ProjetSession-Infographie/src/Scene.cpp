#include "Scene.h"


Scene::Scene()
{

}

Scene::~Scene()
{
}

Entity & Scene::getRoot()
{
	return this->root;
}

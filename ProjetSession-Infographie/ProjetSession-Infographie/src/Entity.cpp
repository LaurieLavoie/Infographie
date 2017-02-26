#include "Entity.h"

#include <algorithm>


Entity::Entity()
{
	this->node.reset(new ofNode());
}

Entity::Entity(ofNode* node)
{
	this->node.reset(node);
}

Entity::~Entity()
{
}


void Entity::clearParent()
{
	this->parent = nullptr;
	this->node->clearParent();
}

void Entity::setParent(Entity& parent)
{
	this->parent = &parent;
	this->node->setParent( *(parent.node.get()) );
}


void Entity::clearChildren()
{
	this->children.clear();
}

void Entity::addChild(const std::shared_ptr<Entity>& child)
{
	this->children.push_back(child);
	child->setParent(*this);
}

void Entity::removeChild(const const std::shared_ptr<Entity>& child)
{
	std::remove(std::begin(this->children), std::end(this->children), child);
}

std::vector<std::shared_ptr<Entity>>& Entity::getChildren()
{
	return this->children;
}

// Please don't call ofNode::clearParent or ofNode::setParent, thank you.
ofNode& Entity::getOfNode()
{
	return *(this->node.get());
}

void Entity::draw()
{
	this->getOfNode().draw();
	std::for_each(std::begin(this->children), std::end(this->children), [](std::shared_ptr<Entity>& child) {
		child->draw();
	});
}

void Entity::setPosition(const ofVec3f & p)
{
	this->node->setPosition(p);
}

void Entity::setOrientation(const ofVec3f & o)
{
	this->node->setOrientation(o);
}

void Entity::setOrientation(const ofQuaternion & q)
{
	this->node->setOrientation(q);
}

void Entity::setScale(const ofVec3f & s)
{
	this->node->setScale(s);
}

void Entity::setScale(float s)
{
	this->node->setScale(s);
}

ofVec3f Entity::getPosition() const
{
	return this->node->getPosition();
}

ofVec3f Entity::getOrientationEuler() const
{
	return this->node->getOrientationEuler();
}

ofQuaternion Entity::getOrientationQuat() const
{
	return this->node->getOrientationQuat();
}

ofVec3f Entity::getScale() const
{
	return this->node->getScale();
}

void Entity::lookAt(Entity& entityToLookAt)
{
	this->node->lookAt(entityToLookAt.getOfNode());
}

void Entity::orbit(float longitude, float latitude, float radius, Entity& entityToLookAt)
{
	this->node->orbit(longitude, latitude, radius, entityToLookAt.getOfNode());
}

void Entity::move(const ofVec3f & offset)
{
	this->node->move(offset);
}

void Entity::truck(float s)
{
	this->node->truck(s);
}

void Entity::boom(float s)
{
	this->node->boom(s);
}

void Entity::dolly(float s)
{
	this->node->dolly(s);
}

void Entity::tilt(float s)
{
	this->node->tilt(s);
}

void Entity::pan(float s)
{
	this->node->pan(s);
}

void Entity::roll(float s)
{
	this->node->roll(s);
}


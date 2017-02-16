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
	this->parent.reset();
	this->node->clearParent();
}

void Entity::setParent(const std::shared_ptr<Entity>& parent)
{
	this->parent = parent;
	if (parent.use_count() != 0) {
		this->node->setParent( *(this->parent->node.get()) );
	}
}


void Entity::clearChildren()
{
	this->children.clear();
}

void Entity::addChild(const std::shared_ptr<Entity>& child)
{
	this->children.push_back(child);
}

void Entity::removeChild(const const std::shared_ptr<Entity>& child)
{
	std::remove(std::begin(this->children), std::end(this->children), child);
}

std::vector<std::shared_ptr<Entity>>& Entity::getChildren()
{
	return this->children;
}

// Please don't call clearParent or setParent, thank you.
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

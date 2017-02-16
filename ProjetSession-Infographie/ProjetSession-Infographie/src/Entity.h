#pragma once

#include <vector>
#include <memory>

#include <ofNode.h>

//* Represents an object in the 3D world
class Entity
{
public:
	Entity();
	Entity(ofNode* node);
	virtual ~Entity();

	void clearParent();
	void setParent(const std::shared_ptr<Entity>& parent);

	void clearChildren();
	void addChild(const std::shared_ptr<Entity>& child);
	void removeChild(const std::shared_ptr<Entity>& child);
	std::vector<std::shared_ptr<Entity>>& getChildren();

	// Please don't call clearParent or setParent, thank you.
	virtual ofNode& getOfNode();

	virtual void draw();


protected:
	std::unique_ptr<ofNode> node;

private:
	std::shared_ptr<Entity> parent;
	std::vector<std::shared_ptr<Entity>> children;
};


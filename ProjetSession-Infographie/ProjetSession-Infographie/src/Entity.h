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
	void setParent(Entity& parent);

	void clearChildren();
	void addChild(const std::shared_ptr<Entity>& child);
	void removeChild(const std::shared_ptr<Entity>& child);
	std::vector<std::shared_ptr<Entity>>& getChildren();

	// Please don't call ofNode::clearParent or ofNode::setParent, thank you.
	virtual ofNode& getOfNode();

	virtual void draw();

	virtual void setPosition(const ofVec3f& p);
	virtual void setOrientation(const ofVec3f& o);
	virtual void setOrientation(const ofQuaternion& q);
	virtual void setScale(const ofVec3f& s);
	virtual void setScale(float s);

	virtual ofVec3f getPosition() const;
	virtual ofVec3f getOrientationEuler() const;
	virtual ofQuaternion getOrientationQuat() const;
	virtual ofVec3f getScale() const;

	void lookAt(Entity& entityToLookAt);
	void orbit(float longitude, float latitude, float radius, Entity& entityToLookAt);
	void orbit(float longitude, float latitude, float radius, const ofVec3f& entityToLookAt);

	void move(const ofVec3f& offset);

	void truck(float s);
	void boom(float s);
	void dolly(float s);
	void tilt(float s);
	void pan(float s);
	void roll(float s);

protected:
	std::unique_ptr<ofNode> node;

private:
	Entity* parent;
	std::vector<std::shared_ptr<Entity>> children;
};


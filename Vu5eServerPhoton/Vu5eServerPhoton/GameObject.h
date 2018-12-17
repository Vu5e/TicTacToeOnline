#ifndef GAMEOBJECT_H
#define APPLICATION_H

#include "vector.h"
#include "sprite.h"
#include "Matrix.h"
#include "Random.h"

enum TileOwner
{
	X = 0,
	O = 1,
	NOTOWNED = 2
};

class GameObject
{
protected:
	Sprite*	m_sprite;
	Color m_color;
	Vector m_position;
	Vector m_scale;
	Vector m_velocity;
	Vector m_acceleration;
	float m_radian;
	BlendMode m_blendMode;
	TileOwner TO_owner;


public:
	GameObject();
	GameObject(Sprite* sprite);
	GameObject(Sprite* sprite, float x, float y);
	GameObject(Sprite* sprite, float x, float y, float scaleX, float scaleY);
	~GameObject();

	void setSprite(Sprite* sprite);

	void setBlendMode(BlendMode blendMode);

	void setPos(Vector position);
	void setPos(float x, float y);
	Vector getPos();

	void setVelocity(Vector velocity);
	void setVelocity(float velocityX, float velocityY);
	Vector getVelocity();

	void setAcceleration(Vector acceleration);
	Vector getAcceleration();

	void setColor(Color color);
	void setColor(float r, float g, float b, float a);
	Color getColor();

	void setScale(Vector scale);
	void setScale(float xScale, float yScale);
	Vector getScale();

	void setRotation(float radian);
	float getRotation();

	void setOwner(TileOwner newOwner);
	void setOwner(int ownerNum);
	TileOwner getOwner();

	virtual void start();
	virtual void update(double elapsedTime);

	virtual void draw();

};

#endif
#pragma once
#include "Sprite.h"

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


public:
	GameObject();
	GameObject(Sprite* sprite);
	GameObject(Sprite* sprite, float x, float y);
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


	virtual void start();
	virtual void update(double elapsedTime);

	virtual void draw();

};


#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
	setPos(0.0f, 0.0f);
	setColor(1.0f, 1.0f, 1.0f, 1.0f);
	setScale(1.0f, 1.0f);
	setRotation(0);
	setBlendMode(BlendMode::NONE);
	setOwner(TileOwner::NOTOWNED);
}

GameObject::GameObject(Sprite* sprite)
{
	m_sprite = sprite;
	setPos(0.0f, 0.0f);
	setRotation(0);
	setColor(1.0f, 1.0f, 1.0f, 1.0f);
	setScale(1.0f, 1.0f);
	setBlendMode(BlendMode::NONE);
	setOwner(TileOwner::NOTOWNED);
}

GameObject::GameObject(Sprite* sprite, float x, float y)
{
	m_sprite = sprite;
	setPos(x, y);
	setRotation(0);
	setColor(1.0f, 1.0f, 1.0f, 1.0f);
	setScale(1.0f, 1.0f);
	setBlendMode(BlendMode::NONE);
	setOwner(TileOwner::NOTOWNED);
}

GameObject::GameObject(Sprite* sprite, float x, float y, float scaleX, float scaleY)
{
	m_sprite = sprite;
	setRotation(0);
	setPos(x, y);
	setColor(1.0f, 1.0f, 1.0f, 1.0f);
	setScale(scaleX, scaleY);
	setBlendMode(BlendMode::NONE);
	setOwner(TileOwner::NOTOWNED);
}

GameObject::~GameObject()
{
}

void GameObject::setSprite(Sprite* sprite)
{
	m_sprite = sprite;
}

void GameObject::setBlendMode(BlendMode blendMode)
{
	m_blendMode = blendMode;
}

void GameObject::setPos(Vector position)
{
	m_position = position;
}

void GameObject::setPos(float x, float y)
{
	m_position.set(x, y, 0);
}

Vector GameObject::getPos()
{
	return m_position;
}

void GameObject::setColor(Color color)
{
	m_color = color;
}

void GameObject::setColor(float r, float g, float b, float a)
{
	m_color.m_r = r;
	m_color.m_g = g;
	m_color.m_b = b;
	m_color.m_a = a;
}

Color GameObject::getColor()
{
	return m_color;
}

void GameObject::setScale(Vector scale)
{
	m_scale = scale;
}

void GameObject::setScale(float xScale, float yScale)
{
	m_scale.set(xScale, yScale, 0);
}

Vector GameObject::getScale()
{
	return m_scale;
}

void GameObject::setRotation(float radian)
{
	m_radian = radian;
}

float GameObject::getRotation()
{
	return m_radian;
}

void GameObject::setOwner(TileOwner newOwner)
{
	TO_owner = newOwner;
}

void GameObject::setOwner(int ownerNum)
{
	switch (ownerNum)
	{
	case 0: TO_owner = TileOwner::X; break;

	case 1: TO_owner = TileOwner::O; break;

	default: TO_owner = TileOwner::NOTOWNED; break;
	}
}

TileOwner GameObject::getOwner()
{
	return TO_owner;
}

void GameObject::setVelocity(Vector velocity)
{
	m_velocity = velocity;
}

void GameObject::setVelocity(float velocityX, float velocityY)
{
	m_velocity.set(velocityX, velocityY, 0);
}

Vector GameObject::getVelocity()
{
	return m_velocity;
}

void GameObject::setAcceleration(Vector acceleration)
{
	m_acceleration = acceleration;
}

Vector GameObject::getAcceleration()
{
	return m_acceleration;
}

void GameObject::start()
{

}

void GameObject::update(double elapsedTime)
{
	m_velocity += m_acceleration * elapsedTime;
	m_position += m_velocity * elapsedTime;
}

void GameObject::draw()
{
	glDepthMask(false);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);

	switch (m_blendMode)
	{
	case BlendMode::NONE:
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	}

	case BlendMode::ADDITIVE:
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		break;
	}

	case BlendMode::MULTIPLY:
	{
		glBlendFunc(GL_ZERO, GL_SRC_COLOR);
		break;
	}
	}
	m_sprite->draw(m_position, m_scale, m_radian, m_color);
}
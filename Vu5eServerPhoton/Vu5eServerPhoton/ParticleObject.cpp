#include "ParticleObject.h"

ParticleObject::ParticleObject()
{

}
/*
ParticleObject::ParticleObject(GameObject * newGameObject) //maybe sprite
{
	gameObj = newGameObject;

	scale = Vector(0.5f, 0.5f, 0.5f);
	rotation = 0.0f;

	objColor.SetColor(Color().White());
	SetPosition(Vector(defaultPos));
	SetVelocity(Vector(0, 0, 0));

	startLife = 1.0f;
	life = startLife;

	SetAcceleration(Vector(0, 0, 0));
}


void ParticleObject::SetVelocity(Vector newVelo)
{
	velocity = newVelo;
}

Vector ParticleObject::GetVelocity()
{
	return Vector();
}

void ParticleObject::SetAcceleration(Vector newAccel)
{
	acceleration = newAccel;
}

Vector ParticleObject::GetAcceleration()
{
	return acceleration;
}

void ParticleObject::ParticleStart()
{
}

void ParticleObject::ParticleUpdate(float deltaTime)//deltatime
{
	life -= deltaTime;

	Vector curPos = GetPosition();

	velocity = velocity + acceleration;

	curPos = curPos + velocity;

	SetPosition(curPos);
}

void ParticleObject::ParticleDraw()
{
	gameObj->GetSprite()->draw(position.mVal[0], position.mVal[1], scale, rotation, objColor);
}

void ParticleObject::SetStartLife(float seconds)
{
	startLife = seconds;
	life = startLife;
}

*/
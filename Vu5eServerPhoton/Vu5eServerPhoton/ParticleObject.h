#ifndef PARTICLEOBJECT_H
#define PARTICLEOBJECT_H

#include "GameObject.h"

class ParticleObject : public GameObject
{
private:


public:
	GameObject* gameObj;

	ParticleObject();

	ParticleObject(GameObject* gameObj);

	Vector velocity = { 0, 0, 0 };
	Vector acceleration = { 0, 0, 0 }; //acceleration is the movement of the individual particle

	float startLife = 1.0f;
	float life = startLife;

	void ParticleStart();
	void ParticleUpdate(float deltaTime);
	void ParticleDraw();

	void SetStartLife(float time);


	void SetVelocity(Vector newVelo);
	Vector GetVelocity();

	void SetAcceleration(Vector newAccel);
	Vector GetAcceleration();


};

#endif

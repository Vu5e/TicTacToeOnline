
#ifndef PARTICLEAFFECTOR_H
#define PARTICLEAFFECTOR_H

#include "ParticleObject.h"

class ParticleAffector
{
protected:

public:
	virtual void affectParticleUpdate(ParticleObject* particle, float deltaTime) = 0;
};

#endif
#ifndef COLORAFFECTOR_H
#define COLORAFFECTOR_H

class ColorAffector : public ParticleAffector
{
public:
	float rChange, gChange, bChange, aChange;

	ColorAffector(Color colorOne, Color colorTwo, float colorChangeSpeed)
	{
		rChange = (colorTwo.r - colorOne.r) / colorChangeSpeed;
		gChange = (colorTwo.g - colorOne.g) / colorChangeSpeed;
		bChange = (colorTwo.b - colorOne.b) / colorChangeSpeed;
		aChange = (colorTwo.a - colorOne.a) / colorChangeSpeed;
	}

	virtual void affectParticleUpdate(ParticleObject* particle, float deltaTime) override
	{
		Color particleColor = particle->GetColor();

		particle->SetColor(Color(particleColor.r + rChange * deltaTime, particleColor.g + gChange * deltaTime, particleColor.b + bChange * deltaTime, particleColor.a + aChange * deltaTime));

	}
};

#endif
#ifndef SCALEAFFECTOR_H
#define SCALEAFFECTOR_H

class ScaleAffector : public ParticleAffector
{
public:
	Vector scaleSize;

	ScaleAffector(Vector initSize, Vector finalSize, float scaleChangeSpeed)
	{
		scaleSize = (finalSize - initSize) / scaleChangeSpeed;
	}

	virtual void affectParticleUpdate(ParticleObject* particle, float deltaTime) override
	{
		Vector scale = particle->GetScale();

		particle->SetScale(particle->GetScale() + scaleSize * deltaTime);
	}
};

#endif
#ifndef WARPCHARGEAFFECTOR_H
#define WARPCHARGEAFFECTOR_H

class WarpChargeAffector : public ParticleAffector
{
public:
	Vector particleAcceleration;

	WarpChargeAffector()
	{

	}

	virtual void affectParticleUpdate(ParticleObject* particle, float deltaTime) override
	{
		Vector finalAccel = (particle->velocity + (particle->GetAcceleration() / sin(glfwGetTime()) - particle->GetAcceleration()) / 5);

		particleAcceleration = finalAccel;

		particle->SetVelocity(particleAcceleration);
	}
};

#endif

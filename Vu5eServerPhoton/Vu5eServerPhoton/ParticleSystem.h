#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "ParticleAffector.h"

/*Enum for Different Emitter Types. Will affect the shape of the emitter that spawns particles*/
enum Emitter
{
	EMITTER_POINT = 0,
	EMITTER_LINE,
	EMITTER_CIRCLE,
	EMITTER_ROTATION
};

class ParticleSystem
{
private:
	float particleStartLifeTime = 1.0f;

	float m_emissionRate;
	float m_emissionLevel; //Init Speed of particles
	float curEmissionCount; //To keep track of how many particles are emitted this frame. //not important because can use ForLoop instead

	int totalParticles;

	Vector defaultPos = { 640, 480, 0 };
	Vector m_position;

	Sprite* m_sprite;

	GameObject* m_gameObj;

	ParticleObject* particle;

public:
	std::list<ParticleObject*> m_ParticleList;
	std::list<ParticleAffector*> m_ParticleAffectorList;

	int maxParticles;

	Vector gravityForce = { 0, -0.0001f, 0 }; //!Default Gravity Force

	Emitter emitterType = Emitter::EMITTER_POINT;
	float emitterRange = 100.0f;
	float emitterRotSpeed = 1.0f;


	void SetDefaults(Sprite* sprite, float emissionRate, float emissionLevel)
	{
		m_sprite = sprite;
		m_gameObj = new GameObject(m_sprite);
		m_emissionRate = emissionRate;
		m_emissionLevel = emissionLevel;
	}

	ParticleSystem(Sprite* sprite) //ParticleObject* particle
	{
		m_emissionRate = 1.0f;
		m_emissionLevel = 0.1f;
		totalParticles = 0.0f;
	}

	//All Variables Defaulted
	ParticleSystem(Sprite* sprite, float emissionRate, float emissionLevel)
	{
		SetDefaults(sprite, emissionRate, emissionLevel);
	}

	ParticleSystem(Sprite* sprite, float lifeTime, int maximumParticles, float emissionRate, float emissionLevel)
	{
		SetDefaults(sprite, emissionRate, emissionLevel);
		particleStartLifeTime = lifeTime;
		maxParticles = maximumParticles;
	}

	ParticleSystem(Sprite* sprite, float lifeTime, int maximumParticles, float emissionRate, float emissionLevel, Vector startPos)
	{
		SetDefaults(sprite, emissionRate, emissionLevel);
		particleStartLifeTime = lifeTime;
		maxParticles = maximumParticles;
		m_position = startPos;
	}

	ParticleSystem(ParticleObject* particleObj, int maximumParticles, float emissionRate, float emissionLevel)
	{
		//...
		maxParticles = maximumParticles;
		totalParticles = 0;
		m_sprite = particleObj->GetSprite();
		m_gameObj = new GameObject(m_sprite);

		particle = new ParticleObject(particleObj->gameObj);

		m_emissionRate = emissionRate;
		m_emissionLevel = emissionLevel;
	}

	/*Adds this Affector type to m_PaticleAffectorList*/
	void AttachColorAffector(Color colorOne, Color colorTwo, float startLifeTime)
	{
		ColorAffector* colorOverLifetime = new ColorAffector(colorOne, colorTwo, startLifeTime);
		m_ParticleAffectorList.push_back(colorOverLifetime);
	}

	/*Adds this Affector type to m_PaticleAffectorList*/
	void AttachScaleAffector(Vector startScale, Vector endScale, float startLifeTime)
	{
		ScaleAffector* scaleOverLifetime = new ScaleAffector(startScale, endScale, startLifeTime);
		m_ParticleAffectorList.push_back(scaleOverLifetime);
	}

	/*Adds this Affector type to m_PaticleAffectorList*/
	void AttachWarpChargeAffector()
	{
		WarpChargeAffector* finalAccelAffector = new WarpChargeAffector();
		m_ParticleAffectorList.push_back(finalAccelAffector);
	}

	void ParticleSystemStart()
	{

		maxParticles = 1000;
		totalParticles = 0;
		m_gameObj = new GameObject(m_sprite);
	}


	void ParticleSystemUpdate(float deltaTime)
	{
		for each(ParticleObject* particle in m_ParticleList)
		{
			particle->SetAcceleration(Vector(particle->GetAcceleration().mVal[0] + gravityForce.mVal[0], particle->GetAcceleration().mVal[1] + gravityForce.mVal[1], particle->GetAcceleration().mVal[2]));
		}


		if (totalParticles <= maxParticles)
		{
			curEmissionCount += m_emissionRate;
			while (curEmissionCount >= 1.0f)
			{
				ParticleObject* newParticle = new ParticleObject(m_gameObj);

				switch (emitterType)
				{
				default:
				{
					newParticle->position = m_position;
				}break;
				case Emitter::EMITTER_LINE:
				{
					newParticle->position = Vector(Random().randf(m_position.mVal[0] - emitterRange, m_position.mVal[0] + emitterRange), m_position.mVal[1], m_position.mVal[2]);
				}break;
				case Emitter::EMITTER_CIRCLE:
				{
					float theta = Random().randf(0, M_2PI);
					newParticle->position = Vector(m_position.mVal[0] + cos(theta) * emitterRange, m_position.mVal[1] + sin(theta) * emitterRange, m_position.mVal[2]);
				}break;
				case Emitter::EMITTER_ROTATION:
				{
					float theta = glfwGetTime() * emitterRotSpeed;
					newParticle->position = Vector(m_position.mVal[0] + cos(theta) * emitterRange, m_position.mVal[1] + sin(theta) * emitterRange, m_position.mVal[2]);
				}break;
				}


				newParticle->velocity = Vector(0.0f, 0.0f, 0.0f);

				//circular Emitter
				float theta = Random().randf(0, M_2PI);

				newParticle->velocity = Vector(cos(theta), sin(theta), 0.0f);
				newParticle->SetStartLife(particleStartLifeTime);

				m_ParticleList.push_back(newParticle);

				curEmissionCount -= 1.0f;

				totalParticles++;
			}
		}


		/*Cycles through each particle in m_ParticleList to call ParticleUpdate() and erase from list if life <= 0.0f*/
		std::list <ParticleObject*>::iterator iter = m_ParticleList.begin();
		while (iter != m_ParticleList.end())
		{
			std::list <ParticleAffector*>::iterator affectorIter = m_ParticleAffectorList.begin();

			ParticleObject* po = *iter;

			if (po->life <= 0.0f)
			{
				iter = m_ParticleList.erase(iter++);

				delete po;
				totalParticles--;
			}
			else
			{
				//! Updates all Affectors in m_ParticleAffectorList
				while (affectorIter != m_ParticleAffectorList.end())
				{
					(*affectorIter)->affectParticleUpdate(po, deltaTime);
					affectorIter++;
				}

				po->ParticleUpdate(deltaTime);
				iter++;
			}
		}
	}


	void ParticleSystemDraw()
	{
		if (totalParticles != 0)
		{
			for (std::list<ParticleObject*>::iterator it = m_ParticleList.begin(); it != m_ParticleList.end(); ++it)
			{
				if ((*it) != nullptr)
				{
					(*it)->ParticleDraw();
				}
			}
		}
	}
};

#endif

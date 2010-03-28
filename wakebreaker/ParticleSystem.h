#ifndef _PARTICLESYSTEM_H_
#define _PARTICLESYSTEM_H_

#include "Base.h"
#include "Vector3.h"

struct Particle
{
	Vector3 m_pos;
	Vector3 m_velocity;
	int32 m_life;
};


class ParticleSystem
{
	Particle* m_particles;
	
	int32 m_numParticles;
	
	int32 m_maxLife;	//maximum life allowed to a particle

	Vector3 m_emitPoint;//point of birth	
	Vector3 m_dir;		//a normalized direction vector

public:
	ParticleSystem(){ m_particles = NULL; }
	~ParticleSystem(){ SAFE_ARRAY_DELETE(m_particles); }

	//moves the emission point
	void Move(const Vector3& newEmitPoint)
	{ m_emitPoint = newEmitPoint; }

	//Changes the particle system's direction
	void Redirect(const Vector3& dir)
	{ m_dir = dir; }
	
	//-----------------------------------
	//Resets the particle at index
	void ResetParticle(int index);

	//---------------------------------
	//Sets up the particle system
	void Initialize(int32 numParticles,int32 maxLife,
					Vector3 pos,Vector3 dir);

	//-------------------------------
	//Draws the beast
	void Render();
	
	//-------------------------------
	//Updates particle position and life, 
	//resets them if they need to be
	void Update();
};


#endif
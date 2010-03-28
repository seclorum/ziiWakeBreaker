#include <stdlib.h>
#include "ParticleSystem.h"

//-------------------------------------------
//Resets the particle at index
void ParticleSystem::ResetParticle(int index)
{
	Particle* p = &m_particles[index];
	//set the position
	p->m_pos = m_emitPoint;

	//reset the life
	p->m_life = (m_maxLife - 5) + rand()%10;

	//Add some variety to the velocities
	int32 factorX= DIVX( (rand()%ITOX(10)),FTOX(1.5));
	int32 factorY= DIVX( (rand()%ITOX(10)),ITOX(2));
	int32 factorZ= DIVX( (rand()%ITOX(10)),FTOX(1.5));

	//Assign them in, alter the direction by the factor
	p->m_velocity.x = MULX(factorX,m_dir.x);
	p->m_velocity.y = MULX(factorY,m_dir.y);
	p->m_velocity.z = MULX(factorZ,m_dir.z);
}
//----------------------------------------------------------
//Sets up the particle system
void ParticleSystem::Initialize(int32 numParticles,int32 maxLife,
								Vector3 pos,Vector3 dir)
{
	//assign in the particle system properties
	m_emitPoint = pos;
	m_dir = dir;
	m_numParticles = numParticles;
	m_maxLife = maxLife;
	//build the new array of particles
	m_particles = new Particle[numParticles];
	//initialize all the particles
	for(int i = 0 ; i < numParticles ; i++)
	{
		ResetParticle(i);
	}

}
//-------------------------------
//Updates particle position and life, resets them if they need to be
void ParticleSystem::Update()
{
	//loop through all the particles
	for(int i = 0 ; i < m_numParticles; i++)
	{
		//decrease life
		m_particles[i].m_life -= 1;
		//check for death
		if(m_particles[i].m_life < 0)
			//revive!
			ResetParticle(i);

		//move the particle
		m_particles[i].m_pos.x += m_particles[i].m_velocity.x;
		m_particles[i].m_pos.y += m_particles[i].m_velocity.y;
		m_particles[i].m_pos.z += m_particles[i].m_velocity.z;
	}
}
//---------------------------
//Draws the particle system
void ParticleSystem::Render()
{
	glPushMatrix();

	//Turn of texturing, it would be too expensive
	glDisable(GL_TEXTURE_2D);

	//Attenuate the particle size based on distance
	glPointSizex(ITOX(8));
	int32 coefficients[] = { FTOX(0),FTOX(0.05),FTOX(0.005) };
	glPointParameterxv(GL_POINT_DISTANCE_ATTENUATION,coefficients);

	glVertexPointer(3, GL_FIXED, sizeof(Particle), m_particles[0].m_pos.v);

	//Draw
	glDrawArrays(GL_POINTS, 0, m_numParticles);
	glEnable(GL_TEXTURE_2D);


	glPopMatrix();
}

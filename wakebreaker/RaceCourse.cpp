#include "RaceCourse.h"
#include "Math.h"
#include "Renderer.h"
#include "Base.h"
#include "Vector3.h"

//---------------------------------------------------------
//Adds racers to the race course and sets up the race course
void RaceCourse::Initialize(Racer* racers,int32 numRacers)
{
	//set the racers and the amount of them
	m_numRacers = numRacers;
	m_racers = racers;

	//place all the racers at the first checkpoint, each
	//racer a bit behind the one before him

	for(int i = 0 ; i < m_numRacers ; i++)
	{
		//set everyone at the starting checkpoint
		m_racers[i].NextCheckPoint(0);
		m_racers[i].CurrLap(0);
		
		Vector3 startPos(m_checkPoints[0].position());
		
		m_racers[i].m_ri->position(startPos);
		m_racers[i].NextCPPos(startPos);
		
	}
	m_racers[0].Rotate(ITOX(90));


	//load the textures for the checkpoints
	m_cpOnTex = new Texture;
	m_cpOnTex->Load(CHECKPOINTON);
	
	m_cpOffTex = new Texture;
	m_cpOffTex->Load(CHECKPOINTOFF);

	
	m_playerNextCP = 0;
}
//-------------------------------------------------------------------
//Generates a random race course within the donut described by min and max radius
void RaceCourse::Generate(const Vector3& center,int32 minRadius,int32 maxRadius,Info* info)
{
	//allocate space for the checkpoints
	m_checkPoints = new RenderInstance[MAX_CHECKPOINTS];

	//calculate the angle apart each checkpoint has to be
	int32 interval = DIVX( TWOPIX , ITOX(MAX_CHECKPOINTS) );
	int32 angle = 0;
	for(int i = 0 ; i < MAX_CHECKPOINTS ; i++)
	{
		//generate the x component
		int32 x = info->m_math->fcosf(angle);
		//translate it by a bit
		int32 randX = (rand()%(maxRadius - minRadius)) + minRadius;
		x = MULX(x,ITOX(randX)) + center.x;

		//generate the z component
		int32 z = info->m_math->fsinf(angle);
		//translate it
		int32 randZ = (rand()%(maxRadius - minRadius)) + minRadius;
		z = MULX(z,ITOX(randZ)) + center.z;

		//assign them in
		m_checkPoints[i].position(x,ITOX(1),z);
		m_checkPoints[i].renderData(info->m_mm->GetCheckPoint());
		m_checkPoints[i].scale(ITOX(1),ITOX(1),ITOX(1));
		Vector3 rot(FTOX(-90),0,0);
		m_checkPoints[i].rotation(rot);
	
		//advance the angle
		angle -= interval;
	
	}

}
//-----------------------------------------
void RaceCourse::Render(Renderer* renderer)
{
	glPushMatrix();
/*
	//loop through each checkpoint
	for(int i = 0 ; i < MAX_CHECKPOINTS ; i++)
	{
		m_checkPoints[i].renderData()->m_texture = m_cpOffTex;
		
		//if this is the player's destination checkpoint
		if(i == m_playerNextCP)
		{
			//render this one in a special color
			m_checkPoints[i].renderData()->m_texture = m_cpOnTex;
		}
		renderer->Render(&m_checkPoints[i]);
		
		//reset the texture
		m_checkPoints[i].renderData()->m_texture = NULL;
	}
*/

	m_checkPoints[m_playerNextCP].renderData()->m_texture = m_cpOnTex;
	renderer->Render(&m_checkPoints[m_playerNextCP]);
	m_checkPoints[m_playerNextCP].renderData()->m_texture = NULL;

	if(m_playerNextCP + 1 == MAX_CHECKPOINTS)
	{
		m_checkPoints[0].renderData()->m_texture = m_cpOffTex;
		renderer->Render(&m_checkPoints[0]);
		m_checkPoints[0].renderData()->m_texture = NULL;
	}
	else
	{
		m_checkPoints[m_playerNextCP + 1].renderData()->m_texture = m_cpOffTex;
		renderer->Render(&m_checkPoints[m_playerNextCP + 1]);
		m_checkPoints[m_playerNextCP + 1].renderData()->m_texture = NULL;
	}

	glPopMatrix();

}
//-----------------------------------------
//Updates the racers, returns 1 if player won, -1 if player lost, and 0
//if race is still in progress
int RaceCourse::Update()
{
	//loop through each racer
	for(int i = 0 ; i < m_numRacers ; i++)
	{
		//see if he has collided with the next checkpoint
		Vector3 nextCP = m_checkPoints[m_racers[i].NextCheckPoint()].position();
		Vector3 pos = m_racers[i].m_ri->position();
		
		int32 dist = MULX( (nextCP.x - pos.x),(nextCP.x - pos.x) ) +
					 MULX( (nextCP.z - pos.z),(nextCP.z - pos.z) );

		int32 radii = MULX(ITOX(3),ITOX(3));

		if(dist < radii )
		{
			//the player has reached the next checkpoint
			//assign him to the next checkpoint
			int CP = m_racers[i].NextCheckPoint() + 1;
			
			//he has reached the last checkpoint
			if(CP == MAX_CHECKPOINTS)
			{
				//increment his lap count
				m_racers[i].CurrLap(m_racers[i].CurrLap()+1);

				if(m_racers[i].CurrLap() == 3)
				{
					//we have a winner

					m_racers[i].SetFinished(true);
				}
				CP = 0;
			}
			//assign him his new checkpoint
			m_racers[i].NextCheckPoint(CP);
			m_racers[i].NextCPPos(m_checkPoints[CP].position());

			if(i == 0)
				m_playerNextCP = CP;

		}
	}
	return 1;
}
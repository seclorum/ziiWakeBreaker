#ifndef _Racer_H_
#define _Racer_H_

#include "RenderInstance.h"
#include "Renderer.h"
#include "Seascape.h"
#include "Base.h"
#include "ParticleSystem.h"

#include "Info.h"
#include "Math.h"


#define MAX_SPEED 1 //ship's maximum speed

//This is the player's ship class
class Racer
{
	int32 m_speed;	//ship's current speed
	Info* m_info;	//info class containing a math and modelmanager pointer
	
	int32 m_nextCheckPoint;		//which check point he's aiming for
	int32 m_currLap;			//which lap he's on

	bool m_hasRotated; //for rotation optimization
	
	
	ParticleSystem* m_spray;		//the water spray that shoots out
								//behind the boat

	//Keeps the racer inside the seascape
	void BoundsCheck();		

	friend class RaceCourse;
	
	void NextCheckPoint(int32 ncp) { m_nextCheckPoint = ncp; }

	void CurrLap(int32 cl) { m_currLap = cl; }

	void NextCPPos(const Vector3& p)
	{ m_nextCPPos = p; }

	Vector3 m_nextCPPos;
	Vector3 m_desiredDir;

	//Are we done with the race?
	void SetFinished(bool b) { m_finished = b; }

	bool m_up,			//used in making the boat bob slight
		 m_finished;	//whether or not we are done with the race

public:
	Vector3 m_dir;			//direction ship is pointing in
	RenderInstance* m_ri;	//ship's render instance

	Racer() : m_ri(NULL), m_speed(0), m_spray(NULL)  {}
	~Racer(){ SAFE_DELETE(m_ri); SAFE_DELETE(m_spray); }

	//Returns the current lap we're on
	int32 CurrLap() const { return m_currLap; }
	//Returns the number of the checkpoint we must reach
	int32 NextCheckPoint() const { return m_nextCheckPoint; }

	//Returns whether or not we are done with the race
	bool IsFinished() const { return m_finished; }

	//------------------------------
	//Set's up ships position and model
	void Initialize(Info* info,int32 model);

	//increases ship's speed
	inline void IncreaseSpeed(int32 s); 

	//resets ship's position and 
	inline void Reset(); 

	//sets the rotation for the ship
	void Rotate(int32 r); 

	//Updates the position and velocity of the spray
	void UpdateSpray();

	//updates ship (applies rotation and translation)
	void Update(Math* math); 

	//updates this to go towards his next checkpoint
	void UpdateAI(Math* math,Racer* player);

	//renders the ship
	inline void Render(Renderer* renderer);

	//return's ship position
	inline Vector3& Position() const { return m_ri->position(); }

};

//-----------------------------------------
//Renders the ship
inline void Racer::Render(Renderer* renderer)
{
	//draw the ship
	renderer->Render(m_ri);
	//draw the spray trail
	m_spray->Render();
}
//---------------------------------------
//Increases ship speed
inline void Racer::IncreaseSpeed(int32 s) 
{ 
	if(m_speed + s < FTOX(MAX_SPEED)) 
		m_speed += s; 
}
//-------------------------------
//Resets the ship's status
inline void Racer::Reset() 
{ 
	m_ri->position(FTOX(WORLD_WIDTH / 2),0,FTOX(WORLD_HEIGHT / 2)); 
}


#endif
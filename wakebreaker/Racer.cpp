#include "Racer.h"
//-----------------------------------------
void Racer::BoundsCheck()
{
	//check the player against each part fo the world,
	//slow him down if he hit
	Vector3 pos = m_ri->position();
	if(pos.x > ITOX(WORLD_WIDTH))
	{
		pos.x = ITOX(WORLD_WIDTH);
		m_speed = MULX(m_speed,FTOX(0.5));
	}
	if(pos.x < 0)
	{
		pos.x = 0;
		m_speed = MULX(m_speed,FTOX(0.5));
	}
	if(pos.z > ITOX(WORLD_HEIGHT))
	{
		pos.z = ITOX(WORLD_HEIGHT);
		m_speed = MULX(m_speed,FTOX(0.5));
	}
	if(pos.z < 0)
	{
		pos.z = 0;
		m_speed = MULX(m_speed,FTOX(0.5));
	}

	//make the racer bob up and down
	if(m_up && m_speed > 0)
		pos.y += MULX(FTOX(0.02),m_speed);
	else if(m_speed > 0)
		pos.y -= MULX(FTOX(0.02),m_speed);

	if(pos.y >= FTOX(0.2))
		m_up = false;

	if(pos.y < FTOX(-0.05))
		m_up = true;

	m_ri->position(pos);
}
//-----------------------------------------
void Racer::Initialize(Info* info,int32 model)
{
	m_up = true;
	m_finished = false;

	//get the 3d model data
	m_info = info;
	m_ri = new RenderInstance;
	switch(model)
	{
	case BOAT1:
		{ m_ri->renderData(info->m_mm->GetBoat1());	} break;
	case BOAT2:
	default:
		{ m_ri->renderData(info->m_mm->GetBoat2());	} break;
	}

	//rotate so he's always right side up
	Vector3 vec(-ITOX(90),0,ITOX(90));
	m_ri->rotation(vec);
	m_ri->scale(FTOX(0.5),FTOX(0.5),FTOX(0.5));

	//set up the position
	m_ri->position(FTOX(WORLD_WIDTH / 2),0,FTOX(WORLD_HEIGHT / 2));

	//update his rotation and direction
	Vector3 rot = m_ri->rotation();
	int32 rad = MULX(DEG2RADX,rot.y);

	m_dir.x = info->m_math->fcosf(rad);
	m_dir.z = info->m_math->fsinf(rad);

	m_hasRotated = true;

	//Initialize the particle system
	m_spray = new ParticleSystem;
	m_spray->Initialize(200,15,m_ri->position(),Vector3(ITOX(0),ITOX(1),ITOX(0)));
}

//--------------------------
//Rotates this object
void Racer::Rotate(int32 r)
{
	Vector3 vec = m_ri->rotation();

	//this makes sure the rotation doesn't exceed 360 degrees
	// the 23527424 is 360 in fixed point (hehe, micro optimization)
	if(vec.y + r > 23527424 || vec.y + r < -23527424)
		vec.y = 0;

	vec.y += r;

	m_ri->rotation(vec);

	m_hasRotated = true;
}
//------------------------------
void Racer::Update(Math* math)
{
	if(m_hasRotated)
	{
		//rotate the ship if needed
		Vector3 rot = m_ri->rotation();
		int32 rad = MULX(DEG2RADX,rot.y);

		m_dir.x = math->fcosf(rad);
		m_dir.z = math->fsinf(rad);
		m_hasRotated = false;
	}

	//move him in
	m_ri->Translate(MULX(m_speed,m_dir.x),0,MULX(-m_dir.z,m_speed));

	//Bounds check him against the world
	BoundsCheck();

	//slow him down
	if(m_speed - 966 > 0)
	{
		m_speed -= 966;
	}
	else if(m_speed - 966 < 0)
	{
		m_speed += 1966;
	}

	//halt him if too slow
	if(m_speed <= 2621 && m_speed >= -2621)
		m_speed = 0;

	//keep the particles with us
	UpdateSpray();

}
void Racer::UpdateAI(Math* math,Racer* player)
{
	//we hit an island, this on most cases, corrects the problem
	if(m_speed < 20000)
	{
		IncreaseSpeed(1553);
		//go around it
		m_dir.x = math->fcosf(MULX(ITOX(90),DEG2RADX));
		m_dir.z = math->fsinf(MULX(ITOX(90),DEG2RADX));
		m_hasRotated = false;

		//move him in
		m_ri->Translate(MULX(m_speed,m_dir.x),0,MULX(-m_dir.z,m_speed));

	}
	else
	{
		IncreaseSpeed(1553);

		//build a normalized direction vector
		m_desiredDir = m_ri->position() - m_nextCPPos;
		m_desiredDir.y = 0;

		int mag = sqrtx( (int32)(MULX(m_desiredDir.x,m_desiredDir.x) + (int32)MULX(m_desiredDir.z,m_desiredDir.z)) );
		int n = DIVX(ITOX(1),mag);
		m_desiredDir.x = MULX(m_desiredDir.x,n);
		m_desiredDir.z = MULX(m_desiredDir.z,n);

		//make the boat rotate the same as the player
		Vector3 playerRot = player->m_ri->rotation();
		playerRot.y + ITOX(5) + rand()%ITOX(20);
		m_ri->rotation(playerRot);

		//slow the AI down a little
		int32 randFac = DIVX(ITOX(8) + rand()%4,ITOX(10));
		int32 finalX = MULX(-m_desiredDir.x,m_speed);
		finalX = MULX(finalX,randFac);	//,rot);	/* !J! */

		int32 finalZ = MULX(-m_desiredDir.z,m_speed);
		finalZ = MULX(finalZ,randFac);	//,rot);  /* !J! */
		//move the boat
		m_ri->Translate(finalX,0,finalZ);

	}
	//keep him in the water
	BoundsCheck();
	//move the spray trail with him
	UpdateSpray();
}

void Racer::UpdateSpray()
{
	//keep it the spray trail right with the boat
	m_spray->Move(m_ri->position());

	//also keep it spraying in the right direction
	Vector3 newDir = m_dir;
	if(m_speed > 0)
	{
		newDir.x = MULX(newDir.x,MULX(FTOX(1),FTOX(1)));
		newDir.y = FTOX(0.1);
		newDir.z = MULX(newDir.z,MULX(-FTOX(1),FTOX(1)));
	}
	else
	{
		newDir.x = 0;
		newDir.y = 0;
		newDir.z = 0;
	}
	m_spray->Redirect(newDir);

	m_spray->Update();
}

#ifndef _RACECOURSE_H_
#define _RACECOURSE_H_

#define MAX_CHECKPOINTS 16

#include "Info.h"
#include "RenderInstance.h"
#include "Renderer.h"
#include "Racer.h"
#include "Texture.h"

class RaceCourse
{

	Racer* m_racers;		//the racers
	int32 m_numRacers;		//number of racers

	RenderInstance* m_checkPoints;		//checkpoints
	Texture* m_cpOnTex, *m_cpOffTex;	//the on and off checkpoint textures

	int32 m_playerNextCP;	//the player's destination checkpoint


public:
	RaceCourse()
	{ m_checkPoints = NULL; }

	~RaceCourse()
	{
		SAFE_ARRAY_DELETE(m_checkPoints);
		SAFE_DELETE(m_cpOnTex);
		SAFE_DELETE(m_cpOffTex);
	}


	//Initializes the RaceCourse with racers
	void Initialize(Racer* racers,int32 numRacers);

	//Generates a random race course
	void Generate(const Vector3& center,int32 minRadius,int32 maxRadius,
				  Info* info);

	//Renders the race course
	void Render(Renderer* renderer);

	//Updates racer checkpoint and lap info for all racers
	int Update();

};



#endif

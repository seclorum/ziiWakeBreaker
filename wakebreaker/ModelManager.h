#ifndef _MODELMANAGER_H_
#define _MODELMANAGER_H_

#include "Base.h"
#include "RenderData.h"


class ModelManager
{

	RenderData *m_boat2, *m_boat1,
			   *m_chest,
			   *m_checkPoint;

	RenderData* m_island1, *m_island2;
	
public:
	ModelManager() : m_boat1(NULL), m_boat2(NULL), m_chest(NULL),
					 m_island1(NULL), m_island2(NULL),
					 m_checkPoint(NULL)
	{}
	~ModelManager()
	{

		SAFE_DELETE(m_boat2);
		SAFE_DELETE(m_boat1);
		SAFE_DELETE(m_chest);

		SAFE_DELETE(m_island1);
		SAFE_DELETE(m_island2);
	
		
		SAFE_DELETE(m_checkPoint);
	}

	void Initialize() {  }


	//These return RenderData's with the requested model

	RenderData* GetBoat1();
	RenderData* GetBoat2();

	RenderData* GetChest();

	RenderData* GetRandomSeascapeModel();

	RenderData* GetIsland1();
	RenderData* GetIsland2();


	RenderData* GetCheckPoint();


};




#endif
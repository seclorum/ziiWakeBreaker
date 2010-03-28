#ifndef _SEASCAPE_H_
#define _SEASCAPE_H_

#include "RenderInstance.h"
#include "ModelManager.h"
#include "Base.h"
#include "Renderer.h"

#define WORLD_WIDTH		175	
#define WORLD_HEIGHT	175
//This class represents the islands and the water and is responsible
//for loading, drawing, placing and updating them

class Seascape
{
	RenderInstance* m_models;	//the islands
	uint16 m_numModels;			//number of islands

	RenderInstance* m_sea;		//the water quad							

	//used in water animation
	int32 m_texTranslate;	
	bool m_waterMoved;	

public:
	Seascape() : m_models(NULL), m_sea(NULL)
	{}
	~Seascape()
	{ 
		RenderData* temp = m_sea->renderData();
		delete temp;
		m_sea->renderData(NULL);

		SAFE_DELETE(m_sea); 
	}

	//sets everything up
	void Generate(ModelManager* mm);

	//checks if anything collided with the islands
	bool Collided(Vector3 pos,int32 radius);

	//renders the seascape
	void Render(Renderer* renderer);


	//Renders the water
	void RenderWater(Renderer* renderer);


};






#endif

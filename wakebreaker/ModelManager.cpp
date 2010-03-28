#include <stdlib.h>
#include "island1.h"
#include "island2.h"
#include "ModelManager.h"
#include "Texture.h"
#include "boat2.h"
#include "boat1.h"
#include "checkpoint.h"

RenderData* ModelManager::GetChest()
{
	return NULL;
}


RenderData* ModelManager::GetIsland1()
{
	if(!m_island1)
	{
		Texture* tex = new Texture;
		tex->Load(ISLAND1);

		m_island1 = Getisland1();
		m_island1->m_texture = tex;
	}
	return m_island1;
}
RenderData* ModelManager::GetIsland2()
{
	if(!m_island2)
	{
		Texture* tex = new Texture;
		tex->Load(ISLAND2);

		m_island2 = Getisland2();
		m_island2->m_texture = tex;
	}
	return m_island2;
}

RenderData* ModelManager::GetBoat2()
{
	if(!m_boat2)
	{
		Texture* tex = new Texture;
		tex->Load(BOAT2);

		m_boat2 = Getboat2();
		m_boat2->m_texture = tex;
	}
	return m_boat2;
}
RenderData* ModelManager::GetBoat1()
{
	if(!m_boat1)
	{
		Texture* tex = new Texture;
		tex->Load(BOAT1);

		m_boat1 = Getboat1();
		m_boat1->m_texture = tex;
	}
	return m_boat1;
}
RenderData* ModelManager::GetRandomSeascapeModel()
{
	//Generate a random number
	uint16 num = rand() % 2;

	if(num == 0)
	{
		return GetIsland1();
	}
	if(num == 1)
	{
		return GetIsland2();
	}

}
RenderData* ModelManager::GetCheckPoint()
{
	if(!m_checkPoint)
	{
		m_checkPoint = Getcheckpoint();
	}
	return m_checkPoint;
}

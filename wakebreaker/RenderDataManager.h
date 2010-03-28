#ifndef _RENDERDATAMANAGER_H_
#define _RENDERDATAMANAGER_H_

#include "RenderData.h"

class RenderDataManager
{
	RenderData* m_renderDataList;
public:

	RenderDataManager() : m_renderDataList(NULL)
	{}
	~RenderDataManager()
	{
		SAFE_DELETE(m_renderDataList);
	}

	inline void AddData(RenderData* data);
	inline RenderData* GetData(RenderData* desiredData);
	inline void ReleaseData(RenderData* data);
	inline void ClearData(RenderData* data);
};

//------------------------------------------------------
//Pop the new data onto the front of the render data list
void RenderDataManager::AddData(RenderData* data)
{
	if(m_renderDataList)
	{
		RenderData* temp = m_renderDataList;
		m_renderDataList = data;		
		m_renderDataList->m_next = temp;
		m_renderDataList->m_prev = NULL;
		temp->m_prev = m_renderDataList;
	}
	else
	{
		m_renderDataList = data;
		data->m_next = NULL;
		data->m_prev = NULL;
	}
}

//-----------------------------------
RenderData* RenderDataManager::GetData(RenderData* desiredData)
{
	//build a temporary id
	uint32 tempID = desiredData->m_vertices/* + 
					desiredData->m_texCoords + 
					desiredData->m_colorData + 
					m_renderState*/;

	//check to see if we already have this render data loaded
	RenderData* curr = m_renderDataList;
	while(curr != NULL)
	{
		//if this data already exists, return an existing pointer to it
		if(curr->m_id == tempID)
		{
			SAFE_DELETE(desiredData);
			curr->m_references++;
			return curr;
		}
	
		curr = curr->m_next;
	}

	desiredData->m_id = tempID;
	//otherwise, we add it to the renderDataList and on we go
	desiredData->m_references++;
	
	AddRenderData(desiredData)


}
//----------------------------------
//Releases a render data
void RenderDataManager::ReleaseData(RenderData* rdata)
{
	m_references--;
	if(m_references == 0)
	{
		//if this is the head of the list
		if(rdata == m_renderDataList)
		{
			m_renderDataList = rdata->m_next;	
			m_renderDataList->m_prev = NULL;
		}
		//if this is the tail
		else if(!rdata->m_next && rdata->m_prev)
		{
			rdata->m_prev->m_next = NULL;
		}
		//middle of the list
		else
		{
			rdata->m_prev->m_next = rdata->m_next;
			rdata->m_next->m_prev = rdata->m_prev;	

		}
		SAFE_DELETE(rdata)
	}
}
//----------------------------------------------------
//Deletes all the left over render data
void RenderDataManager::ClearData(RenderData* renderDataList)
{
	
	RenderData* curr = renderDataList;
	while(curr != NULL)
	{
		curr->m_references = 0;
		curr = curr->m_next;
	}
	curr = renderDataList;
	while(curr != NULL)
	{
		CRenderData* temp = curr->m_next;
		ReleaseRenderData(curr);
		curr = temp;
	}
}

#endif
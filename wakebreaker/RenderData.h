#ifndef _RENDERDATA_H_
#define _RENDERDATA_H_

//This bit of code details the RenderData system.  
//RenderData must be used to render anything 3D. 

//only the model manager creates these RenderDatas,
//everything else requests them from the model manager
#include "Color4.h"
#include "Vector3.h"
#include "Texture.h"

struct TexCoord2
{
	int32 u,v;
};


struct RenderData
{
	RenderData() : m_indices(NULL), m_vertices(NULL), m_texCoords(NULL),
				   m_texture(NULL), m_colorData(NULL),
				   m_indexDataType(GL_UNSIGNED_SHORT)

	{}
	~RenderData()
	{
		SAFE_DELETE(m_texture);
		SAFE_ARRAY_DELETE(m_vertices);
		SAFE_ARRAY_DELETE(m_indices);
		SAFE_ARRAY_DELETE(m_colorData);
		SAFE_ARRAY_DELETE(m_texCoords);
	}

	Texture* m_texture;
	
	uint16* m_indices;		
	Vector3* m_vertices;	
	TexCoord2* m_texCoords;	
	Color4* m_colorData;
	
	uint16 m_numVertices;
	uint16 m_numTexCoords;
	uint16 m_numColorData;
	
	GLuint m_indexDataType;
	uint16 m_numIndices;
};


#endif
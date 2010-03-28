#ifndef _RENDERINSTANCE_H_
#define _RENDERINSTANCE_H_

#include "RenderData.h"
#include "Vector3.h"

//This stores the positional data and renderable data of a an object

class RenderInstance
{
	RenderData* m_rdata;	//the render data, as requested from the modelmanager
	
	Vector3 m_pos,
			m_rotation,
			m_scale;


public:
	RenderInstance() : m_pos(0,0,0), 
					   m_rotation(0,0,0), 
					   m_scale(65536,65536,65536)
	{}
	~RenderInstance()
	{
		//all renderData is obtained from the
		//model manager, which deletes it
	}

	inline void renderData(RenderData* rd) { m_rdata = rd; }
	inline RenderData* renderData() { return m_rdata; }

	inline void position(const Vector3& p) { m_pos = p; }
	inline void position(int32 x,int32 y,int32 z) { m_pos.x = x; m_pos.y = y; m_pos.z = z; }
	inline Vector3& position() { return m_pos; }

	inline void rotation(const Vector3& p) { m_rotation = p; }
	inline Vector3& rotation() { return m_rotation; }

	inline void Rotate(const Vector3& p) 
	{
		//cap all the values
		if(m_rotation.x + p.x > 23527424 || m_rotation.x + p.x < -23527424)
			m_rotation.x = 0;
	
		if(m_rotation.y + p.y > 23527424 || m_rotation.y + p.y < -23527424)
			m_rotation.y = 0;
	
		if(m_rotation.z + p.z > 23527424 || m_rotation.z + p.z < -23527424)
			m_rotation.z = 0;

		m_rotation += p; 
	}

	inline void scale(const Vector3& s) { m_scale = s; }
	inline void scale(int32 x,int32 y,int32 z)
	{ 
		m_scale.x = x;
		m_scale.y = y;
		m_scale.z = z;
	}
	inline Vector3& scale() { return m_scale; }

	inline void Translate(const Vector3& trans)
	{
		m_pos += trans;
	}
	inline void Translate(int32 x,int32 y,int32 z)
	{
		m_pos.x += x;
		m_pos.y += y;
		m_pos.z += z;
	}
};


#endif

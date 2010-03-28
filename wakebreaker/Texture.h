#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Base.h"

//used to identify which texture to load
enum TexID
{
	WATER,
	ISLAND1,
	ISLAND2,
	CHEST,
	BOAT2,
	BOAT1,
	SPLASH,
	VICTORY,
	DEFEAT,
	CHECKPOINTON,
	CHECKPOINTOFF
};

class Texture
{
	GLuint m_id;

public:
	Texture(){}
	~Texture(){}

	inline GLuint id() const { return m_id; }

	//loads a texture based on the TexID
	void Load(uint16 id);

	//binds this texture
	inline void Bind() { glBindTexture(GL_TEXTURE_2D, m_id); }
};


#endif

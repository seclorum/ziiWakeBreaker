#include "Seascape.h"

void Seascape::Generate(ModelManager* mm)
{
	m_waterMoved = true;

	m_numModels = 15;
	m_models = new RenderInstance[m_numModels];

	for(uint16 i = 0 ; i < m_numModels ; i++)
	{
		//Get a random island model
		m_models[i].renderData(mm->GetRandomSeascapeModel());

		//generate a random x and z
		uint32 x = rand() % WORLD_WIDTH;
		uint32 z = rand() % WORLD_HEIGHT;

		//set our random position
		m_models[i].position(ITOX(x),0,ITOX(z));
	
		//generate a random rotation
		uint32 rotY = rand() % 360;
		Vector3 rot(FTOX(-90),FTOX(rotY),0);
		m_models[i].rotation(rot);

	}

	//Set up the sea floor
	Vector3* tempVerts = new Vector3[4];
	tempVerts[0] = Vector3(FTOX(-2),0,FTOX(-2));
	tempVerts[1] = Vector3(FTOX(-2),0,FTOX((WORLD_HEIGHT / 2) + 2));
	tempVerts[2] = Vector3(FTOX((WORLD_WIDTH / 2)  + 2),0,FTOX(-2));
	tempVerts[3] = Vector3(FTOX((WORLD_WIDTH / 2) + 2),0,FTOX((WORLD_HEIGHT / 2) + 2));
	
	//set up texture coords
	TexCoord2* texCoords = new TexCoord2[4];
	texCoords[0].u = 0;
	texCoords[0].v = 0;
	
	texCoords[1].u = ITOX(15);
	texCoords[1].v = 0;
	
	texCoords[2].u = 0;
	texCoords[2].v = ITOX(15);
	
	texCoords[3].u = ITOX(15);
	texCoords[3].v = ITOX(15);
	//set up indices
	uint16* indices = new uint16[6];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 1;
	indices[5] = 3;

	//fill in the correct numbers
	RenderData* rtemp = new RenderData;
	rtemp->m_vertices = tempVerts;
	rtemp->m_numVertices = 4;

	rtemp->m_texCoords = texCoords;
	rtemp->m_numTexCoords = 4;
	
	rtemp->m_indices = indices;
	rtemp->m_numIndices = 6;
	
	//load the texture
	Texture* tex = new Texture;
	tex->Load(WATER);
	rtemp->m_texture = tex;
	//set up the renderInstance
	m_sea = new RenderInstance;
	m_sea->position(FTOX(0),FTOX(0),FTOX(0));

	m_sea->renderData(rtemp);
}

bool Seascape::Collided(Vector3 pos,int32 radius)
{
	for(uint16 i = 0 ; i < m_numModels ; i++)
	{
		Vector3 islandPos = m_models[i].position();

		//if the distance between the two points is more than the two radii, no collision
		//calculate the distance squared
		int32 dist = MULX( (islandPos.x - pos.x),(islandPos.x - pos.x) ) +
					 MULX( (islandPos.z - pos.z),(islandPos.z - pos.z) );

		int32 radii = MULX((radius + FTOX(1.5)),(radius + FTOX(1.5)));

		if(dist < radii )
			return true;
	}
	return false;
}

void Seascape::RenderWater(Renderer* renderer)
{

	glMatrixMode(GL_TEXTURE);
	//shift the texture coords to simulate motion
	glTranslatex(m_texTranslate,m_texTranslate,0);
	glRotatex(FTOX(35),0,0,1);
	glColor4x(65536,65536,65536,FTOX(0.6f));

	//render the first sea quad
	renderer->Render(m_sea);
	//reset the texture matrix
	glLoadIdentity();
	//now scale and move the tex coords
	glScalex(FTOX(0.7f),FTOX(0.7f),FTOX(0.7f));
	glTranslatex(-m_texTranslate,0,0);
	
	//change the transparency
	glColor4x(65536,65536,65536,FTOX(0.35f));

	//render another water quad just slightly above the previous one
	glMatrixMode(GL_MODELVIEW);
	m_sea->Translate(0,6553,0);	
	renderer->Render(m_sea);	
	m_sea->Translate(0,-6553,0);
	glMatrixMode(GL_TEXTURE);

	//reset the texture matrix again
	glLoadIdentity();

	//change back to modelview
	glMatrixMode(GL_MODELVIEW);

}

void Seascape::Render(Renderer* renderer)
{
	//render all the models first
	for(uint16 i = 0 ; i < m_numModels ; i++)
	{		
		renderer->Render(&m_models[i]);

		//draw reflection
		m_models[i].scale(2*65536,-2*65536,2*65536);
		renderer->Render(&m_models[i]);
		m_models[i].scale(2*65536,2*65536,2*65536);
	}

		//make sure the m_texTranslate never goes out of bounds
	if(m_waterMoved == false)
		m_texTranslate += FTOX(0.005);
	if(m_waterMoved == true) 
		m_texTranslate -= FTOX(0.005);

	if(m_texTranslate > 983040)
		m_waterMoved = true;
	if(m_texTranslate < -983040)
		m_waterMoved = false;

	//Now render the water plane
	//We render it 4 times, so that it forms a giant block

	glPushMatrix();
	
	//set up blending
	glEnable(GL_BLEND);
	glColor4x(65536,65536,65536,FTOX(0.6f));
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	RenderWater(renderer);
	
	glTranslatex(0,0,ITOX(WORLD_HEIGHT / 2 +4));
	RenderWater(renderer);
	
	glTranslatex(ITOX(WORLD_HEIGHT / 2 + 4),0,0);
	RenderWater(renderer);
	
	glTranslatex(0,0,-ITOX(WORLD_HEIGHT / 2 + 4));
	RenderWater(renderer);

	//turn of blending and restore the original color
	glDisable(GL_BLEND);
	glColor4x(65536,65536,65536,65536);
	
	glPopMatrix();
}

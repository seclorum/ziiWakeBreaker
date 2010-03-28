//#include "Chest.h"

#include "Info.h"
#include "Racer.h"
#include "RenderInstance.h"

class Chest {

private:
		int m_chestsRecovered;
		RenderInstance *m_ri;
		int m_up;

public:
	void	Initialize(Info* info);
	void 	Reset();
	void	Update(Racer* ship);
	int		rand() {};
};

void Chest::Initialize(Info* info)
{
	m_chestsRecovered = 0;
	m_ri = new RenderInstance;
	m_ri->renderData(info->m_mm->GetChest());

	//rotate so he's always right side up
	Vector3 vec(-ITOX(90),0,0);
	m_ri->rotation(vec);
	m_ri->scale(FTOX(0.5),FTOX(0.5),FTOX(0.5));

	Reset();
}

void Chest::Reset()
{
	m_up = true;
	int32 z = rand() % WORLD_WIDTH;
	int32 x = rand() % WORLD_HEIGHT;

	m_ri->position(ITOX(x),0,ITOX(z));

}
void Chest::Update(Racer* ship)
{
	//test of the ship has collided with this chest
	Vector3 chestPos = m_ri->position(),
			shipPos = ship->m_ri->position();

	if(m_up)
		chestPos.y += FTOX(0.01);
	else
		chestPos.y -= FTOX(0.01);

	if(chestPos.y >= FTOX(-0.2))
		m_up = false;

	if(chestPos.y < FTOX(-0.6))
		m_up = true;


	m_ri->position(chestPos);

	if( MULX((chestPos.x - shipPos.x),(chestPos.x - shipPos.x)) +
		MULX((chestPos.z - shipPos.z),(chestPos.z - shipPos.z)) < ITOX(2) )
	{
		m_chestsRecovered++;
		Reset();
	}
}

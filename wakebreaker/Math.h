/* The code is completely free to use in any project, commercial 
   or hobby, for fun or for profit.  Just leave these lines in, 
   and if you feature a credits screen, it wouldn't be mean to 
   mention me.  Also, I am not responsible for any damage to anything
   that this code might cause.  Have fun.

  (C) 2005 - Peter Angstadt
*/


#ifndef _MATH_H_
#define _MATH_H_

#include "Base.h"

//integer to fixed point
#define ITOX(x) ((x)<<16)

//fixed point to integer
#define XTOI(x) ((x)>>16)

//float to fixed point
#define FTOX(x) ( (int32)((x) * 65536) )

//fixed point to float
#define XTOF(x) ( ((float)(x)) / 65536 )

//multiply two fixed points
#define MULX(x,y) ( ((int64)(x)) * ((int64)(y)) / 65536 )

//divide two fixed points
#define DIVX(x,y) ( (((int64)(x)) << 16) / (y) )

#define DEG2RADX 1144 //pi over 180

#define RAD2DEGX 3754936 //180 over pi

#define asininv
#define bsininv
#define csininv

//returns the square root of a float or fixed point
float sqrtx(float x);
int sqrtx(int32 x);


class Math
{
	int32* m_sinTable;
	int32* m_cosTable;
	float m_accuracy;
public:
	Math() : m_sinTable(NULL), m_cosTable(NULL)
	{}
	~Math() 
	{ 
		SAFE_ARRAY_DELETE(m_sinTable); 
		SAFE_ARRAY_DELETE(m_cosTable);
	}

	void Initialize();

	//------------------------------
	inline int32 fsinf(int32 f)
	{
		
		if(f >= PIX)
		{
			f -= PIX;
			f = MULX(-65536,f);
		}
		else if(f <= -PIX)
		{
			f += PIX;
			f = MULX(-65536,f);
		}
		
		int abs_f = f;

		if(f < 0)
		{
			abs_f = MULX(-65536,abs_f);
		}

		//we grab the array element
		int32 x1 = XTOI(DIVX(abs_f,259));
		//now we have the one above it
		int32 x2 = x1 + 1;
		//if(x1 == 804)
		//	return 0;

		int32 sinX2 = m_sinTable[x2];
		int32 angle = (sinX2 - MULX(DIVX((sinX2 - m_sinTable[x1]),ITOX(x2 - x1)),abs_f));

		if(f < 0)
		{
			angle = MULX(angle,-65536);
		}
		return angle;
	}
	//------------------------------
	inline int32 fcosf(int32 f)
	{
		if(f >= PIX)
		{
			f -= 2 * PIX;
			f = MULX(-65536,f);
		}
		else if(f <= -PIX)
		{
			f += 2 * PIX;
			f = MULX(-65536,f);
		}
		
		int abs_f = f;

		if(f <= 0)
		{
			abs_f = MULX(-65536,abs_f);
		}

		//we grab the array element
		int32 x1 = XTOI(DIVX(abs_f,259));
		//now we have the one above it
		int32 x2 = x1 + 1;
		if(x1 == 804)
			return -65536;

		int32 sinX2 = m_cosTable[x2];
		int32 angle = (sinX2 - MULX(DIVX((sinX2 - m_cosTable[x1]),ITOX(x2 - x1)),abs_f));

		return angle;
	}



};

#endif
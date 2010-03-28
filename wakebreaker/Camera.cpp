#include "Camera.h"	
#include "Math.h"


void Camera::Update()
{
	Vector3 f = m_center - m_eye;
	//normalize it
	//int test = XTOF(f.z);
	int mag = sqrtx( (int32)(MULX(f.x,f.x) + (int32)MULX(f.y,f.y) + (int32)MULX(f.z,f.z)) );
	
	int n = DIVX(ITOX(1),mag);
	
	f.x = MULX(f.x,n);
	f.y = MULX(f.y,n);
	f.z = MULX(f.z,n);

	//update direction
	m_dir = f;


	Vector3 s = f ^ m_up,
			u = s ^ f;

	int matrix[16] = { s.x, u.x, -f.x, 0,
						s.y, u.y, -f.y, 0,
						s.z, u.z, -f.z, 0, 
						0,  0,   0,  ITOX(1) };


	glMultMatrixx(matrix);
	
	glTranslatex(-m_eye.x,-m_eye.y,-m_eye.z);

}
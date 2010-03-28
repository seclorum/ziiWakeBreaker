#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Vector3.h"

class Camera
{
	Vector3 m_eye,		//position
			m_center,	//what the camera is looking at
			m_up,		//the up vector
			m_dir;		//normalized direction vector

public:

	Camera() : m_eye(0,0,ITOX(-10)), m_center(0,0,0), m_up(0,1,0)
	{}

	//moves the camera
	void Translate(const Vector3& trans)
	{ m_eye += trans; }


	//fills the eye, center, up vectors for use when the camera updates
	void LookAt(const Vector3& pos,const Vector3& center,const Vector3& up)
	{
		m_eye = pos;
		m_center = center;
		m_up = up;
	}
	
	//returns the direction or position
	const Vector3& Direction() const { return m_dir; }
	const Vector3& Position() const { return m_eye; }

	//this is an implementation of the gluLookAt() function
	void Update();



};


#endif
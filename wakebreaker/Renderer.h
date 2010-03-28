#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Base.h"
#include "Math.h"
#include "RenderInstance.h"

#include <skin.h>

class Renderer
{
private:
	EGLDisplay*	m_display;
	const EGLSurface*	m_surface;

	RenderData* m_currData;	//used to reduce state changes

	int16 m_currTexture; //used to reduce state changes

	bool m_fogEnabled;
public:
	Renderer() : m_currData(NULL), m_fogEnabled(false)
	{}
	~Renderer(){  }

	void j_gluPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);
	bool resizeWindow(int width, int height);

	//creates the opengl context
	bool Create();

	//doestry the opengl context
	void Destroy();

	//sets up the openGL enable/disables
	void Initialize(uint16 width, uint16 height);

	//Renders a renderInstance tot he screen
	void Render(RenderInstance* data);

	void SwapBuffers() const { /* eglSwapBuffers(m_display, m_surface); !J! */ }

	void Draw2DQuad(Texture* tex);
	void DrawOneSmoothTri(int width, int height);
	void EnableFog()
	{
		if(!m_fogEnabled)
		{
			glEnable(GL_FOG);
			m_fogEnabled = true;
		}
	}
	void DisableFog()
	{
		if(m_fogEnabled)
		{
			glDisable(GL_FOG);
			m_fogEnabled = false;
		}
	}

};

#endif

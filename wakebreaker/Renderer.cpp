#include <syslog.h>
#include "Game.h"

#include <plaszma.h>
#include <skin.h>

#include <3dcell/3dcell.h>

// Cheap and dirty
void Renderer::j_gluPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar)
{
    GLfloat xmin, xmax, ymin, ymax;

    ymax = zNear * tan(fovy * M_PI / 360.0);
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;
    glFrustumf(xmin, xmax, ymin, ymax, zNear, zFar);
}


/* function to reset our viewport after a window resize */
bool Renderer::resizeWindow(int width, int height)
{
    /* Height / width ration */
    GLfloat ratio;

    /* Protect against a divide by zero */
    if (height==0)
    {
        height=1;
    }

    ratio=(GLfloat)width/(GLfloat)height;

    /* Setup our viewport. */
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    /* change to the projection matrix and set our viewing volume. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* Set our perspective */
    j_gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode(GL_MODELVIEW);

    /* Reset The View */
    glLoadIdentity();

    return true;
}


//---------------------------------
//bool Renderer::Create(HWND* hWnd);
bool Renderer::Create()
{

	return TRUE;
}
//---------------------------------

// NOTE Logging details are included for sanity only
void Renderer::Initialize(uint16 width,uint16 height)
{

	m_currTexture = -1;

	WB_LOGGER(LOG_ERR, "renderer initialized: %d x %d", width, height);
#if 1
	WB_LOGGER(LOG_ERR, "Initialize A");

	// Enable the zbuffer
	glEnable(GL_DEPTH_TEST);
	WB_LOGGER(LOG_ERR, "Initialize b");

	// Set the view port size to the window size
	glViewport(0, 0, width, height);
	WB_LOGGER(LOG_ERR, "Initialize c");
resizeWindow(width, height);
	// Diable lighting and alpha blending
	glDisable(GL_LIGHTING);
	WB_LOGGER(LOG_ERR, "Initialize d");
	glDisable(GL_BLEND);
	WB_LOGGER(LOG_ERR, "Initialize e");

	glCullFace(GL_BACK);
	WB_LOGGER(LOG_ERR, "Initialize f");
	glEnable(GL_CULL_FACE);
	WB_LOGGER(LOG_ERR, "Initialize g");

	glEnable(GL_TEXTURE_2D);
	WB_LOGGER(LOG_ERR, "Initialize h");

	glDisable(GL_DITHER);
	WB_LOGGER(LOG_ERR, "Initialize i");

    glClearColor(0.745f, 0.95f, 1.0f, 0.f);
	WB_LOGGER(LOG_ERR, "Initialize j");

	// Set a precomputed view matrix
	int matrix[16] = {	 FTOX( 2.41421 / ((float)width/(float)height) ),  FTOX(0.000000), FTOX(0.000000), FTOX(0.000000),
						 FTOX(0.000000), FTOX(2.41421),  FTOX(0.000000), FTOX(0.000000),
						 FTOX(0.000000), FTOX(0.000000), FTOX(-1.00020), FTOX(-1.00000),
						 FTOX(0.000000), FTOX(0.000000), FTOX(-2.00020), FTOX(0.000000) };
	WB_LOGGER(LOG_ERR, "Initialize k");


	glMatrixMode(GL_PROJECTION);
	WB_LOGGER(LOG_ERR, "Initialize l");
	glLoadMatrixx(matrix);
	WB_LOGGER(LOG_ERR, "Initialize m");

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	WB_LOGGER(LOG_ERR, "Initialize n");

	// Set up fog

	glFogx(GL_FOG_DENSITY,FTOX(0.01));
	glFogx(GL_FOG_MODE,GL_EXP);
	WB_LOGGER(LOG_ERR, "Initialize o");

	glHint(GL_FOG_HINT, GL_DONT_CARE);
	WB_LOGGER(LOG_ERR, "Initialize p");

	int color[] = { FTOX(0.745f), FTOX(0.95f), FTOX(1.0f), FTOX(0.f) };
	glFogxv(GL_FOG_COLOR,color);

	WB_LOGGER(LOG_ERR, "Initialize q");

	// Set the model view to identity
	glMatrixMode(GL_MODELVIEW );
	glLoadIdentity();
	WB_LOGGER(LOG_ERR, "Initialize r");

	// Enable the arrays we want used when we glDrawElements()
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	WB_LOGGER(LOG_ERR, "Initialize s");
#endif

#if 0
	if (!resizeWindow(width, height))
		WB_LOGGER(LOG_ERR, "!resizeWindow");
	else
		WB_LOGGER(LOG_ERR, ":) resizeWindow");
#endif

}
//---------------------------------
//Renders a renderInstance
void Renderer::Render(RenderInstance* data)
{
	if(data->renderData() != m_currData)
	{
		if(data->renderData()->m_texCoords)
			glTexCoordPointer(2,GL_FIXED,0,&data->renderData()->m_texCoords[0]);

		glVertexPointer(3, GL_FIXED, 0, data->renderData()->m_vertices[0].v);

		if(data->renderData()->m_colorData)
			glColorPointer(4, GL_UNSIGNED_BYTE, 0, data->renderData()->m_colorData[0].v);	// Set the color data source

		m_currData = data->renderData();
	}

	if(data->renderData()->m_texture && m_currTexture != data->renderData()->m_texture->id())
	{
		data->renderData()->m_texture->Bind();
		m_currTexture = data->renderData()->m_texture->id();
	}

	glPushMatrix();

	glTranslatex(data->position().x,data->position().y,data->position().z);
	glScalex(data->scale().x,data->scale().y,data->scale().z);
	glRotatex(data->rotation().y,0,1,0);
	glRotatex(data->rotation().x,1,0,0);
	glRotatex(data->rotation().z,0,0,1);

	glDrawElements(GL_TRIANGLES, data->renderData()->m_numIndices, data->renderData()->m_indexDataType, data->renderData()->m_indices);// Draw the triangle

	glPopMatrix();
}


// Helper functions to support the port effort - these were gotten working
// to prove the project setup, first, then the rest of the Render class
// was enabled.  These functions are included only for continued reference
// as needed, but feel free to ignore.
// HELPER
void Renderer::DrawOneSmoothTri(int width, int height)
{
	static const GLbyte vertices[3 * 3] = {-1,1,0, 1,-1,0, 1, 1, 0};
	static const GLubyte colors[3 * 4] = {255,0,0,255, 0,255,0,255, 0,0,255,255};
	glDisable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.f, 0.f, 0.1f, 1.f);
	glVertexPointer(3, GL_BYTE, 0, vertices);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glViewport(0,0, width, height);
	glMatrixMode(GL_PROJECTION);
	glFrustumf( -1.f, 1.f, -1.f, 1.f, 3.f, 1000.f);
	glMatrixMode(GL_MODELVIEW);

}
//---------------------------------
//Draws a screen size quad with tex on it
// HELPER
void Renderer::Draw2DQuad(Texture* tex)
{

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glPushMatrix();
	glLoadIdentity();

	glTranslatex(0,  FTOX(-0.25), ITOX(-5));


  	  int FaceData[18] =
	  {
		-FTOX(3), -ITOX(2), ITOX(0),    // First vertex position
		 FTOX(3), -ITOX(2), ITOX(0),    // Second vertex position
		-FTOX(3),  ITOX(2), ITOX(0),    // Third vertex position

		 FTOX(3),  ITOX(2), ITOX(0),    // First vertex position
		 FTOX(3), -ITOX(2), ITOX(0),    // Second vertex position
		-FTOX(3),  ITOX(2), ITOX(0)    // Third vertex position

	  };
	  int TexCoordData[12] =
	  {
		  FTOX(0.0),FTOX(0.0),
		  FTOX(1.0),FTOX(0.0),
		  FTOX(0.0),FTOX(1.0),

		  FTOX(1.0),FTOX(1.0),
		  FTOX(1.0),FTOX(0.0),
		  FTOX(0.0),FTOX(1.0),

	  };


	  tex->Bind();

	  uint8 IndexData[6] = {0, 1, 2, 5, 4, 3};

	  glVertexPointer(3, GL_FIXED, 0, FaceData);  // Set the vertex (position) data source
	  glTexCoordPointer(2, GL_FIXED, 0, TexCoordData);  // Set the vertex (position) data source

	  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, IndexData);  // Draw the triangle

	  glPopMatrix();

}

//---------------------------------
void Renderer::Destroy()
{
	// Destroy not done, Plaszma will do it anyway ..
#if 0
	eglMakeCurrent(EGL_NO_DISPLAY, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);


	if(m_surface)
	{
		eglDestroySurface(m_display, m_surface);
		m_surface = NULL;
	}
	if(m_display)
	{
		eglTerminate(m_display);
		m_display = NULL;
	}
#endif
}

//---------------------------------

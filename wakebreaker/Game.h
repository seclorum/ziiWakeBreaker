#ifndef _GAME_H_
#define _GAME_H_

#include "Base.h"
#include "Renderer.h"
#include "Camera.h"
#include "ModelManager.h"

#include "Texture.h"
#include "Seascape.h"
#include "Racer.h"
#include "Math.h"
#include "Info.h"
#include "RaceCourse.h"

#include <skin.h>

// TODO: Turn WB_LOGGER into a cairo-using CBuffer for blitting ..
#ifndef WB_LOGGER
#define WB_LOGGER(x, ...) syslog(x, ##__VA_ARGS__)
#endif
// FOR NOW: use syslog .. NOTE: *must* be enabled on the Zii
// Egg manually by the developer, see Zii Egg dev forums for
// details.

enum Keys
{
	G_UP = 0,
	G_DOWN,
	G_RIGHT,
	G_LEFT,
	G_OK,
	G_DEVICE1,
	G_DEVICE2
};

class Game
{
private:

	Renderer		m_renderer;
	Camera			m_camera;
	Math			m_math;
	ModelManager	m_modelManager;
	bool			m_gameCreated;
	Info* m_info;		//a helper structure containing the modelmanager and math class
	Texture* m_splash;	//the victory/defeat/opening screen
	Seascape* m_seascape;	//the ocean environment
	Racer* m_racers;		//the racers
	int32 m_numRacers;
	RaceCourse* m_raceCourse;	//the course they race on
	bool m_playing;			//are we racing
	int16 m_width, m_height;	//window dimensions
	int16 m_keysDown[7];	//we only test for 4 keys

	bool m_hasWon;		//did we win?
public:
	Game(){m_gameCreated = false;}
	~Game(){ }

	void Menu();

	void SetDimensions(int w, int h);

	bool Create(EGLSurface* surf1, EGLSurface* surf2);
	bool Create(int w,int h);
	bool Create(int w,int h, EGLSurface* surf1, EGLSurface* surf2);
	bool Create(int w,int h, EGLSurface* surf1, EGLSurface* surf2, EGLDisplay *display);
	//bool Create(int w,int h,HWND* hWnd);
	void Destroy();

	//runs one frame of the game
	void Tick(int timeElapsed);

	void KeyDown(int keyCode);
	void KeyUp(int keyCode);

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }
	bool isGameCreated() const { return m_gameCreated;}
};

#endif

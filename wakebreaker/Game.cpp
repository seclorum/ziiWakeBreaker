#include <syslog.h>

#include "Math.h"
#include "Game.h"

void Game::Menu()
{
	if(m_playing)
	{
		Tick(0);
	}
	else
	{
		if(m_hasWon)
		{
			m_splash->Load(VICTORY);

		}
		if(!m_hasWon)
		{
			m_splash->Load(DEFEAT);

		}

		if(m_racers[0].CurrLap() == 0 && m_racers[0].NextCheckPoint() == 0)
		{
			m_splash->Load(SPLASH);
			WB_LOGGER(LOG_ERR, "Splash loaded..");

			for(int i = 0 ; i < 5 ; i++)
			{
				if(m_keysDown[i] == TRUE)
					m_playing = true;
			}
		}

		m_renderer.Draw2DQuad(m_splash);
		//m_renderer.DrawOneSmoothTri(310,240); // bork'd!

	}
}

void Game::SetDimensions(int w, int h)
{
	WB_LOGGER(LOG_ERR, "set dimensions: w=%d x h=%d", w, h);
	m_width = w;
	m_height = h;
}

bool Game::Create(int w, int h)
{
	SetDimensions(w,h);

	m_playing = false;
	//seed the random number generator
	srand((unsigned)time(NULL));
syslog(LOG_ERR, "Create A");

	//set up a convient info structure to pass to
	//functions which require the math and modelmanager
	m_info = new Info;
	m_info->m_math = &m_math;
	m_info->m_mm = &m_modelManager;

	//set up the splash screens
	m_splash = new Texture;

	syslog(LOG_ERR, "Create b");

	//Initialize the math and modelmanager
	m_math.Initialize();
	syslog(LOG_ERR, "Create c");

	m_modelManager.Initialize();
	syslog(LOG_ERR, "Create d");

	//Create and initialize the OpenGL ES renderer

m_renderer.Create();	// !J!
syslog(LOG_ERR, "Create e");

	//m_renderer.Create(hWnd);
	m_renderer.Initialize(GetWidth(),GetHeight());
	syslog(LOG_ERR, "Create f");

	//Set up the player
	m_racers = new Racer[2];
	syslog(LOG_ERR, "Create ff");

	m_racers[0].Initialize(m_info,BOAT2);
	syslog(LOG_ERR, "Create fg");
	m_racers[1].Initialize(m_info,BOAT1);

	syslog(LOG_ERR, "Create g");

	//Generate the race course first
	m_raceCourse = new RaceCourse;
	m_raceCourse->Generate(Vector3(ITOX(WORLD_WIDTH / 2),0,ITOX(WORLD_HEIGHT / 2)),
							58,
							60,
							m_info);
	syslog(LOG_ERR, "Create h");

	//Then add racers to it
	m_raceCourse->Initialize(m_racers,2);

	//set up the environment
	m_seascape = new Seascape;
	m_seascape->Generate(&m_modelManager);
	syslog(LOG_ERR, "Create i");

	//put the camera at an initial positiong
	Vector3 eye(-ITOX(0),ITOX(15),FTOX(-59.f)),
		    center(ITOX(WORLD_WIDTH / 2),0,ITOX(WORLD_HEIGHT / 2)),
			up(ITOX(0),ITOX(1),ITOX(0));
	syslog(LOG_ERR, "Create j");

	m_camera.LookAt(eye,center,up);
	syslog(LOG_ERR, "Create KKK");


	m_gameCreated = TRUE;
	return TRUE;
}
//---------------------------------
void Game::Destroy()
{
	SAFE_DELETE(m_raceCourse);
	SAFE_ARRAY_DELETE(m_racers);
	SAFE_DELETE(m_seascape);
	SAFE_DELETE(m_splash);

	m_renderer.Destroy();
}
//---------------------------------
void Game::Tick(int timeElapsed)
{
	//clear screen
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	//set up the camera to follow the player
	Vector3 eye(m_racers[0].Position().x - (MULX(ITOX(25), MULX(m_racers[0].m_dir.x,FTOX(0.7))  )),
			    ITOX(7),
				m_racers[0].Position().z - (MULX(ITOX(25),-MULX(m_racers[0].m_dir.z,FTOX(0.7)) )));

	Vector3 up(ITOX(0),ITOX(1),ITOX(0));

	m_camera.LookAt(eye,m_racers[0].Position(),up);


	m_camera.Update();

	//process input
	if(m_keysDown[G_UP] == TRUE)
	{
		m_racers[0].IncreaseSpeed(6553);
	}
	if(m_keysDown[G_DOWN] == TRUE)
	{
		m_racers[0].IncreaseSpeed(-6553);
	}
	if(m_keysDown[G_RIGHT] == TRUE)
	{
		m_racers[0].Rotate(-ITOX(5));
	}
	if(m_keysDown[G_LEFT] == TRUE)
	{
		m_racers[0].Rotate(ITOX(5));
	}
	if(m_keysDown[G_DEVICE1])
		m_renderer.EnableFog();

	if(m_keysDown[G_DEVICE2])
		m_renderer.DisableFog();


	//update all major game related classes
	m_raceCourse->Update();
	m_racers[0].Update(&m_math);
	m_racers[1].UpdateAI(&m_math,&m_racers[0]);


	if(m_seascape->Collided(m_racers[0].m_ri->position(),ITOX(1)))
	{
		m_racers[0].IncreaseSpeed(-ITOX(1));
	}
	if(m_seascape->Collided(m_racers[1].m_ri->position(),ITOX(1)))
	{
		m_racers[1].IncreaseSpeed(-ITOX(1));
	}
	if(m_racers[0].IsFinished())
	{
		m_hasWon = true;
		m_playing = false;
	}
	if(m_racers[1].IsFinished())
	{
		m_hasWon = false;
		m_playing = false;
	}
	m_seascape->Render(&m_renderer);
	m_raceCourse->Render(&m_renderer);

        //render everything
	m_racers[0].Render(&m_renderer);
	m_racers[1].Render(&m_renderer);

}
//---------------------------------
void Game::KeyDown(int keyCode)
{
	m_keysDown[keyCode] = TRUE;

}
void Game::KeyUp(int keyCode)
{
	m_keysDown[keyCode] = FALSE;

}

